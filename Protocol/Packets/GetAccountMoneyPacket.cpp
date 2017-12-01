#include "GetAccountMoneyPacket.h"

GetAccountMoneyPacket::GetAccountMoneyPacket():
    _token(0),
    _accountId(0),
    _terminalId(0)
{}

GetAccountMoneyPacket::GetAccountMoneyPacket
    (const quint64 token, const quint64 accountId,
     const quint32 terminalId):
    _token(token),
    _accountId(accountId),
    _terminalId(terminalId)
{}

GetAccountMoneyPacket::~GetAccountMoneyPacket()
{}

char GetAccountMoneyPacket::specificGetID() const
{
    return 2;
}

PacketHolder GetAccountMoneyPacket::specificClone() const
{
    return PacketHolder(new GetAccountMoneyPacket(*this));
}

QByteArray GetAccountMoneyPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_accountId, sizeof(_accountId));
    data.append((char*)&_terminalId, sizeof(_terminalId));
    return data;
}

void GetAccountMoneyPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_accountId, sizeof(_accountId));
    data.read((char*)&_terminalId, sizeof(_terminalId));
}
