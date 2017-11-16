#include "GetAccountMoneyResponsePacket.h"

GetAccountMoneyResponsePacket::GetAccountMoneyResponsePacket()
{}

GetAccountMoneyResponsePacket::~GetAccountMoneyResponsePacket()
{}

char GetAccountMoneyResponsePacket::specificGetID() const
{
    return -2;
}

PacketHolder GetAccountMoneyResponsePacket::specificClone() const
{
    return PacketHolder(new GetAccountMoneyResponsePacket(*this));
}

QByteArray GetAccountMoneyResponsePacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_accountId, sizeof(_accountId));
    data.append((char*)&_amount, sizeof(_amount));
    return data;
}

void GetAccountMoneyResponsePacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_accountId, sizeof(_accountId));
    data.read((char*)&_amount, sizeof(_amount));
}
