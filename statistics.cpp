#include "statistics.h"
#include "ui_statistics.h"
#include "queryoption.h"
#include "secondmain.h"
#include <QtWidgets>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

Statistics::Statistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);
    showPieChart();
}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::showPieChart() {
    QPieSeries *series = new QPieSeries();
    int res = inCompleteCount()/totalCount();
    qDebug() << "res: " << res;
    series->append("Incomplete Task", 1);
    series->append("Total Task", 2);

    QPieSlice *inComSlide = series->slices().at(0);
    inComSlide->setExploded();
    inComSlide->setLabelVisible();
    inComSlide->setPen(QPen(Qt::darkRed,2));
    inComSlide->setBrush(Qt::red);

    QPieSlice *toTalSlide = series->slices().at(1);
    toTalSlide->setLabelVisible();

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics of Work Effort In 3 Days");
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

double Statistics::inCompleteCount() {
    QSqlDatabase conn = QSqlDatabase::database();
    QSqlQuery qry(conn);
    QString sqlQuery = "SELECT COUNT(*) FROM catalog c JOIN task t "
                       "ON c.list_no = t.list_no "
                       "WHERE c.time BETWEEN date_sub(current_date(), INTERVAL 3 DAY) AND current_date() "
                       "AND c.id = :id AND t.status = :stat";
    qry.prepare(sqlQuery);
    qry.bindValue(":id", queryOption::getID());
    qry.bindValue(":stat", "NO");
    if(qry.exec()){
        qDebug() << "Calculating inCompleteCount...";
    }
    else{
        qDebug() << "ERROR: inCompleteCount failed to return the count";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    qDebug() << "sqlQuery: " << sqlQuery;
    qDebug() << "result for inCompleteCount: " <<qry.result();

    return 0;
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
    int result = qry.value(0).toInt();
    qDebug() << "result for totalCount: " << result;
    return result;
}
