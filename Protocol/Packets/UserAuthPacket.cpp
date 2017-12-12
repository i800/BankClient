#include "UserAuthPacket.h"

const char UserAuthPacket::_ID = 1;

UserAuthPacket::UserAuthPacket():
    _cardNumber(0),
    _password(""),
    _machineId(0)
{}

UserAuthPacket::UserAuthPacket(quint64 card, const QString& pass, quint32 machineId):
    _cardNumber(card),
    _password(pass),
    _machineId(machineId)
{}

quint64& UserAuthPacket::card()
{
    return _cardNumber;
}

QString& UserAuthPacket::password()
{
    return _password;
}

quint32& UserAuthPacket::machineId()
{
    return _machineId;
}

quint64 UserAuthPacket::card() const
{
    return _cardNumber;
}

const QString& UserAuthPacket::password() const
{
    return _password;
}

char UserAuthPacket::specificGetID() const
{
    return _ID;
}

quint32 UserAuthPacket::machineId() const
{
    return _machineId;
}

PacketHolder UserAuthPacket::specificClone() const
{
    return PacketHolder(new UserAuthPacket(*this));
}

QByteArray UserAuthPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_cardNumber, sizeof(_cardNumber));
    std::string str = _password.toStdString();
    data.append(str.c_str(), str.length()+1);
    data.append((char*)&_machineId, sizeof(_machineId));
    return data;
}

void UserAuthPacket::specificLoad(QBuffer& buff)
{
    buff.read((char*)&_cardNumber, sizeof(_cardNumber));
    QByteArray str = buff.readLine(6); // To read 5 bytes.
    _password = QString(str);
    buff.read((char*)&_machineId, sizeof(_machineId));
}
