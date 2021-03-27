#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "queryoption.h"
#include "createnewacount.h"

//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowTitle("Wellcom to TO_DO_LIST");
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
     db.setHostName("127.0.0.1");
     db.setDatabaseName("test");
     db.setUserName("root");
     db.setPassword("");
     if(db.open()){
         ui->label->setText("connected:");
     }
     else{
          ui->label->setText("NOT connected:");
     }
       QSqlQuery query(db);
        queryOption queryOption;
        queryOption::setCon(db);
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
     QString q="SELECT * FROM users WHERE users username = "+username;
     qDebug()<<q;
    query.exec("SELECT * FROM users");
    while (query.next()) {
            QString usernamedb = query.value(2).toString();
            QString passdb = query.value(1).toString();
            if(username==usernamedb && password==passdb){
                QMessageBox::information(this, "Login", "You are login!!");
                userlogined=true;
                close();
                secondMain secondMain;
                secondMain.userreturn(username,query.value(3).toString());
                queryOption::accessID(query.value(3).toString());
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

void MainWindow::on_pushButton_2_clicked()
{
    createNewAcount createnewacount;
    createnewacount.setModal(true);
    createnewacount.exec();
}
