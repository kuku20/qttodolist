#include "secondmain.h"
#include "ui_secondmain.h"
#include<QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include "thirdmain.h"
#include "mainwindow.h"
#include <QTextStream>
#include "create_todolist_dialog.h"

QString username;
QString userID;
QStandardItemModel *smodel;
bool searchActive = false;

secondMain::secondMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondMain)
{
    ui->setupUi(this);
    smodel = new QStandardItemModel(1,4,this);
//    queryOption queryOption;
//    username=queryOption.getID();
    ui->label_userdb->setText(username);
//    this->setWindowTitle("USER Catalog");
    this->setWindowTitle("secondmain");
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

