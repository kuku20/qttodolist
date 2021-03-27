#include "task_dialog.h"
#include "ui_task_dialog.h"

task_dialog::task_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::task_dialog)
{
    ui->setupUi(this);
     this->setWindowTitle("USER task list__task_dialog.cpp");
    model = new QStandardItemModel(3,3,this);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cata_no"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("task_no"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("task_name"));
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
