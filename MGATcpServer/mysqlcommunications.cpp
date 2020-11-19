#include "mysqlcommunications.h"
#include <QDebug>

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

bool MySQLCommunications::SQLAddNewUer(QString *qsHost, QString *qsUser, QString *qsPWD, QString *qsRole)
{
    try
    {
        std::string str;
        CREATE_STATEMENT()
        ADD_NEW_USER(qsUser->toStdString(),qsHost->toStdString(),qsPWD->toStdString(), qsRole->toStdString())
    }
    catch (sql::SQLException e)
    {
        qDebug()<< e.what();
        qDebug()<< "e.what()";
        return true;
    }
    return  true;
}

bool MySQLCommunications::SQLDeleteUer(QString *qsHost, QString *qsUser)
{
    try
    {
        std::string str;
        CREATE_STATEMENT()
        ADD_DELETE_USER(qsUser->toStdString(),qsHost->toStdString())
    }
    catch (sql::SQLException e)
    {
        qDebug()<< e.what();
        return true;
    }
    return  true;
}

QStringList MySQLCommunications::SQLGetUsersListAsQStringList()
{
    CREATE_STATEMENT()
    GET_USERS_LIST()
    QStringList usersList;
    if(res->rowsCount() > 0)
    {
        while (res->next())
        {
            std::string str;
            try
            {
                str += res->getString(1).asStdString();
                str += "#-#";
                str += res->getString(2).asStdString();

            }
            catch (...)
            {
                //return ;
            }
            usersList.append(str.c_str());
        }
        //if (usersList.size() < 1) return "";
    }
    return usersList;
}

QStringList MySQLCommunications::SQLGetMemberssListAsQStringList()
{
    CREATE_STATEMENT()
    GET_MEMBERS_LIST()
    QStringList membersList;
    if(res->rowsCount() > 0)
    {
        while (res->next())
        {
            std::string str;
            try
            {
                //TODO: use colounm label instead
                str += res->getString(1).asStdString();
                str += "#-#";
                str += res->getString(2).asStdString();
                str += "#-#";
                str += res->getString(3).asStdString();
                str += "#-#";
                str += res->getString(2).asStdString();
                str += "#-#";
                str += res->getString(5).asStdString();
                str += "#-#";
                str += res->getString(6).asStdString();
            }
            catch (...)
            {
                //return ;
            }
            membersList.append(str.c_str());
        }
    }
    return membersList;
}

std::string MySQLCommunications::GetLoginUserRole(QString *host, QString *user)
{
    CREATE_STATEMENT()
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
