#include "GetCardsResponsePacket.h"

GetCardsResponsePacket::GetCardsResponsePacket():
    _amount(0)
{}

GetCardsResponsePacket::GetCardsResponsePacket
    (const quint8 amount, const QMap<quint64, quint8>& cards):
    _amount(amount)
{
    QMapIterator<quint64, quint8> iter(cards);
    while (iter.hasNext())
    {
        iter.next();
        _cards.insert(iter.key(), iter.value());
    }
}

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

    for (unsigned i(0); i < _amount; ++i)
    {
        quint64 temp64(0);
        quint8 temp8(0);
        data.read((char*)&temp64, sizeof(quint64));
        data.read((char*)&temp8, sizeof(quint8));
        _cards.insert(temp64, temp8);
    }
}
