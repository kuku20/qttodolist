#include "create_todolist_dialog.h"
#include "ui_create_todolist_dialog.h"
#include <QDebug>
#include "queryoption.h"
#include <QInputDialog>

create_todolist_dialog::create_todolist_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_todolist_dialog)
{
    ui->setupUi(this);
}

create_todolist_dialog::~create_todolist_dialog()
{
    delete ui;
}
QString get_date;
void create_todolist_dialog::set_date(QString get_date_input){
    get_date=get_date_input;
}
QString create_todolist_dialog::getdate(){
    QString temp = get_date;
    return temp;
}
void create_todolist_dialog::on_pushButton_clicked()
{
    int exist_u = 0;
    QString list_name = ui->lineEdit->text();
//    qDebug()<<getdate();
    queryOption queryOption;
    exist_u=queryOption.checkIfExist(list_name,"catalog");
    if(exist_u<0 or list_name=="" or getdate()==""){
        QMessageBox::warning(this, "Warning",
                                 "This  catalog already exist!!!");
        }
    else
    {
        queryOption.newList(list_name, getdate());
        QMessageBox::information(this,"Create catalog",
                             "the " +list_name+" created.");
//        QMessageBox::StandardButton reply;
//        while(reply != QMessageBox::No){
//            reply = QMessageBox::question(this, "Add Task", "Do you want to add task"
//                                                            "to this ?",
//                                           QMessageBox::Yes|QMessageBox::No);
//             if (reply == QMessageBox::Yes) {
//               qDebug() << "Yes was clicked";
//               //add task
//               bool ok;
//               QString catalogI = QInputDialog::getText(this, tr("Which catalog???: "),
//                                                       tr("Input taskName:"), QLineEdit::Normal,
//                                                       tr(""), &ok);
//                  if (ok && !catalogI.isEmpty()){
//                      qDebug() << catalogI;
//                      queryOption.newTask(catalogI);
//                      close();
//                  }
//                  else{
//                      qDebug() << catalogI;
//                      return ;
//                  }
//    //           QApplication::quit();
//             } else {
//               qDebug() << "Yes was *not* clicked";
//             }

//        }
        close();

    }


}

void create_todolist_dialog::on_calendarWidget_clicked(const QDate &date)
{
    QString date_input= date.toString("yyyy-MM-dd");
    set_date(date_input);
}

