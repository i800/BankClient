#include "MakePaymentPacket.h"

MakePaymentPacket::MakePaymentPacket()
{}

MakePaymentPacket::MakePaymentPacket(const quint64 token, const quint64 from,
                                     const quint64 to, const quint64 amount,
                                     const quint32 terminalId,
                                     const QString &comment):
    _token(token),
    _from(from),
    _to(to),
    _amount(amount),
    _terminalId(terminalId),
    _comment(comment)
{}

MakePaymentPacket::~MakePaymentPacket()
{}

char MakePaymentPacket::specificGetID() const
{
    return 4;
}

PacketHolder MakePaymentPacket::specificClone() const
{
    return PacketHolder(new MakePaymentPacket(*this));
}

QByteArray MakePaymentPacket::specificDump() const
{
    QByteArray data;
    data.append((char*)&_token, sizeof(_token));
    data.append((char*)&_terminalId, sizeof(_terminalId));
    data.append((char*)&_from, sizeof(_from));
    data.append((char*)&_to, sizeof(_to));
    data.append((char*)&_amount, sizeof(_amount));
    std::string str = _comment.toStdString();
    data.append(str.c_str(), str.length()+1);
    return data;
}

void MakePaymentPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_terminalId, sizeof(_terminalId));
    data.read((char*)&_from, sizeof(_from));
    data.read((char*)&_to, sizeof(_to));
    data.read((char*)&_amount, sizeof(_amount));
    _comment = QString(data.readAll());
}
