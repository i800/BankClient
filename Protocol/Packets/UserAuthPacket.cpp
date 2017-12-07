#include "UserAuthPacket.h"

UserAuthPacket::UserAuthPacket():
    _cardNumber(0),
    _password("")
{}

UserAuthPacket::UserAuthPacket(const long long card, const quint32 terminalId,
                               const QString& pass):
    _cardNumber(card),
    _password(pass),
    _terminalId(terminalId)
{}

UserAuthPacket::UserAuthPacket(const UserAuthPacket& pack):
    _cardNumber(pack._cardNumber),
    _password(pack._password)
{}

long long& UserAuthPacket::card()
{
    return _cardNumber;
}

QString& UserAuthPacket::password()
{
    return _password;
}

long long UserAuthPacket::card() const
{
    return _cardNumber;
}

const QString& UserAuthPacket::password() const
{
    return _password;
}

char UserAuthPacket::specificGetID() const
{
    return 1;
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
    data.append(str.c_str(), str.length() + 1);
    data.append((char*)&_terminalId, sizeof(_terminalId));
    return data;
}

void UserAuthPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_cardNumber, sizeof(_cardNumber));
    QByteArray str = data.readLine(6); //read 5 bytes
    _password = QString(str);
    data.read((char*)&_terminalId, sizeof(_terminalId));
}
