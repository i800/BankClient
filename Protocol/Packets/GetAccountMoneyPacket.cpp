#include "GetAccountMoneyPacket.h"
#include "GetAccountMoneyResponsePacket.h"
#include "ErrorPacket.h"

GetAccountMoneyPacket::GetAccountMoneyPacket():
    _token(0),
    _machineId(0),
    _accountId(0)
{}

GetAccountMoneyPacket::GetAccountMoneyPacket
    (quint64 token, quint32 machineId, quint64 accountId):
    _token(token),
    _machineId(machineId),
    _accountId(accountId)
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
    data.append((char*)&_machineId, sizeof(_machineId));
    data.append((char*)&_accountId, sizeof(_accountId));
    return data;
}

void GetAccountMoneyPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_machineId, sizeof(_machineId));
    data.read((char*)&_accountId, sizeof(_accountId));
}
