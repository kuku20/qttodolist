
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


secondMain::secondMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondMain)
{
    ui->setupUi(this);
    qDebug()<<"in2nd"<<queryOption::getUser();
    ui->label_userdb->setText(queryOption::getUser());
    this->setWindowTitle("secondmain_USER Catalog");
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
