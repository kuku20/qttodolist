
#ifndef SEARCHTASK_H
#define SEARCHTASK_H
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

class queryOption
{
    private:
        static QSqlDatabase dbConnection;
        static QString sqlQuery;
        static QString currentID;
        static QSqlQuery qry;
    public:
        void searchTasks(string keys);
};

#endif // SEARCHTASK_H
