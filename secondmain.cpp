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

QString username;
QString userID;
secondMain::secondMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondMain)
{
    ui->setupUi(this);
//    queryOption queryOption;
//    username=queryOption.getID();
    ui->label_userdb->setText(username);
//    this->setWindowTitle("USER Catalog");
    this->setWindowTitle("secondmain");
    Statistics stat;
    stat.setModal(true);
    stat.exec();
}

void secondMain::userreturn(QString userReturn,QString userRID){
    ui->label_userdb->setText(userReturn);
    username=userReturn;
    userID=userRID;
//    queryOption queryOption;
//    queryOption.accessID(userID,username);
}

secondMain::~secondMain()
{
    delete ui;
}

//create new todo list
void secondMain::on_pushButton_clicked()
{
    create_todolist_dialog create_todolist_dialog;
    create_todolist_dialog.setModal(true);
    create_todolist_dialog.exec();
}

void secondMain::on_pushButton_2_clicked()
{
    qDebug()<<"username Id:"<<userID;
    //get the userID then user the queryF
    hide();
    //show all the list of the user and option
    thirdmain thirdmain;
    thirdmain.setModal(true);
    thirdmain.exec();
}

//logout
void secondMain::on_pushButton_3_clicked()
{
    this->hide();
    MainWindow *newmain= new MainWindow();
    newmain->show();

}


void secondMain::on_searchBUT_clicked()
{
    queryOption queryAct;
    QString key = ui->sLine->text();
    QString sqlQuery = queryAct.searchCata(key);
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

void secondMain::on_searchBUT_2_clicked()
{
    queryOption queryAct;
    QString key = ui->sLine->text();
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
