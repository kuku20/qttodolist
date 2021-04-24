
#include "secondmain.h"
#include "ui_secondmain.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include "thirdmain.h"
#include "mainwindow.h"
#include <QTextStream>
#include "create_todolist_dialog.h"
#include "statistics.h"
#include "sent_notification.h"

secondMain::secondMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondMain)
{
    ui->setupUi(this);
    ui->label_userdb->setText(queryOption::getUser());
    this->setWindowTitle("secondmain_USER Catalog");
//    show();

    //    QMessageBox::warning(this,"Login","Username or password is not correct");
    int count=send_mail_notic();
    QString cout = QString::number(count);
    ui->pushButton_nt->setText(cout);
    if(count>0){
        ui->pushButton_nt->setStyleSheet("background-color: red");
    }
    else{
        ui->pushButton_nt->setStyleSheet("background-color: green");
    }

    //
}
int secondMain::send_mail_notic()
{
    QSqlDatabase conn = QSqlDatabase::database();
    queryOption queryOption;
    QSqlQuery qry(conn);
    QString email="SELECT email FROM users WHERE id = :id";
    qry.prepare(email);
    qry.bindValue(":id", queryOption::getID());
    qry.exec();
    while (qry.next()) {
        email = qry.value(0).toString();
    }
    QDate date = QDate::currentDate().addDays(1);
    QString date_input= date.toString("yyyy-MM-dd");
    //the key is day to search
    QString sqlQuery = queryOption.searchCata(date_input,"auto");
    qry.prepare(sqlQuery);
    qry.exec();
    int count=0;
    while (qry.next()) {
        QString noti=qry.value(4).toString();
        QString list_no_update=qry.value(1).toString();
        QString list_name_subject=qry.value(2).toString();
        if(noti!="NO"){
            count+=1;
            qDebug()<<qry.value(1).toString();
            queryOption.setInputNo(qry.value(1).toString());
            QString get_task = queryOption.getTasks();
            //get data
            QSqlQuery get_task_data(conn);
            get_task_data.prepare(get_task);
            get_task_data.exec();
            QString email_body="You have some task(s) in this list \nTask_name\t\tComplete \n";
            while (get_task_data.next()) {
                email_body+="+ "+get_task_data.value(2).toString()+"\t\t"+get_task_data.value(3).toString()+"\n";

            }
            if(noti==""""){
                queryOption.updateList("YES",list_no_update);
                Sent_notification* email_noti = new Sent_notification();
                list_name_subject=list_name_subject+" DUE " +date_input;
                email_noti->sendMail( email ,list_name_subject,email_body);
            }
        }
    }

    return count;
}

secondMain::~secondMain()
{

    delete ui;
}

//create new todo list
void secondMain::on_pushButton_clicked()
{
    //show the create_todolist_dialog
    create_todolist_dialog create_todolist_dialog;
    create_todolist_dialog.setModal(true);
    create_todolist_dialog.exec();

}

void secondMain::on_pushButton_2_clicked()
{
    //get the userID then user the queryF
    hide();
    //show all the list of the user and option
    thirdmain thirdmain;
    thirdmain.setModal(true);
    thirdmain.exec();
}

//logout, go back to the login
void secondMain::on_pushButton_3_clicked()
{
    this->hide();
    MainWindow *newmain= new MainWindow();
    newmain->show();
}

//search for catalog by input string
void secondMain::on_searchBUT_clicked()
{
    queryOption queryAct;
    QString key = ui->sLine->text();
    if(key != "") {
        //get the key by type and call the query
        QString sqlQuery = queryAct.searchCata(key,"type");
        QSqlQueryModel *smodel = new QSqlQueryModel();
        QSqlDatabase conn = QSqlDatabase::database();
        QSqlQuery qry(conn);
        qry.prepare(sqlQuery);
        if(qry.exec()){
            qDebug() << "Searching...";
        }
        else{
            qDebug() << "ERROR: Failed to find any results";
            qDebug() << "ERROR: " << qry.lastError().text();
        }
        //display the result if have any
        smodel->setQuery(qry);
        ui->searchView->setModel(smodel);
    }
}
//search for the tasks
void secondMain::on_searchBUT_2_clicked()
{
    queryOption queryAct;
    QString key = ui->sLine->text();
    if(key != "") {
        //get the key by type and call the query
        QString sqlQuery = queryAct.searchTasks(key);
        QSqlQueryModel *smodel = new QSqlQueryModel();
        QSqlDatabase conn = QSqlDatabase::database();
        QSqlQuery qry(conn);
        qry.prepare(sqlQuery);
        if(qry.exec()){
            qDebug() << "Searching...";
        }
        else{
            qDebug() << "ERROR: Failed to find any results";
            qDebug() << "ERROR: " << qry.lastError().text();
        }
        smodel->setQuery(qry);
        ui->searchView->setModel(smodel);
    }
}
//search by click to the calender to choice the date
void secondMain::on_calendarWidget_clicked(const QDate &date)
{
    queryOption queryAct;
    QString date_input= date.toString("yyyy-MM-dd");
    //the key is day to searck
    QString sqlQuery = queryAct.searchCata(date_input,"click");
    QSqlQueryModel *smodel = new QSqlQueryModel();
    QSqlDatabase conn = QSqlDatabase::database();
    QSqlQuery qry(conn);
    qry.prepare(sqlQuery);
    if(qry.exec()){
        qDebug() << "Searching...";
    }
    else{
        qDebug() << "ERROR: Failed to find any results";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    //display
    smodel->setQuery(qry);
    ui->searchView->setModel(smodel);
}
//display the static chart
void secondMain::on_statBUT_clicked()
{
    Statistics stat;
    stat.setModal(true);
    stat.exec();
}





void secondMain::on_pushButton_nt_clicked()
{

    //    showmex();
    //    QString count = QString::number(x);
    //    ui->label_userdb->setText(queryOption::getUser());
    queryOption queryOption;
    QDate date = QDate::currentDate().addDays(1);
    qDebug()<<date.toString("yyyy-MM-dd");
    QString date_input= date.toString("yyyy-MM-dd");
    //the key is day to search
    QString sqlQuery = queryOption.searchCata(date_input,"auto");
    QSqlDatabase conn = QSqlDatabase::database();
    QSqlQuery qry(conn);
    qry.prepare(sqlQuery);
    qry.exec();
    int count=0;
    while (qry.next()) {
        QString noti=qry.value(4).toString();
        if(noti!="NO"){
            count+=1;
            QString list_name=qry.value(2).toString();
            qDebug() << "Notification under 24h...";
            qDebug() << "You have list: "<<list_name<<"due tomorow!!!!";
            //        QMessageBox::warning(this,"DUE!!DUE","You have list: "+list_name+"due tomorow!!!!");
            //repeat this noti
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this,list_name+" : DUE tomorow!!!!",
                                         list_name+"\n\nDo you want to REPEAT this notification??",
                                         QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::No) {
                qDebug() << "Yes was *not* clicked";
                queryOption.updateList("NO",qry.value(1).toString());
                count-=1;

            } else {

                qDebug() << "Yes was clicked";

                queryOption.updateList("YES",qry.value(1).toString());
            }
        }
        else{
            //        QMessageBox::information(this,"GOOD-NEWS","YOU HAVE NOTHING DUE UNDER 24h");
            qDebug() << "ERROR: Failed to find any results";
            qDebug() << "ERROR: " << qry.lastError().text();
        }

    }
    if(count==0){
        ui->pushButton_nt->setStyleSheet("background-color: green");
    }

    ui->pushButton_nt->setText(QString::number(count));
}
