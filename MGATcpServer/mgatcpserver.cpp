#include "mgatcpserver.h"
#include "QStringList"



MGATcpServer::MGATcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }}

MGATcpServer::~MGATcpServer()
{
    //delete server;
}

void MGATcpServer::MSGHandling(MGAServerClientMSG *msg)
{
    QString password, user, host;
    if((msg->GetMSGType() == EMSGType::eConnectToDB)
       && SerializeUser(msg, &host , &user, &password))
    {
        ConnectToSQLDriver(&host,&user,&password);
    }
    else
    if ((msg->GetMSGType() == EMSGType::eGetUserRole)
        && SerializeLoginUserName(msg ,&host, &user))
    {
        //GetUserRole(&sLoginUserHost,&sLoginUserName);
    }
    else
    if (msg->GetMSGType() == EMSGType::eDisconnectDB)
    {
        DisconnectSQL();
    }
}

void MGATcpServer::newConnection()
{
    qDebug()<<"newConnecton";
    // need to grab the socket
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}


void MGATcpServer::connected()
{

}

void MGATcpServer::disconnected()
{
    socket->close();
}


void MGATcpServer::readyRead()
{
    MGAServerClientMSG msg;
    QByteArray res = socket->readAll();
    msg.GetFromResponse(res);
    MSGHandling(&msg);
}

bool MGATcpServer::SerializeUser(MGAServerClientMSG *msg, QString *host, QString *user, QString *psw)
{
    if(msg->GetBodyLength() < 1) return false;
    try
    {
        *host = msg->GetValue(JSON_ATT_HOST,0);
        *user = msg->GetValue(JSON_ATT_USER,1);
        *psw  = msg->GetValue(JSON_ATT_PWD,2);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool MGATcpServer::SerializeLoginUserName(MGAServerClientMSG *msg, QString *host, QString *user)
{
    if(msg->GetBodyLength() < 1) return false;
    try
    {
        *host = msg->GetValue(JSON_ATT_HOST,0);
        *user = msg->GetValue(JSON_ATT_USER,1);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

void MGATcpServer::DisconnectSQL()
{
    if (StopSQLCommunication())
    {
        MGAServerClientMSG msg(EMSGType::eDisconnectDB);
        msg.InsertInMSGBody(JSON_ATT_DISCONNECTED,"true");
        socket->write(msg.GetMSGAsByteArray());
        socket->flush();
    }
}

void MGATcpServer::ConnectToSQLDriver(QString *qsHost, QString *qsUser, QString *qsPWD)
{
    if(StartSQLCommunication(qsHost,qsUser,qsPWD))
    {
        QString role = GetUserRole(qsHost,qsUser);
        SendClientDBIsConnected(&role);
        emit MYSQLIsConnected();
    }
    else
    {
        qDebug() << "Mysql is NOT connected!";
    }
}

QString  MGATcpServer::GetUserRole(QString *host, QString *user)
{
    std::string str = GetLoginUserRole(host,user);
    return ExtractRoleFromGrantsSQLStatement(&str);
}

void MGATcpServer::SendClientDBIsConnected(QString *role)
{
    MGAServerClientMSG msg(EMSGType::eConnectToDB);
    msg.InsertInMSGBody(JSON_ATT_CONNECTED,"true");
    msg.InsertInMSGBody(JSON_ATT_LOGIN_USER_ROLE,*role);
    socket->write(msg.GetMSGAsByteArray());
    socket->flush();
}

QString MGATcpServer::ExtractRoleFromGrantsSQLStatement(std::string *sqlSmt)
{
    if( sqlSmt->find(SQL_ADMIN_GRANT) != std::string::npos)
    {
        return FIELD_ROLE_ADMIN;
    }
    else
    if (sqlSmt->find(SQL_USER_GRANT) != std::string::npos)
    {
        return FIELD_ROLE_USER;
    }
    return 0;
}
