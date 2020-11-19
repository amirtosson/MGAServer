#ifndef MGASERVERCLIENTMSG_H
#define MGASERVERCLIENTMSG_H

#include <QString>
#include <QStringList>

#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


enum class EMSGType
{
    eConnectToDB,
    eGetUserRole,
    eDisconnectDB,
    eGetUsersList,
    eAddNewUser,
    eDeleteUser,
    eEditUser,
    eGetMembersList,
    eAddNewMember,
    eDeleteMember,
    eEditMember,
    eGetExpList,
    eAddNewExp,
    eDeleteExp,
    eEditExp,
    eGetAppointsList,
    eAddNewAppoint,
    eDeleteAppoint,
    eEditAppoint
};

class MGAServerClientMSG
{
public:
    MGAServerClientMSG(EMSGType eMSGType);
    MGAServerClientMSG();


    void InsertInMSGBody(QString key, QString value);
    EMSGType GetMSGType();
    QByteArray GetMSGAsByteArray();
    bool GetFromResponse(QByteArray jPesponse);
    QString GetValue(QString key, const int col);
    unsigned int GetBodyLength();

private:

    QJsonObject joMSGHeader;
    QJsonArray jaMSGBody;
    EMSGType eCurruntMSGType;

private:
    void SetMSGHeader(QString key, QString value);
    void SetCurrentTypeEnum(QString currentTypeName);

};

#endif // MGASERVERCLIENTMSG_H
