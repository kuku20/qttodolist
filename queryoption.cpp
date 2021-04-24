#include "queryoption.h"
#include <QMessageBox>
#include <QDebug>

QSqlDatabase queryOption::dbConnection;
QString queryOption::sqlQuery;
QString queryOption::currentID,queryOption::inputNumber,queryOption::currentUser;
QSqlQuery queryOption::qry;

/**
 * @brief setCon A static funciton to connect to the database
 * @param none
 */
void queryOption::setCon() {
    dbConnection = QSqlDatabase::addDatabase("QMYSQL");
    dbConnection.setHostName("127.0.0.1");
    dbConnection.setDatabaseName("test");
    dbConnection.setUserName("root");
    dbConnection.setPassword("");
    dbConnection.setPort(3306);
    if(dbConnection.open()) {
        qDebug() << "Database connected!";
        QSqlQuery q(dbConnection);
        qry.operator=(q);
    }
    else {
        qDebug() << "ERROR: setCon could not connect to database.";
        qDebug() << "ERROR: " << dbConnection.lastError().text();
    }
}
/**
 * @brief queryOption::setCon set connection to the database
 * @param conn
 */
void queryOption::setCon(QSqlDatabase conn) {
    if(conn.open()) {
        dbConnection = conn;
        qDebug() << "Database connected!";
        QSqlQuery q(dbConnection);
        qry.operator=(q);
    }
    else
        qDebug() << "ERROR: " << conn.lastError().text();

}

// create users table in mysql database, it will also create catalog and task table
// id is the primary key of this table
// @param none
// @return none
void queryOption::createUser() {
    sqlQuery = "CREATE TABLE IF NOT EXISTS users ("
        "email varchar(50) NOT NULL, password varchar(50) NOT NULL, username VARCHAR(50) NOT NULL, id int(11) NOT NULL AUTO_INCREMENT, "
        "PRIMARY KEY(id))";
    qry.prepare(sqlQuery);
    if(qry.exec())
        qDebug() << "User table created!";
    else {
        qDebug() << "ERROR: createUser query failed.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    //create catalog table
    createCatalog();
}

// create catalog table for all the todo list, it will also create task table
// list_no is the primary key of this table
// @param none
// @return none
void queryOption::createCatalog() {
    sqlQuery =	"CREATE TABLE IF NOT EXISTS Catalog ("
                "id INT NOT NULL, list_no INT NOT NULL, list_name VARCHAR(50) NOT NULL, time DATE NOT NULL,noti VARCHAR(3) NOT NULL,"
                "PRIMARY KEY(list_no));";
    qry.prepare(sqlQuery);
    if(qry.exec())
        qDebug() << "Catalog table created!";
    else
        qDebug() << "ERROR: createCatalog query failed.";
    //create task table
    createTaskTable();
}

// create task table for all the tasks inside todo lists
// task_no is the primary key of this table
// @param none
void queryOption::createTaskTable() {
    sqlQuery =	"CREATE TABLE IF NOT EXISTS Task ("
                "list_no INT NOT NULL, task_no INT NOT NULL, task_name VARCHAR(50) NOT NULL,"
                "status VARCHAR(3) NOT NULL, PRIMARY KEY(task_no));";
    qry.prepare(sqlQuery);
    if(qry.exec())
        qDebug() << "Task table created!";
    else
        qDebug() << "ERROR: createTaskTable query failed.";
}

// create a new todo list in catalog table
// @param list_name the name of the todo list that input by user
// @param dateInsert the date that user choose
void queryOption::newList(QString list_name, QString dateInsert) {
    QString listNo = genListNo();
    sqlQuery = "INSERT INTO Catalog (id, list_no, list_name, time) VALUES(:id, :no, :name, :date)";
    qry.prepare(sqlQuery);
    qry.bindValue(":id", getID());
    qry.bindValue(":no", listNo);
    qry.bindValue(":name", list_name);
    qry.bindValue(":date", dateInsert);
    if(qry.exec())
        qDebug() << "new to-do list created!";
    else {
        qDebug() << "ERROR: newList function failed to create the to-do list.";
        qDebug() << "ERROR:" << qry.lastError().text();
    }
}

// create a new task in the task table
// @param task_name the name of the task input by user
void queryOption::newTask(QString task_name) {
    QString taskNo = genTaskNo();
    sqlQuery = "INSERT INTO Task VALUES(:listNo, :taskNo, :name, :stat)";
    qry.prepare(sqlQuery);
    qry.bindValue(":listNo", getInputNo());
    qry.bindValue(":taskNo", taskNo);
    qry.bindValue(":name", task_name);
    qry.bindValue(":stat", "NO");
    if(qry.exec())
        qDebug() << "new task created!";
    else {
        qDebug() << "ERROR: newTask function failed to create the task.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
}


// generate the list number which has not been used in the catalog table, and always check the available number from 0
// @return the generated number
QString queryOption::genListNo() {
    int genNo = 0;
    do {
        genNo++;
        sqlQuery = "SELECT list_no FROM Catalog where list_no = :bNum";
        qry.prepare(sqlQuery);
        qry.bindValue(":bNum", genNo);
        if(qry.exec())
            qDebug() << "Generating list_no...";
        else {
            qDebug() << "ERROR: genListNo function failed.";
            qDebug() << "ERROR: " << qry.lastError().text();
        }
    } while (qry.next());
    return QString::number(genNo);
}

// generate the task number which has not been used in the task table, and always check the available number from 0
// @param none
// @return the generated number
QString queryOption::genTaskNo() {
    int genNo = 0;
    do {
        genNo++;
        sqlQuery = "SELECT task_no FROM Task where task_no = :bNum";
        qry.prepare(sqlQuery);
        qry.bindValue(":bNum", genNo);
        if(qry.exec())
            qDebug() << "Generating task_no...";
        else {
            qDebug() << "ERROR: genTaskNo function failed.";
            qDebug() << "ERROR: " << qry.lastError().text();
        }
    } while (qry.next());
    return QString::number(genNo);
}

// A static function that set and store the current user id to the system
// @param user_id the current user id
// @return none
void queryOption::accessID(QString user_id) {
    currentID = user_id;
}

// A static function that return the user id to identify the current user
// @param none
// @return temp current user id
QString queryOption::getID() {
    QString temp = currentID;
    return temp;
}

// display all the todo list the current user has in the catalog table
// @param none
// @return sqlQuery for geting list table
QString queryOption::getLists() {
    sqlQuery =	"SELECT list_no, list_name, time "
                "FROM Catalog "
                "WHERE id = :userID";
    qry.prepare(sqlQuery);
    qry.bindValue(":userID", getID());
    if(qry.exec())
        qDebug() << "Displaying the catalog table...";
    else {
        qDebug() << "ERROR: getLists failed to display the catalog table.";
        qDebug() << "ERROR: " << qry.lastError().text();
        return "";
    }
    qDebug() << "list_no\nlist_name\ntime\n";
    while (qry.next()) {
        for (int i = 0; i < 3; i++) {
            qDebug() <<  qry.value(i).toString();
        }
        qDebug() << "";
    }
    qDebug() << "Finished displaying the catalog table.";
    sqlQuery = "SELECT list_no, list_name, time "
                "FROM Catalog "
                "WHERE id = " + getID();
    return sqlQuery;
}

// display all the task inside the todo list that current user has in the task table
// @return sqlQuery for getting the task table
QString queryOption::getTasks() {
    sqlQuery = "SELECT task.list_no, task.task_no, task.task_name, task.status, catalog.id "
        "FROM catalog "
        "JOIN task "
        "ON catalog.list_no = task.list_no "
        "AND task.list_no = :listNo "
        "AND catalog.id = :userID";
    qry.prepare(sqlQuery);
    qry.bindValue(":listNo", getInputNo());
    qry.bindValue(":userID", getID());
    if(qry.exec())
        qDebug() << "Displaying the task table...";
    else {
        qDebug() << "ERROR: getTasks failed to display the task table.";
        qDebug() << "ERROR: " << qry.lastError().text();
        return "";
    }
    qDebug() << "list_no\ntask_no\ntask_name\nuser_id";
    while (qry.next()) {
        for (int i = 0; i < 5; i++) {
            qDebug() <<  qry.value(i).toString();
        }
        qDebug() << "";
    }
    sqlQuery = "SELECT task.list_no, task.task_no, task.task_name, task.status, catalog.id "
        "FROM catalog "
        "JOIN task "
        "ON catalog.list_no = task.list_no "
        "AND task.list_no = " + getInputNo();
    return sqlQuery;
}

// delete one task in the list table
// @param taskNo the specific item that current user want to delete
// @return none
void queryOption::delTask(QString taskNo) {
    sqlQuery = "DELETE FROM task WHERE task_no = :taskNo";
    qry.prepare(sqlQuery);
    qry.bindValue(":taskNo", taskNo);
    if(qry.exec())
        qDebug() << "One task has been deleted";
    else {
        qDebug() << "ERROR: delTask failed to delete a task in task table.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
}

//delete the todo list including the task inside the list
//@param listNo the specific todo list number that current user want to delete
//@return none
void queryOption::delList(QString listNo) {
    //disable safe mode
    sqlQuery = "SET SQL_SAFE_UPDATES = 0;";
    qry.prepare(sqlQuery);
    if(qry.exec())
        qDebug() << "The safe mode has been turned off";
    else {
        qDebug() << "ERROR: delList failed to turn off the safe mode.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    //delete the items
    sqlQuery = "DELETE FROM task WHERE list_no = " + listNo;
    qry.prepare(sqlQuery);
    if(qry.exec())
        qDebug() << "The list has been deleted from the catalog table";
    else {
        qDebug() << "ERROR: delList failed to delete the list.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    sqlQuery = "DELETE FROM catalog WHERE list_no = " + listNo;
    qry.prepare(sqlQuery);
    if(qry.exec())
        qDebug() << "The tasks inside the list are deleted from the task table";
    else {
        qDebug() << "ERROR: delList failed to delete the tasks.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    //enable safe mode
    sqlQuery = "SET SQL_SAFE_UPDATES = 1;";
    qry.prepare(sqlQuery);
    if(qry.exec())
        qDebug() << "The safe mode has been turned on.";
    else {
        qDebug() << "ERROR: delList failed to turn on the safe mode.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
}

// update a task's name in the task table
// @param newUpdate the name to replace the old name as new name for item name
// @param taskNo the target task item number that needs to update
// @param kindof update either the task name or task status
// @return none
void queryOption::updateTask(QString newUpdate, QString taskNo,QString kindof) {
    if(kindof=="name"){
    sqlQuery =	"UPDATE task SET task_name = :update WHERE task_no = :num";
    }
    else{
    sqlQuery =	"UPDATE task SET status = :update WHERE task_no = :num";
    }
    qry.prepare(sqlQuery);
    qry.bindValue(":update", newUpdate);
    qry.bindValue(":num", taskNo);
    if(qry.exec())
        qDebug() << "The task name has been changed.";
    else {
        qDebug() << "ERROR: updateTask failed to update the task name.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
}

// update a todo list name in the catalog table
// @param newUpdate the name to replace the old name as new name for todo list name
// @param listNo the taget todo list number that needs to update
// @return none
void queryOption::updateList(QString newUpdate, QString listNo) {
    sqlQuery = "UPDATE catalog SET list_name = :update WHERE list_no = :num";
    if(newUpdate=="YES" || newUpdate=="NO"){
       sqlQuery = "UPDATE catalog SET noti = :update WHERE list_no = :num";
    }
    qry.prepare(sqlQuery);
    qry.bindValue(":update", newUpdate);
    qry.bindValue(":num", listNo);
    if(qry.exec())
        qDebug() << "The catalog_database has been changed.";
    else {
        qDebug() << "ERROR: updateList failed to update the task name.";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
}

/**
 * @brief queryOption::accessUser store the current user in the variable
 * @param user_name current user name
 */
void queryOption::accessUser(QString user_name) {
    currentUser = user_name;
    qDebug()<< "current user: " << currentUser;
}

/**
 * @brief queryOption::getUser return current user name
 * @return temp as the current user
 */
QString queryOption::getUser() {
    QString temp = currentUser;
    return temp;
}

/**
 * @brief queryOption::setInputNo set the listNo or taskNo for action
 * @param inNum user input either the listNo or taskNo
 */
void queryOption::setInputNo(QString inNum) {
    inputNumber = inNum;
}

/**
 * @brief queryOption::getInputNo get the inputnumber that user typed
 * @return temp as inputNumber
 */
QString queryOption::getInputNo() {
    QString temp = inputNumber;
    return temp;
}

//* check if the user, email, or catalog name exist
//* @param location
//* @param option
//* @return exist
int queryOption::checkIfExist(QString option, QString table) {
    sqlQuery="SELECT * FROM " + table;
    //depend on the table to select
    //if table is user sqlQuery.length()==19
    //if table is catalog sqlQuery.length()==21
    qry.prepare(sqlQuery);
    qry.exec();
    int exist = 0;
     while (qry.next()) {
         QString usernamedb = qry.value(2).toString();
         QString emaildb = qry.value(0).toString();
         QString test = qry.value(1).toString();
         if(option==usernamedb ||
                 sqlQuery.length()==19 && option==emaildb ||
                 sqlQuery.length()>25 && option==test){
             exist -= 1;
             return exist;
         }
     }
    return exist;
}

// return the specific tasks lists
// @param key the input to search for specific tasks
// @param kindof search the list either by date or by name
// @return sqlQuery to search the lists
QString queryOption::searchCata(QString keys,QString kindof){
    //this is for the sqlQuery when the user insert to seach cata
    if(kindof=="type"){
        sqlQuery = "SELECT *  "
                       "FROM catalog "
                       "WHERE catalog.list_name LIKE :key AND catalog.id = :id";
            qry.prepare(sqlQuery);
            qry.bindValue(":key", "%" + keys + "%");
            qry.bindValue(":id", getID());
    }
    else{
        //this is for the sqlQuery when the user click the calendar
        sqlQuery = "SELECT *  "
                   "FROM catalog "
                   "WHERE catalog.time = :key "
                   "AND catalog.id = :id";
        qry.prepare(sqlQuery);
        qry.bindValue(":key", keys);
        qry.bindValue(":id", getID());
    }
    if(qry.exec()){
        qDebug() << "Display the Results";
    }
    else{
        qDebug() << "ERROR: Failed to find any tasks";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    while (qry.next()) {
        for(int i = 0; i < 4; i++){
            qDebug() << qry.value(i).toString();
        }
         qDebug() << "";
    }
    //this is for the sqlQuery when the user insert to seach cata
    if(kindof=="type"){
        sqlQuery = "SELECT *  "
                       "FROM catalog "
                       "WHERE catalog.list_name LIKE '%" + keys +
                       "%' AND catalog.id = " + getID();
            qDebug() << "second query sent: " << sqlQuery;
    }
    else{
        //this is for the sqlQuery when the user click the calendar
        sqlQuery = "SELECT *  "
                   "FROM catalog "
                   "WHERE catalog.time = '" + keys +
                   "' AND catalog.id = " + getID();
    }
    return sqlQuery;
}

/**
 * @brief queryOption::searchTasks search the specific task that contain the key
 * @param keys the keywords search in the table
 * @return sqlQuery to search the tasks
 */
QString queryOption::searchTasks(QString keys){
    //make query for search key from table
    sqlQuery = "SELECT catalog.id, task.list_no, task.task_no, task.task_name, task.status "
               "FROM catalog, task "
               "WHERE task.task_name LIKE :key "
               "AND catalog.id = :id "
               "AND catalog.list_no = task.task_no";
    qry.prepare(sqlQuery);
    qry.bindValue(":key", "%" + keys + "%");
    qry.bindValue(":id", getID());
    if(qry.exec()){
        qDebug() << "Display the Results";
    }
    else{
        qDebug() << "ERROR: Failed to find any list in task";
        qDebug() << "ERROR: " << qry.lastError().text();
    }
    while (qry.next()) {
        for(int i = 0; i < 4; i++){
            qDebug() << qry.value(i).toString();
        }
         qDebug() << "";
    }
    sqlQuery = "SELECT catalog.id, task.list_no, task.task_no, task.task_name, task.status "
               "FROM catalog, task "
               "WHERE task.task_name LIKE '%" + keys +
               "%' AND catalog.id = " + getID() +
               " AND catalog.list_no = task.task_no";
    return sqlQuery;
}
