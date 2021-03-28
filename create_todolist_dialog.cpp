#include "create_todolist_dialog.h"
#include "ui_create_todolist_dialog.h"
#include <QDebug>
#include "queryoption.h"

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
    QString list_name = ui->lineEdit->text();
//    qDebug()<<getdate();
    queryOption queryOption;
    queryOption.newList(list_name, getdate());
    QMessageBox::warning(this,"Create catalog",
                         "the " +list_name+" created.");
    close();


}

void create_todolist_dialog::on_calendarWidget_clicked(const QDate &date)
{
    QString date_input= date.toString("yyyy-MM-dd");
    set_date(date_input);
}

