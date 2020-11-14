#-------------------------------------------------
#
# Project created by QtCreator 2013-09-18T12:54:50
#
#-------------------------------------------------

QT += core
QT += network
QT -= gui

TARGET = TcpServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../mysqlConnect/include/


SOURCES += mgatcpserver.cpp \
    main.cpp \
    mysqlcommunications.cpp

HEADERS += mgatcpserver.h \
    ServerDefines.h \
    mysqlcommunications.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MGAServerClientMSG/release/ -lMGAServerClientMSG
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MGAServerClientMSG/debug/ -lMGAServerClientMSG
else:unix: LIBS += -L$$OUT_PWD/../MGAServerClientMSG/ -lMGAServerClientMSG

INCLUDEPATH += $$PWD/../MGAServerClientMSG/
DEPENDPATH += $$PWD/../MGAServerClientMSG/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../MGAServerClientMSG/release/libMGAServerClientMSG.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../MGAServerClientMSG/debug/libMGAServerClientMSG.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../MGAServerClientMSG/release/MGAServerClientMSG.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../MGAServerClientMSG/debug/MGAServerClientMSG.lib
else:unix: LIBS += $$OUT_PWD/../MGAServerClientMSG/libMGAServerClientMSG.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../mysqlConnect/lib/release/ -lmysqlcppconn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../mysqlConnect/lib/debug/ -lmysqlcppconn
else:unix: LIBS += -L$$PWD/../mysqlConnect/lib/ -lmysqlcppconn

INCLUDEPATH += $$PWD/../mysqlConnect/include/cppconn
DEPENDPATH += $$PWD/../mysqlConnect/include/cppconn
