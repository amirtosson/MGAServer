#ifndef MYSQLCOMMUNICATIONS_H
#define MYSQLCOMMUNICATIONS_H

#include <QString>

#include "mysql_connection.h"
#include "mysql_error.h"
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "cppconn/sqlstring.h"
#include "cppconn/exception.h"
#include "cppconn/prepared_statement.h"


#define SQLQUERY std::string
#define SQLSTRING sql::SQLString

class MySQLCommunications
{
public:
    MySQLCommunications();

public:
    bool StartSQLCommunication(QString *qsHost, QString *qsUser, QString *qsPWD);
    bool StopSQLCommunication();
    std::string GetLoginUserRole(QString *host, QString *user);

private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
};

#endif // MYSQLCOMMUNICATIONS_H
