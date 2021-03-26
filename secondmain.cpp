#include "secondmain.h"
#include "ui_secondmain.h"
#include<QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include "thirdmain.h"
#include "mainwindow.h"
#include <QTextStream>
QString username;
QString userID;

secondMain::secondMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondMain)
{

    ui->setupUi(this);
    this->setWindowTitle("USER Catalog");
}
void secondMain::userreturn(QString userReturn,QString userRID){
    ui->label_userdb->setText(userReturn);
    username=userReturn;
    userID=userRID;
}

secondMain::~secondMain()
{
    delete ui;
}
//create new todo list
void secondMain::on_pushButton_clicked()
{
    bool ok;

        qDebug()<<"in 1 click"<<username;
        qDebug()<<"username Id:"<<userID;
       QString catalogI = QInputDialog::getText(this, tr("Wellcome to create new datalog: "),
                                               tr("Input the catalog name:"), QLineEdit::Normal,
                                               tr("none"), &ok);
          if (ok && !catalogI.isEmpty()){
              qDebug() << catalogI;
          }
       //add list to the this catalog or


}

void secondMain::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Show the data", "There are all the data");
    qDebug()<<"username Id:"<<userID;
    //get the userID then user the queryF
    hide();
//    Tasklist = new tasklist(this);
//    Tasklist->show();
    thirdmain thirdmain;
    thirdmain.setModal(true);
    thirdmain.exec();

}


void secondMain::on_pushButton_3_clicked()
{
    this->hide();
    MainWindow *newmain= new MainWindow();
    newmain->show();
//    parentMainWindow.show();
}



void secondMain::on_label_3_linkActivated(const QString &link)
{

}
