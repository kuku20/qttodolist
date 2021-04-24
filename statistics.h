#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDialog>

//#include <QtCharts>
//#include <QChartView>
//#include <QPieSeries>
//#include <QPieSlice>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Statistics;
}

class Statistics : public QDialog
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    ~Statistics();

private:
    QSqlDatabase conn;
    QSqlQuery qry;
    QString sqlQuery;
    Ui::Statistics *ui;
    int inCompleteCount();
    int completeCount();
};

#endif // STATISTICS_H
