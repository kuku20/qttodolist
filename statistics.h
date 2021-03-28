#ifndef STATISTICS_H
#define STATISTICS_H

#include <QMainWindow>

namespace Ui {
class Statistics;
}

class Statistics : public QMainWindow
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    ~Statistics();
    void showPieChart();
    double inCompleteCount();
    double totalCount();
private:
    Ui::Statistics *ui;
};

#endif // STATISTICS_H
