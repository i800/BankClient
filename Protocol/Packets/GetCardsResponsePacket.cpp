#include "GetCardsResponsePacket.h"

GetCardsResponsePacket::GetCardsResponsePacket()
{}

GetCardsResponsePacket::~GetCardsResponsePacket()
{}

char GetCardsResponsePacket::specificGetID() const
{
    return -3;
}

PacketHolder GetCardsResponsePacket::specificClone() const
{
    return PacketHolder(new GetCardsResponsePacket(*this));
}

QByteArray GetCardsResponsePacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_amount, sizeof(_amount));

    QMapIterator<quint64, quint8> iter(_cards);
    while (iter.hasNext())
    {
        iter.next();
        data.append((char*)&iter.key(), sizeof(iter.key()));
        data.append((char*)&iter.value(), sizeof(iter.value()));
    }

    return data;
}

void GetCardsResponsePacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_amount, sizeof(_amount));

    QMapIterator<quint64, quint8> iter(_cards);
    while (iter.hasNext())
    {
        iter.next();
        data.read((char*)&iter.key(), sizeof(iter.key()));
        data.read((char*)&iter.value(), sizeof(iter.value()));
    }
}
