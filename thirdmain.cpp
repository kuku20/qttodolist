#include "thirdmain.h"
#include "ui_thirdmain.h"
#include"secondmain.h"
#include"mainwindow.h"
#include"task_dialog.h"


thirdmain::thirdmain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thirdmain)
{
    qDebug()<<"";
    ui->setupUi(this);
    this->setWindowTitle("USER datalog_list__thirdmain.cpp");
    queryOption queryOption;
    ui->label->setText(queryOption.getUsername().toUpper()+"'s Catalogs : ");
    model = new QStandardItemModel(3,3,this);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("list_no"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("list_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Create"));
//    model->setData()

//    for(int row = 0; row < 3; row++)
//        {
//            for(int col = 0; col < 3; col++)
//            {
//                QModelIndex index
//                        = model->index(row,col,QModelIndex());
//                // 0 for all data
//                model->setData(index,row);
//            }
//        }
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
    task_dialog task_dialog;
    task_dialog.setModal(true);
    task_dialog.exec();
}
