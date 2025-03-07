#ifndef QUERYOPTION_H
#define QUERYOPTION_H

#include<QtSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

// This class as database management system contains several functions to send the query to the mysql database
// these function allows the system creating tables, creating todo list and task items, update names, and delete todo list or task items
// developers need to create an object to use the function in other files
// and connect to the database before make an instance of this class
// @note the current version will cause error running on MAC OS environment
// @note accessID function needs to be called before call other functions to avoid error happens

class queryOption
{
    private:
        static QSqlDatabase dbConnection;
        static QString sqlQuery;
        static QString currentID;
        static QSqlQuery qry;
        static QString currentUser;
        static QString inputNumber;
    public:
        //headers
        void static setCon();
        void static setCon(QSqlDatabase conn);
        void static createUser();
        void static createCatalog();
        void static createTaskTable();
        void newList(QString list_name, QString dateInsert);
        void newTask( QString task_name);
        QString genListNo();
        QString genTaskNo();
        void static accessID(QString user_id);
        static QString getID();
        QString getLists();
        QString getTasks();
        void delTask(QString taskNo);
        void delList(QString listNo);
        void updateTask(QString newUpdate, QString taskNo,QString kindof);
        void updateList(QString newUpdate, QString listNo);
        void static accessUser(QString user_name);
        static QString getUser();
        void static setInputNo(QString inNum);
        static QString getInputNo();
        int checkIfExist(QString option, QString table);
        QString searchTasks(QString keys);
        QString searchCata(QString keys,QString kindof);
};

#endif // QUERYOPTION_H
