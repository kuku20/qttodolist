#ifndef CREATENEWACOUNT_H
#define CREATENEWACOUNT_H

#include <QDialog>

namespace Ui {
class createNewAcount;
}

class createNewAcount : public QDialog
{
    Q_OBJECT

public:
    explicit createNewAcount(QWidget *parent = nullptr);
    ~createNewAcount();

private slots:
    void on_pushButton_clicked();

private:
    Ui::createNewAcount *ui;
};

#endif // CREATENEWACOUNT_H
