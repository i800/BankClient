#-------------------------------------------------
#
# Project created by QtCreator 2017-10-29T16:11:25
#
#-------------------------------------------------

QT += network
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BankClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    GUI/MainWindow.cpp \
    Logic/Client.cpp \
    App.cpp \
    GUI/AuthFrame.cpp \
    Protocol/Packet.cpp \
    Protocol/Packets/MakePaymentPacket.cpp \
    Protocol/Packets/MakePaymentResponsePacket.cpp \
    Protocol/Packets/UserAuthPacket.cpp \
    Protocol/Packets/GetAccountMoneyPacket.cpp \
    Protocol/Packets/GetAccountMoneyResponsePacket.cpp \
    Protocol/Packets/GetCardsPacket.cpp \
    Protocol/Packets/GetCardsResponsePacket.cpp \
    Protocol/Packets/ErrorPacket.cpp \
    Protocol/Packets/UserAuthResponsePacket.cpp \
    Protocol/Packets/GetPaymentsPacket.cpp \
    Protocol/Packets/GetPaymentsResponsePacket.cpp \
    GUI/TransactionFrame.cpp \
    Protocol/Packets/CancelPeriodicPayment.cpp \
    Protocol/Packets/SuccessPacket.cpp \
    Protocol/Packets/UserLogoutPacket.cpp \
    GUI/PCancellingFrame.cpp \
    Logic/ClientConfiguration.cpp

HEADERS += \
    GUI/MainWindow.h \
    Logic/Client.h \
    App.h \
    GUI/AuthFrame.h \
    Protocol/Packet.h \
    Protocol/PacketsList.h \
    Protocol/Packets/MakePaymentPacket.h \
    Protocol/Packets/MakePaymentResponsePacket.h \
    Protocol/Packets/UserAuthPacket.h \
    Protocol/Packets/GetAccountMoneyPacket.h \
    Protocol/Packets/GetAccountMoneyResponsePacket.h \
    Protocol/Packets/GetCardsPacket.h \
    Protocol/Packets/GetCardsResponsePacket.h \
    Protocol/Packets/ErrorPacket.h \
    Protocol/Packets/UserAuthResponsePacket.h \
    Protocol/Packets/GetPaymentsPacket.h \
    Protocol/Packets/GetPaymentsResponsePacket.h \
    GUI/TransactionFrame.h \
    Protocol/Packets/CancelPeriodicPaymentPacket.h \
    Protocol/Packets/SuccessPacket.h \
    Protocol/Packets/UserLogoutPacket.h \
    GUI/PCancellingFrame.h \
    Logic/ClientConfiguration.h

FORMS += \
    GUI/MainWindow.ui \
    GUI/AuthFrame.ui \
    GUI/TransactionFrame.ui \
    GUI/PCancellingFrame.ui

RESOURCES += \
    resourses.qrc

DISTFILES += \
    WinDeploy.bat
