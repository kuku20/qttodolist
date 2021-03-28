#include "createnewacount.h"
#include "ui_createnewacount.h"
#include <QMessageBox>
#include <QString>
#include "mainwindow.h"
#include "queryoption.h"

createNewAcount::createNewAcount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createNewAcount)
{
    ui->setupUi(this);
}

createNewAcount::~createNewAcount()
{
    delete ui;
}

void createNewAcount::on_pushButton_clicked()
{
    int exist_u = 0;
    int exist_e=0;
    QString new_user = ui->lineEdit_Nuser->text();
    QString new_pass = ui->lineEdit_Npass->text();
    QString new_email = ui->lineEdit_Nemail->text();
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
        close();
        createNewAcount createnewacount;
        createnewacount.setModal(true);
        createnewacount.exec();
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
        close();
        QMessageBox::information(this, "New account created", "You have create account!!");
    }
}
