#include "statistics.h"
#include "ui_statistics.h"
#include "queryoption.h"

Statistics::Statistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistics)
{
    conn = QSqlDatabase::database();
    QFont font;
    QSqlQuery q(conn);
    qry.operator=(q);

    ui->setupUi(this);
    QPieSeries *series = new QPieSeries();
    series->append("Incomplete Tasks", inCompleteCount());
    series->append("Complete Tasks", completeCount());

    QPieSlice *slice0 = series->slices().at(0);
    font.setPixelSize(14);
    slice0->setLabelVisible(true);
    slice0->setLabelFont(font);
    slice0->setPen(QPen(Qt::darkRed,2));
    slice0->setBrush(Qt::red);

    QPieSlice *slice1 = series->slices().at(1);
    slice1->setLabelVisible(true);
    slice1->setLabelFont(font);
    slice1->setPen(QPen(Qt::darkBlue,2));
    slice1->setBrush(Qt::blue);

    QChart *chart = new QChart();
    font.setPixelSize(20);
    chart->setTitleFont(font);
    chart->addSeries(series);
    chart->setTitle("Statistics of Work Effort In Past 3 Days");

    QChartView *cView = new QChartView(chart);
    cView->setParent(ui->horizontalFrame);
}

Statistics::~Statistics()
{
    delete ui;
}

int Statistics::inCompleteCount() {
    sqlQuery = "SELECT COUNT(*) as taskCount FROM catalog c JOIN task t "
               "ON c.list_no = t.list_no "
               "WHERE c.time BETWEEN date_sub(current_date(), INTERVAL 3 DAY) AND current_date() "
               "AND c.id = :id AND t.status = :stat";
    qry.prepare(sqlQuery);
    qry.bindValue(":id", queryOption::getID());
    qry.bindValue(":stat", "NO");
    if(qry.exec()){
        qDebug() << "Counting incompleted tasks...";
    }
    else{
        qDebug() << "ERROR: inCompleteCount failed to return the count";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    qry.next();
    return qry.value("taskCount").toInt();
}

int Statistics::completeCount() {
    sqlQuery = "SELECT COUNT(*) as taskCount FROM catalog c JOIN task t "
               "ON c.list_no = t.list_no "
               "WHERE c.time BETWEEN date_sub(current_date(), INTERVAL 3 DAY) AND current_date() "
               "AND c.id = :id AND t.status = :stat";
    qry.prepare(sqlQuery);
    qry.bindValue(":id", queryOption::getID());
    qry.bindValue(":stat", "YES");
    if(qry.exec()){
        qDebug() << "Counting completed tasks...";
    }
    else{
        qDebug() << "ERROR: completeCount failed to return the count";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    qry.next();
    return qry.value("taskCount").toInt();
}
