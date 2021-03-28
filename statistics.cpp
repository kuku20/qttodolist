#include "statistics.h"
#include "ui_statistics.h"
#include "queryoption.h"
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

Statistics::Statistics(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);

}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::showPieChart() {
    QPieSeries *series = new QPieSeries();
    double res = inCompleteCount()/totalCount();
    series->append("Incomplete Task", res);
    series->append("Total Task", (1-res));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics of Work Effort In 3 Days");
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
    resize(420,300);
}

double Statistics::inCompleteCount() {
    QSqlDatabase conn = QSqlDatabase::database();
    QSqlQuery qry(conn);
    QString sqlQuery = "";
    double result;
    return result;
}

double Statistics::totalCount() {
    QSqlDatabase conn = QSqlDatabase::database();
    QSqlQuery qry(conn);
    QString sqlQuery = "SELECT COUNT(*) FROM catalog c JOIN task t "
                       "ON c.list_no = t.list_no "
                       "WHERE c.time BETWEEN date_sub(current_date(), INTERVAL 3 DAY) AND current_date() "
                       "AND c.id = :id";
    qry.prepare(sqlQuery);
    qry.bindValue(":id", queryOption::getID());
    if(qry.exec()){
        qDebug() << "Calculating totalCount...";
    }
    else{
        qDebug() << "ERROR: totalCount failed to return the count";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    qDebug() << "sqlQuery: " << sqlQuery;
    double result = qry.value(0).Double;
    qDebug() << "result for totalCount: " << result;
    return result;
}
