#include "GetPaymentsPacket.h"

GetPaymentsPacket::GetPaymentsPacket():
    _token(0),
    _cardNumber(0),
    _terminalId(0)
{}

GetPaymentsPacket::GetPaymentsPacket(const quint64 token, const quint64 cardNumber,
                                     const quint32 terminalId):
    _token(token),
    _cardNumber(cardNumber),
    _terminalId(terminalId)
{}

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
    data.append((char*)&_cardNumber, sizeof(_cardNumber));
    data.append((char*)&_terminalId, sizeof(_terminalId));
    return data;
}

void GetPaymentsPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_cardNumber, sizeof(_cardNumber));
    data.read((char*)&_terminalId, sizeof(_terminalId));
}
