#include "mysqlcommunications.h"

MySQLCommunications::MySQLCommunications()
{

}

bool MySQLCommunications::StartSQLCommunication(QString *qsHost, QString *qsUser, QString *qsPWD)
{
    try
    {
        driver = get_driver_instance();
        con = driver->connect(qsHost->toStdString(), qsUser->toStdString(), qsPWD->toStdString());
    }
    catch (sql::SQLException e)
    {
        return false;
    }
    return con->isValid();
}

bool MySQLCommunications::StopSQLCommunication()
{
    try
    {
        con->close();
    }
    catch (sql::SQLException e)
    {
        return false;
    }
    return true;
}

std::string MySQLCommunications::GetLoginUserRole(QString *host, QString *user)
{
    stmt = con->createStatement();
    res = stmt->executeQuery(SQLSTRING(SQLQUERY("SHOW GRANTS for ") +SQLQUERY(user->toStdString()) + SQLQUERY("@") +SQLQUERY(host->toStdString())));
    std::string str;
    if(res->rowsCount() > 0)
    {
        while (res->next())
        {
            try
            {
                str += res->getString(1).asStdString();
            }
            catch (...)
            {
                return "";
            }

        }
        if (str.size() < 1) return "";
    }
    return str;
}
