#ifndef THIRDMAIN_H
#define THIRDMAIN_H

#include <QDialog>
#include "secondmain.h"
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

namespace Ui {
class thirdmain;
}

class thirdmain : public QDialog
{
    Q_OBJECT

public:
    explicit thirdmain(QWidget *parent = nullptr);

    ~thirdmain();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::thirdmain *ui;
    QStandardItemModel *model;
};

#endif // THIRDMAIN_H
