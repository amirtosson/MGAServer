#include "mgaserverclientmsg.h"
#include <QDebug>

#define MSG_CONNECT_TOSQL_TYPE_NAME         "CTSQLD"
#define MSG_DISCONNECT_DB_TYPE_NAME         "DCSQLD"
#define MSG_GET_USER_ROLE_TYPE_NAME         "GURSQL"


//keys
#define MSG_ID_KEY                          "MSG_ID"


MGAServerClientMSG::MGAServerClientMSG(EMSGType eMSGType)
    :eCurruntMSGType(eMSGType)
{
    switch (eCurruntMSGType) {
    case EMSGType::eConnectToDB:
        SetMSGHeader(MSG_ID_KEY,MSG_CONNECT_TOSQL_TYPE_NAME);
        break;
    case EMSGType::eGetUserRole:
        SetMSGHeader(MSG_ID_KEY,MSG_GET_USER_ROLE_TYPE_NAME);
        break;
    case EMSGType::eDisconnectDB:
        SetMSGHeader(MSG_ID_KEY,MSG_DISCONNECT_DB_TYPE_NAME);
        break;
    default:
        break;
    }
}

MGAServerClientMSG::MGAServerClientMSG()
{

}


void MGAServerClientMSG::SetMSGHeader(QString key, QString value)
{
    joMSGHeader.insert(key,value);
}

void MGAServerClientMSG::SetCurrentTypeEnum(QString currentTypeName)
{
    if(currentTypeName == MSG_CONNECT_TOSQL_TYPE_NAME)
    {
       eCurruntMSGType =  EMSGType::eConnectToDB;
    }
    else if(currentTypeName == MSG_GET_USER_ROLE_TYPE_NAME)
    {
       eCurruntMSGType =  EMSGType::eGetUserRole;
    }
    else if(currentTypeName == MSG_DISCONNECT_DB_TYPE_NAME)
    {
       eCurruntMSGType =  EMSGType::eDisconnectDB;
    }
}

void MGAServerClientMSG::InsertInMSGBody(QString key, QString value)
{
    QJsonObject jObj;
    jObj.insert(key,value);
    jaMSGBody.push_back(jObj);
}

EMSGType MGAServerClientMSG::GetMSGType()
{
    return eCurruntMSGType;
}

QByteArray MGAServerClientMSG::GetMSGAsByteArray()
{
    QJsonArray msg;
    msg.push_back(joMSGHeader);
    for (int i = 0 ; i<jaMSGBody.size();++i )
    {
           msg.push_back(jaMSGBody[i]);
    }
    QJsonDocument jsDoc(msg);
    QString jsString = QString::fromLatin1(jsDoc.toJson());
    return  jsString.toLatin1();
}

bool MGAServerClientMSG::GetFromResponse(QByteArray jPesponse)
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(jPesponse);
    QJsonArray jsonArray = jsonResponse.array();

    // get header
    QStringList kL = jsonArray[0].toObject().keys();
    QString idKey = kL[0];
    QString sVal = jsonArray[0].toObject().value(idKey).toString();
    SetMSGHeader(idKey, sVal);
    SetCurrentTypeEnum(sVal);
    // get body
    jsonArray.removeAt(0);
    jaMSGBody = jsonArray;
    return true;
}

QString MGAServerClientMSG::GetValue(QString key, const int col)
{
    return jaMSGBody[col].toObject().value(key).toString();
}

 unsigned int MGAServerClientMSG::GetBodyLength()
{
     return  jaMSGBody.size();
}

