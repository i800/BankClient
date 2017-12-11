#include "GetPaymentsPacket.h"

GetPaymentsPacket::GetPaymentsPacket():
    _token(0),
    _machineId(0),
    _cardNumber(0)
{}

GetPaymentsPacket::GetPaymentsPacket(quint64 token, quint32 machineId, quint64 carnNum):
    _token(token),
    _machineId(machineId),
    _cardNumber(carnNum)
{}

GetPaymentsPacket::PaymentsType GetPaymentsPacket::getTypeById(char id) const
{
    switch(id)
    {
        case 1: return COMMITED_PAYMENTS;
        case 2: return PERIODIC_PAYMENTS;
        default: return UNKNOWN_PAYMENTS;
    }
}

GetPaymentsPacket::~GetPaymentsPacket()
{}

char GetPaymentsPacket::specificGetID() const
{
    return 5;
}

PacketHolder GetPaymentsPacket::specificClone() const
{
    return PacketHolder(new GetPaymentsPacket(*this));
}

QByteArray GetPaymentsPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_machineId, sizeof(_machineId));
    data.append((char*)&_cardNumber, sizeof(_cardNumber));
    return data;
}

void GetPaymentsPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_machineId, sizeof(_machineId));
    data.read((char*)&_cardNumber, sizeof(_cardNumber));
}
