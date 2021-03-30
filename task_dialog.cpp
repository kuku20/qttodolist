#include "task_dialog.h"
#include "ui_task_dialog.h"
#include "queryoption.h"
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

    QString s = queryOption.getTasks();
    if(s == "")
        return;
    else {
    //get data
    q.prepare(s);
    q.exec();
    //create table and display
    model = new QStandardItemModel(q.size(),4,this);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cata_no"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("task_no"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("task_name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("complete"));
    ui->tableView->setModel(model);
    int row=0;
    while (q.next()) {
        for(int col = 0; col < 4; col++)
            {
                    qDebug() << "status: " << q.value(col).toString();
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
            //call the query to add data to list
           queryOption queryOption;
           queryOption.newTask(catalogI);
           close();
           //close and reopen to refesh the display
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
    QString taskNo = QInputDialog::getText(this, tr("Which catalog???: "),
                                            tr("Input taskNo:"), QLineEdit::Normal,
                                            tr(""), &ok);
       if (ok && !taskNo.isEmpty()){
           queryOption queryOption;
           queryOption.delTask(taskNo);
           close();
           //close and reopen to refesh the display
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
    QString taskNo = QInputDialog::getText(this, tr("Task_no to update???: "),
                                            tr("Input Task_no to update:"), QLineEdit::Normal,
                                            tr(""), &ok);
   if (ok && !taskNo.isEmpty()){
       QString newUpdate = QInputDialog::getText(this, tr("???: "),
                                               tr("Input new taskName:"), QLineEdit::Normal,
                                               tr(""), &ok);
       if (ok && !newUpdate.isEmpty()){
           queryOption queryOption;
           queryOption.updateTask(newUpdate, taskNo,"name");
           close();
           //close and reopen to refesh the display
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
//click the task to set it complete or not
void task_dialog::on_tableView_clicked(const QModelIndex &index )
{
    int set=index.column();
    if(set==3){
        qDebug()<<index.data(1);
        QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "DONE??", "Are you finish this task?",
                                           QMessageBox::Yes|QMessageBox::No);
             if (reply == QMessageBox::Yes) {
               qDebug() << "Yes was clicked";
               queryOption queryOption;
               queryOption.updateTask("YES", index.siblingAtColumn(1).data().toString(),"complete");
                //close and reopen to refesh the display
               close();
               task_dialog task_dialog;
               task_dialog.setModal(true);
               task_dialog.exec();

             } else {
               qDebug() << "Yes was *not* clicked";
               queryOption queryOption;
               queryOption.updateTask("NO", index.siblingAtColumn(1).data().toString(),"complete");
                //close and reopen to refesh the display
               close();
               task_dialog task_dialog;
               task_dialog.setModal(true);
               task_dialog.exec();
             }
    }
}


