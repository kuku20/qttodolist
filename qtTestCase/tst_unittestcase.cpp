#include <QtTest>

// add necessary includes here
#include "queryoption.h"
#include "create_todolist_dialog.h"
#include "mainwindow.h"
#include "secondmain.h"
#include "statistics.h"
#include "task_dialog.h"
#include "thirdmain.h"

class unitTestCase : public QObject
{
    Q_OBJECT

public:
    unitTestCase();
    ~unitTestCase();
    queryOption qryAction;
    QSqlDatabase db;


private slots:
    void test_setCon();
    void test_createTables();
    void test_newUser();
    void test_userInfo();
};

unitTestCase::unitTestCase()
{
}

unitTestCase::~unitTestCase()
{
}

void unitTestCase::test_setCon()
{
    QSqlDatabase conn;
    queryOption::setCon();
    conn = QSqlDatabase::database();
    QVERIFY(conn.isOpen());
}
void unitTestCase::test_createTables()
{
    qryAction.createUser();
    db = QSqlDatabase::database();
    QStringList tableName = db.tables();
    for(int i = 0; i < tableName.size(); i++) {
        QVERIFY(tableName.at(i) == "catalog" || tableName.at(i) == "users" || tableName.at(i) == "task");
    }
}
void unitTestCase::test_newUser()
{
    QString sqlQuery;
    db = QSqlDatabase::database();
    QSqlQuery qry(db);
    int exist_u = 0;
    int exist_e = 0;
    QString new_user = "testadmin";
    QString new_pass = "testadmin";
    QString new_email = "testadmin@gmail.com";
    exist_u = qryAction.checkIfExist(new_user,"users");
    exist_e = qryAction.checkIfExist(new_email,"users");
    if(exist_u < 0 || exist_e < 0 ){
        QSKIP("username: testadmin needs to be removed for this test.");
    }
    else {
        sqlQuery = "INSERT INTO users(username, email, password) "
                   "VALUES (:username, :email, :password)";
        qry.prepare(sqlQuery);
        qry.bindValue(":username", new_user);
        qry.bindValue(":email", new_email);
        qry.bindValue(":password", new_pass);
        QVERIFY(qry.exec());
    }
}

void unitTestCase::test_userInfo() {
    QString usernamedb;
    QString passdb;
    db = QSqlDatabase::database();
    QSqlQuery qry(db);
    qry.exec("SELECT * FROM users");
    while(qry.next()) {
        usernamedb = qry.value(2).toString();
        passdb = qry.value(1).toString();
        if("testadmin" == usernamedb && "testadmin" == passdb){
            queryOption::accessID(qry.value(3).toString());
            queryOption::accessUser(usernamedb);
            break;
        }
    }
    QVERIFY(queryOption::getUser() == "testadmin");
}
QTEST_APPLESS_MAIN(unitTestCase)

#include "tst_unittestcase.moc"
