#include "task_dialog.h"
#include "ui_task_dialog.h"
#include"queryoption.h"

task_dialog::task_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::task_dialog)
{
    ui->setupUi(this);
     this->setWindowTitle("USER task list__task_dialog.cpp");
    queryOption queryOption;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q(db);

    QString s=queryOption.getTasks();
    q.prepare(s);
    q.exec();
    model = new QStandardItemModel(q.size(),3,this);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cata_no"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("task_no"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("task_name"));
    ui->tableView->setModel(model);
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

task_dialog::~task_dialog()
{
    delete ui;
}

void task_dialog::on_pushButton_clicked()
{
    //add more task to the specific catalog
}

void task_dialog::on_pushButton_2_clicked()
{
    //choice task_no to delete
}

void task_dialog::on_pushButton_3_clicked()
{
    //choice task_no to change name
}

void task_dialog::on_pushButton_4_clicked()
{
    //go back to the catalog
    close();
}
