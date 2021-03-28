#ifndef CREATE_TODOLIST_DIALOG_H
#define CREATE_TODOLIST_DIALOG_H

#include <QDialog>

namespace Ui {
class create_todolist_dialog;
}

class create_todolist_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit create_todolist_dialog(QWidget *parent = nullptr);
    ~create_todolist_dialog();
    QString getdate();
    void set_date(QString get_date_input);

private slots:
    void on_pushButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::create_todolist_dialog *ui;
};

#endif // CREATE_TODOLIST_DIALOG_H
