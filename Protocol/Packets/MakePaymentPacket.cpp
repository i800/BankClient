#include "MakePaymentPacket.h"

MakePaymentPacket::MakePaymentPacket()
{}

MakePaymentPacket::MakePaymentPacket(const quint64 token, const quint64 from,
                                     const qint64 to, const qint64 amount,
                                     const quint32 machinelId, quint64 periodicity,
                                     const QString& comment, const QString& technicalComment):
    _token(token),
    _from(from),
    _to(to),
    _amount(amount),
    _machineId(machinelId),
    _periodicity(periodicity),
    _comment(comment),
    _technicalComment(technicalComment)
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
    data.append((char*)&_machineId, sizeof(_machineId));
    data.append((char*)&_from, sizeof(_from));
    data.append((char*)&_to, sizeof(_to));
    data.append((char*)&_amount, sizeof(_amount));
    data.append((char*)&_periodicity, sizeof(_periodicity));
    std::string str = _comment.toStdString();
    data.append(str.c_str(), str.length()+1);
    str = _technicalComment.toStdString();
    data.append(str.c_str(), str.length()+1);
    return data;
}

void MakePaymentPacket::specificLoad(QBuffer& data)
{
    data.read((char*)&_token, sizeof(_token));
    data.read((char*)&_machineId, sizeof(_machineId));
    data.read((char*)&_from, sizeof(_from));
    data.read((char*)&_to, sizeof(_to));
    data.read((char*)&_amount, sizeof(_amount));
    data.read((char*)&_periodicity, sizeof(_periodicity));
    QByteArray strings = data.readAll();
    _comment = QString(strings.data());
    strings.remove(0, _comment.size()+1);
    _technicalComment = QString(strings.data());
}
