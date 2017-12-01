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
    data.append((char*)&_terminalId, sizeof(_terminalId));
    std::string str = _password.toStdString();
    data.append(str.c_str(), str.length() + 1);
    return data;
}

void UserAuthPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_cardNumber, sizeof(_cardNumber));
    data.read((char*)&_terminalId, sizeof(_terminalId));
    _password = QString(data.readAll());
}
