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
    qDebug()<<"";
    ui->setupUi(this);
    this->setWindowTitle("USER datalog_list__thirdmain.cpp");
    queryOption queryOption;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q(db);
//    ui->label->setText(queryOption.getUsername().toUpper()+"'s Catalogs : ");

    QString s=queryOption.getLists();
    q.prepare(s);
    q.exec();
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
            // 0 for all data

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

void thirdmain::on_pushButton_3_clicked()
{
    close();
    secondMain secondMain;
    secondMain.setModal(true);
    secondMain.exec();
}



void thirdmain::on_pushButton_2_clicked()
{
    //display the specfic catalog
    bool ok;
    QString catalogI = QInputDialog::getText(this, tr("Which catalog???: "),
                                            tr("Input the list_no:"), QLineEdit::Normal,
                                            tr("input the list_no"), &ok);
       if (ok && !catalogI.isEmpty()){
           qDebug() << catalogI;
       }
       else{
           qDebug() << catalogI;
           return ;
       }
    queryOption queryOption;
    queryOption.setInputNo(catalogI);
    task_dialog task_dialog;
    task_dialog.setModal(true);
    task_dialog.exec();
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
           queryOption.delList(catalogI);
           close();
           thirdmain thirdmain;
           thirdmain.setModal(true);
           thirdmain.exec();
       }
       else{
           qDebug() << catalogI;
           return ;
       }
}
