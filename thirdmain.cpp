#include "thirdmain.h"
#include "ui_thirdmain.h"
#include"secondmain.h"
#include"mainwindow.h"
#include"task_dialog.h"
#include<QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include "queryoption.h"

thirdmain::thirdmain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thirdmain)
{
    ui->setupUi(this);
    this->setWindowTitle("USER datalog_list__thirdmain.cpp");
    queryOption queryOption;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q(db);
    //to show the username
    ui->label->setText(queryOption.getUser().toUpper()+"'s Catalogs : ");
    //get data
    QString s=queryOption.getLists();
    q.prepare(s);
    q.exec();
    //create table and display
    model = new QStandardItemModel(q.size(),3,this);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("list_no"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("list_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Create"));
    int row=0;
    while (q.next()) {
    {
        for(int col = 0; col < 3; col++)
        {
            QModelIndex index
                    = model->index(row,col,QModelIndex());
                model->setData(index,q.value(col).toString());
            }
        }
        row++;
    }
}

thirdmain::~thirdmain()
{
    delete ui;
}

void thirdmain::on_pushButton_2_clicked()
{
    //display the specfic catalog(LIST_NO)
    bool ok;
    QString inNum = QInputDialog::getText(this, tr("Which catalog???: "),
                                            tr("Input the list_no:"), QLineEdit::Normal,
                                            tr(""), &ok);
       if (ok && !inNum.isEmpty()){
           qDebug() << inNum;
       }
       else{
           qDebug() << inNum;
           return ;
       }
    queryOption queryOption;
    //search if list_no in the user
    QString scan= "catalog WHERE id ="+queryOption.getID();
    int exist=0;
     exist=queryOption.checkIfExist(inNum,scan);
     qDebug()<<"oday"<<exist;
    if(exist<0){
        queryOption.setInputNo(inNum);
        task_dialog task_dialog;
        task_dialog.setModal(true);
        task_dialog.exec();
    }
    else{
        QMessageBox::information(this, "Warning",
                                 "You don't have this list_no");
    }

}

void thirdmain::on_pushButton_clicked()
{
    //delete the catalog_name
    bool ok;
    QString catalogI = QInputDialog::getText(this, tr("Which catalog???: "),
                                            tr("Input the list_no:"), QLineEdit::Normal,
                                            tr(""), &ok);
       if (ok && !catalogI.isEmpty()){
           qDebug() << catalogI;
           queryOption queryOption;
           //check to delete
           QString scan= "catalog WHERE id ="+queryOption.getID();
           int exist=0;
            exist=queryOption.checkIfExist(catalogI,scan);
            qDebug()<<"oday"<<exist;
           if(exist<0){
               queryOption.delList(catalogI);
               close();
               thirdmain thirdmain;
               thirdmain.setModal(true);
               thirdmain.exec();
           }
           else{
               QMessageBox::information(this, "Warning",
                                        "You don't have this list_no");
           }
       }
       else{
           qDebug() << catalogI;
           return ;
       }
}

void thirdmain::on_pushButton_5_clicked()
{
    //change catalog name
    bool ok;
    QString list_no = QInputDialog::getText(this, tr("Which catalog???: "),
                                            tr("Input the list_no:"), QLineEdit::Normal,
                                            tr(""), &ok);
       if (ok && !list_no.isEmpty()){

           QString newUpdate = QInputDialog::getText(this, tr("Which catalog???: "),
                                                   tr("Input the new list_name :"), QLineEdit::Normal,
                                                   tr(""), &ok);
           if (ok && !newUpdate.isEmpty()){
               queryOption queryOption;
               //check to update
               QString scan= "catalog WHERE id ="+queryOption.getID();
               int exist=0;
                exist=queryOption.checkIfExist(newUpdate,scan);
                qDebug()<<"oday"<<exist;
               if(exist<0){

                   queryOption.updateList(newUpdate, list_no);
                   close();
                   thirdmain thirdmain;
                   thirdmain.setModal(true);
                   thirdmain.exec();
               }
               else{
                   QMessageBox::information(this, "Warning",
                                            "You don't have this list_no");
               }
           }
           else{
               return ;
           }
       }
       else{
           return ;
       }
}
//go back to user option
void thirdmain::on_pushButton_3_clicked()
{
    close();
    secondMain secondMain;
    secondMain.setModal(true);
    secondMain.exec();
}
