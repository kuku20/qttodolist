
#include <queryOption.h>
#include <QMessageBox>
#include <QDebug>

QSqlDatabase queryOption::dbConnection;
QString queryOption::sqlQuery;
QString queryOption::currentID;
QSqlQuery queryOption::qry;

// return the specific tasks lists
// @param key: the input to search for specific tasks
// @return none
void quertOption::searchTasks(string keys){
    QSqlQuery query(db);
 //make query for search key from table
    sqlQuery = "SELECT task.list_no, task.item_no, task.item_name, catalog.id"
				"FROM catalog AND task"
				"WHERE task.item_name =" + keys + "OR catalog.list_name = " + keys;
    qry.prepare(sqlQuery);
    if(qry.exec()){
        qDebug() << "Display the Results\n";
    }
    else{
        qDebug() << "ERROR: Failed to find any tasks\n";
    }
	
    while (qry.next()) {
        for(int i = 0; i < 4; i++){
            qDebug() << qry.value(i).toString();
        }
         qDebug() << "";
    }
}
