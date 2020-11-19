#include "mgaserverclientmsg.h"
#include <QDebug>

#define MSG_CONNECT_TOSQL_TYPE_NAME         "CTSQLD"
#define MSG_DISCONNECT_DB_TYPE_NAME         "DCSQLD"
#define MSG_GET_USER_ROLE_TYPE_NAME         "GURSQL"

#define MSG_GET_USERS_LIST_TYPE_NAME        "GULSQL"
#define MSG_ADD_NEW_USER_TYPE_NAME          "ANUSQL"
#define MSG_DELETE_USER_TYPE_NAME           "DUFSQL"
#define MSG_EDIT_USER_TYPE_NAME             "EUFSQL"

#define MSG_GET_MEMBERS_LIST_TYPE_NAME      "GMFSQL"
#define MSG_ADD_NEW_MEMBER_TYPE_NAME        "ANMSQL"
#define MSG_DELETE_MEMBER_TYPE_NAME         "DMFSQL"
#define MSG_EDIT_MEMBER_TYPE_NAME           "EMFSQL"

#define MSG_GET_EXP_LIST_TYPE_NAME          "GEXSQL"
#define MSG_ADD_NEW_EXP_TYPE_NAME           "AEXSQL"
#define MSG_DELETE_EXP_TYPE_NAME            "DEXSQL"
#define MSG_EDIT_EXP_TYPE_NAME              "EEXSQL"

#define MSG_GET_APPOINTS_LIST_TYPE_NAME     "GAPSQL"
#define MSG_ADD_NEW_APPOINT_TYPE_NAME       "AAPSQL"
#define MSG_DELETE_APPOINT_TYPE_NAME        "DAPSQL"
#define MSG_EDIT_APPOINT_TYPE_NAME          "EAPSQL"

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
    case EMSGType::eGetUsersList:
        SetMSGHeader(MSG_ID_KEY,MSG_GET_USERS_LIST_TYPE_NAME);
        break;
    case EMSGType::eAddNewUser:
           SetMSGHeader(MSG_ID_KEY,MSG_ADD_NEW_USER_TYPE_NAME);
           break;
    case EMSGType::eEditUser:
           SetMSGHeader(MSG_ID_KEY,MSG_EDIT_USER_TYPE_NAME);
           break;
    case EMSGType::eDeleteUser:
           SetMSGHeader(MSG_ID_KEY,MSG_DELETE_USER_TYPE_NAME);
           break;
    case EMSGType::eGetMembersList:
           SetMSGHeader(MSG_ID_KEY,MSG_GET_MEMBERS_LIST_TYPE_NAME);
           break;
    case EMSGType::eAddNewMember:
           SetMSGHeader(MSG_ID_KEY,MSG_ADD_NEW_MEMBER_TYPE_NAME);
           break;
    case EMSGType::eEditMember:
           SetMSGHeader(MSG_ID_KEY,MSG_EDIT_MEMBER_TYPE_NAME);
           break;
    case EMSGType::eDeleteMember:
           SetMSGHeader(MSG_ID_KEY,MSG_DELETE_USER_TYPE_NAME);
           break;
    case EMSGType::eGetExpList:
           SetMSGHeader(MSG_ID_KEY,MSG_GET_EXP_LIST_TYPE_NAME);
           break;
    case EMSGType::eAddNewExp:
           SetMSGHeader(MSG_ID_KEY,MSG_ADD_NEW_EXP_TYPE_NAME);
           break;
    case EMSGType::eEditExp:
           SetMSGHeader(MSG_ID_KEY,MSG_EDIT_EXP_TYPE_NAME);
           break;
    case EMSGType::eDeleteExp:
           SetMSGHeader(MSG_ID_KEY,MSG_DELETE_EXP_TYPE_NAME);
           break;
    case EMSGType::eGetAppointsList:
           SetMSGHeader(MSG_ID_KEY,MSG_GET_APPOINTS_LIST_TYPE_NAME);
           break;
    case EMSGType::eAddNewAppoint:
           SetMSGHeader(MSG_ID_KEY,MSG_ADD_NEW_APPOINT_TYPE_NAME);
           break;
    case EMSGType::eEditAppoint:
           SetMSGHeader(MSG_ID_KEY,MSG_EDIT_APPOINT_TYPE_NAME);
           break;
    case EMSGType::eDeleteAppoint:
           SetMSGHeader(MSG_ID_KEY,MSG_DELETE_APPOINT_TYPE_NAME);
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
    else if(currentTypeName == MSG_GET_USERS_LIST_TYPE_NAME)
    {
       eCurruntMSGType =  EMSGType::eGetUsersList;
    }
    else if(currentTypeName == MSG_ADD_NEW_USER_TYPE_NAME)
    {
      eCurruntMSGType =  EMSGType::eAddNewUser;
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

