#include "task_dialog.h"
#include "ui_task_dialog.h"
#include"queryoption.h"
#include <QInputDialog>
bool ok;
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
    if(s==""){
        return;
    }else{
    //get data
    q.prepare(s);
    q.exec();
    //create table and display
    model = new QStandardItemModel(q.size(),3,this);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cata_no"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("task_no"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("task_name"));
    ui->tableView->setModel(model);
    int row=0;
    while (q.next()) {
        for(int col = 0; col < 3; col++)
            {
                QModelIndex index
                        = model->index(row,col,QModelIndex());
                    model->setData(index,q.value(col).toString());
            }
        row++;
        }
    }
}


task_dialog::~task_dialog()
{
    delete ui;
}

void task_dialog::on_pushButton_clicked()
{
    //add more task to the specific catalog
    QString catalogI = QInputDialog::getText(this, tr("Which catalog???: "),
                                            tr("Input taskName:"), QLineEdit::Normal,
                                            tr(""), &ok);
       if (ok && !catalogI.isEmpty()){
           qDebug() << catalogI;
           queryOption queryOption;
           queryOption.newTask(catalogI);
           close();
           task_dialog task_dialog;
           task_dialog.setModal(true);
           task_dialog.exec();
       }
       else
           return ;
}

void task_dialog::on_pushButton_2_clicked()
{
    //choice task_no to delete
    //queryOption::delTask(QString taskNo)
    QString taskNo = QInputDialog::getText(this, tr("Which catalog???: "),
                                            tr("Input taskName:"), QLineEdit::Normal,
                                            tr(""), &ok);
       if (ok && !taskNo.isEmpty()){
           queryOption queryOption;
           queryOption.delTask(taskNo);
           close();
           task_dialog task_dialog;
           task_dialog.setModal(true);
           task_dialog.exec();
       }
       else
           return ;
}

void task_dialog::on_pushButton_3_clicked()
{
    //choice task_no to change name
    //queryOption::updateTask(QString newUpdate, QString taskNo)

    QString taskNo = QInputDialog::getText(this, tr("Task_no to update???: "),
                                            tr("Input Task_no to update:"), QLineEdit::Normal,
                                            tr(""), &ok);
   if (ok && !taskNo.isEmpty()){
       QString newUpdate = QInputDialog::getText(this, tr("???: "),
                                               tr("Input new taskName:"), QLineEdit::Normal,
                                               tr(""), &ok);

       if (ok && !newUpdate.isEmpty()){

           queryOption queryOption;
           queryOption.updateTask(newUpdate, taskNo);
           close();
           task_dialog task_dialog;
           task_dialog.setModal(true);
           task_dialog.exec();
       }
       else
           return ;
   }
   else
       return ;

}

void task_dialog::on_pushButton_4_clicked()
{
    //go back to the catalog
    close();
}
