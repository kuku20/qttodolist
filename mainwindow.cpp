#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "queryoption.h"

//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowTitle("Wellcom to TO_DO_LIST");
        queryOption queryOption;
        queryOption::setCon();
       queryOption.createUser();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit_userInput->text();
    QString password = ui->lineEdit_passInput->text();
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    bool userlogined=false;
    query.exec("SELECT * FROM users");
    while (query.next()) {
            QString usernamedb = query.value(2).toString();
            QString passdb = query.value(1).toString();
            if(username==usernamedb && password==passdb){
                QMessageBox::information(this, "Login", "You are login!!");
                userlogined=true;
                close();
                queryOption::accessID(query.value(3).toString());
                queryOption::accessUser(username);
                secondMain secondMain;
//                secondMain.userreturn(username,query.value(3).toString());
                queryOption::setCon(db);
                secondMain.setModal(true);
                secondMain.exec();
                break;
            }
        }
    if(userlogined==false){
        QMessageBox::warning(this,"Login","Username or password is not correct");

    }
}



void MainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"NONO";
    int exist_u = 0;
    int exist_e=0;
    QString new_user = ui->lineEdit_Nuser->text();
    QString new_pass = ui->lineEdit_Npass->text();
    QString new_email = ui->lineEdit_Nemail->text();
    qDebug()<<"NONO"<<new_user;
    queryOption queryOption;
    exist_u=queryOption.checkIfExist(new_user,"users");
    exist_e=queryOption.checkIfExist(new_email,"users");

    if(exist_u<0 or exist_e <0){
        if(exist_u<0){
            QMessageBox::information(this, "Warning",
                                     "This User already exist!!!");
        }
        else{
            QMessageBox::information(this, "Warning",
                                     "This  Email already exist!!!");
        }
        }
    else
    {
        qDebug()<<exist_u;
        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);
        query.prepare("INSERT INTO users(username, email, password) "
                          "VALUES (:username, :email, :password)");
        query.bindValue(":username", new_user);
        query.bindValue(":email", new_email);
        query.bindValue(":password", new_pass);
        query.exec();
        QMessageBox::information(this, "New account created", "You have create account!!");
    }
}
