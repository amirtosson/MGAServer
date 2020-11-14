#ifndef MGASERVERCLIENTMSG_H
#define MGASERVERCLIENTMSG_H

#include <QString>
#include <QStringList>

#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>




////MSG header key
//#define MSG_TYPE_KEY                        "MSGTYP"
////MSG header value
//#define CONNECT_TO_SQL_MSG_ID               "CTSQLD"
//#define GET_USERS_LIST_MSG_ID               "GUSRSL"
//#define GET_MEMBERS_LIST_MSG_ID             "GMEMSL"
enum class EMSGType
{
    eConnectToDB,
    eGetUserRole,
    eDisconnectDB
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
