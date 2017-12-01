#include "GetCardsPacket.h"

GetCardsPacket::GetCardsPacket():
    _token(0),
    _userId(0),
    _terminalId(0)
{}

GetCardsPacket::GetCardsPacket(const quint64 token, const quint64 userId,
                               const quint32 terminalId):
    _token(token),
    _userId(userId),
    _terminalId(terminalId)
{}

GetCardsPacket::~GetCardsPacket()
{}

char GetCardsPacket::specificGetID() const
{
    return 3;
}

PacketHolder GetCardsPacket::specificClone() const
{
    return PacketHolder(new GetCardsPacket(*this));
}

QByteArray GetCardsPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_userId, sizeof(_userId));
    data.append((char*)&_terminalId, sizeof(_terminalId));
    return data;
}

void GetCardsPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_userId, sizeof(_userId));
    data.read((char*)&_terminalId, sizeof(_terminalId));
}
