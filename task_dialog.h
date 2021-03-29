#ifndef TASK_DIALOG_H
#define TASK_DIALOG_H

#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

namespace Ui {
class task_dialog;
}

class task_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit task_dialog(QWidget *parent = nullptr);
    ~task_dialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::task_dialog *ui;
    QStandardItemModel *model;
};

#endif // TASK_DIALOG_H
