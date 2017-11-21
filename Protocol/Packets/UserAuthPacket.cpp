#include "UserAuthPacket.h"

const char UserAuthPacket::_ID = 1;

UserAuthPacket::UserAuthPacket():
    _cardNumber(0),
    _password("")
{}

UserAuthPacket::UserAuthPacket(long long card, QString pass):
    _cardNumber(card),
    _password(pass)
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
    return _ID;
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
    return data;
}

void UserAuthPacket::specificLoad(QBuffer& buff)
{
    buff.read((char*)&_cardNumber, sizeof(_cardNumber));
    _password = QString(buff.readAll());
}
