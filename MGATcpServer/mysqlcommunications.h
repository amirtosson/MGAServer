#ifndef MYSQLCOMMUNICATIONS_H
#define MYSQLCOMMUNICATIONS_H

#include <QString>
#include <QStringList>

#include "mysql_connection.h"
#include "mysql_error.h"
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "cppconn/sqlstring.h"
#include "cppconn/exception.h"
#include "cppconn/prepared_statement.h"


#define ADD_NEW_USER(N,H,P,R)\
        res = stmt->executeQuery(SQLSTRING(SQLQUERY("CREATE USER '") + SQLQUERY(N)+ SQLQUERY("'@'")+ SQLQUERY(H)+ SQLQUERY("' IDENTIFIEd BY '")+ SQLQUERY(P) + SQLQUERY("'; ")));

#define ADD_DELETE_USER(N,H)\
        res = stmt->executeQuery(SQLSTRING(SQLQUERY("DROP USER '") + SQLQUERY(N)+ SQLQUERY("'@'")+ SQLQUERY(H)+ SQLQUERY("' IDENTIFIEd BY '")+ SQLQUERY("'; ")));

#define GET_USERS_LIST()\
        res = stmt->executeQuery(SQLSTRING(SQLQUERY("SELECT user, host FROM  mysql.user;")));

#define CREATE_STATEMENT()\
        stmt = con->createStatement();

#define GET_MEMBERS_LIST()\
        res = stmt->executeQuery(SQLSTRING(SQLQUERY("SELECT * FROM MGA_Database.MGA_members;")));

#define SQLQUERY std::string
#define SQLSTRING sql::SQLString

class MySQLCommunications
{
public:
    MySQLCommunications();

public:
    bool StartSQLCommunication(QString *qsHost, QString *qsUser, QString *qsPWD);
    bool StopSQLCommunication();
    bool SQLAddNewUer(QString *qsHost, QString *qsUser, QString *qsPWD, QString *qsRole);
    bool SQLDeleteUer(QString *qsHost, QString *qsUser);

    QStringList SQLGetUsersListAsQStringList();
    QStringList SQLGetMemberssListAsQStringList();

    std::string GetLoginUserRole(QString *host, QString *user);

private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
};

#endif // MYSQLCOMMUNICATIONS_H
