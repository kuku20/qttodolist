#include "create_todolist_dialog.h"
#include "ui_create_todolist_dialog.h"
#include <QDebug>
#include "queryoption.h"
#include <QInputDialog>
#include"thirdmain.h"

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
//set the input date when create new todolist
void create_todolist_dialog::set_date(QString get_date_input){
    get_date=get_date_input;
}
//get the date
QString create_todolist_dialog::getdate(){
    QString temp = get_date;
    return temp;
}
//create new to-dolist
void create_todolist_dialog::on_pushButton_clicked()
{
    int exist_u = 0;
    QString list_name = ui->lineEdit->text();
    queryOption queryOption;
    exist_u=queryOption.checkIfExist(list_name,"catalog");
    //check if this name cata already exist
    if(exist_u<0){
        QMessageBox::warning(this, "Warning",
                             "This  catalog already exist!!!");
    }
    //check if user not input any
    else if( list_name==""){
        QMessageBox::warning(this, "Warning",
                             "Please input name catalog !!!");
    }
    //check if the forgot to choose the day
    else if(getdate()==""){
        QMessageBox::warning(this, "Warning",
                             "Please choose date!!!");
    }
    else{
        //go to create
        queryOption.newList(list_name, getdate());
        QMessageBox::information(this,"Create catalog",
                                 "the " +list_name+" created.");
        close();

    }
}
//click to the calendar and get the date
void create_todolist_dialog::on_calendarWidget_clicked(const QDate &date)
{
    QString date_input= date.toString("yyyy-MM-dd");
    set_date(date_input);
}

