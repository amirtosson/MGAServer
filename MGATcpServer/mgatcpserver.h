#ifndef MGATCPSERVER_H
#define MGATCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "mgaserverclientmsg.h"
#include "ServerDefines.h"
#include "mysqlcommunications.h"


class MGATcpServer : public QObject, private MySQLCommunications
{
    Q_OBJECT
public:
    explicit MGATcpServer(QObject *parent = 0);
    ~MGATcpServer();
    void MSGHandling(MGAServerClientMSG *msg);


signals:
    void MYSQLIsConnected();

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void newConnection();




private:
    QTcpServer *server;
    QTcpSocket *socket;

private:
    bool SerializeUser(MGAServerClientMSG *msg, QString *host, QString *user, QString *psw);
    bool SerializeLoginUserName(MGAServerClientMSG *msg, QString *host, QString *user);
    void DisconnectSQL();
    void ConnectToSQLDriver(QString *qsHost, QString *qsUser, QString *qsPWD);
    QString GetUserRole(QString *host, QString *user);
    void SendClientDBIsConnected(QString *role);
    //mysql has no role-based feature, so this function is to convert grants to role
    QString ExtractRoleFromGrantsSQLStatement(std::string *sqlSmt);
};

#endif // MGATCPSERVER_H
