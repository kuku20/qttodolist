#include <QtTest>

// add necessary includes here
#include "queryoption.h"
#include "create_todolist_dialog.h"
#include "mainwindow.h"
#include "secondmain.h"
#include "statistics.h"
#include "task_dialog.h"
#include "thirdmain.h"

class unitTestCase2 : public QObject
{
    Q_OBJECT

public:
    unitTestCase2();
    ~unitTestCase2();
    queryOption qryAction;
    QSqlDatabase db;

private slots:
    void test_setCon();
    void test_createTables();
    void test_newUser();
    void test_userInfo();
    void test_createList();
    void test_getList();
};

unitTestCase2::unitTestCase2()
{
}

unitTestCase2::~unitTestCase2()
{
}

void unitTestCase2::test_setCon()
{
    QSqlDatabase conn;
    queryOption::setCon();
    conn = QSqlDatabase::database();
    QVERIFY(conn.isOpen());
}
void unitTestCase2::test_createTables()
{
    qryAction.createUser();
    db = QSqlDatabase::database();
    QStringList tableName = db.tables();
    for(int i = 0; i < tableName.size(); i++) {
        QVERIFY(tableName.at(i) == "catalog" || tableName.at(i) == "users" || tableName.at(i) == "task");
    }
}
void unitTestCase2::test_newUser()
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

void unitTestCase2::test_userInfo() {
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

void unitTestCase2::test_createList() {
    db = QSqlDatabase::database();
    QSqlQuery qry(db);
    QString sqlQuery;
    QString testList = "testadmin_list";
    QString testDate = "2021-04-26";
    QString retList = "";
    qryAction.newList(testList, testDate);

    sqlQuery =	"SELECT list_no, list_name, time "
                "FROM Catalog "
                "WHERE id = :userID "
                "ORDER BY list_no desc";
    qry.prepare(sqlQuery);
    qry.bindValue(":userID", queryOption::getID());
    QVERIFY(qry.exec());
    if(qry.next()) {
        retList = qry.value(1).toString();
    }
    QVERIFY(retList == testList);
}

void unitTestCase2::test_getList() {
    QString getSql = qryAction.getLists();
    QVERIFY(getSql != "");
}
QTEST_APPLESS_MAIN(unitTestCase2)

#include "tst_unittestcase2.moc"
