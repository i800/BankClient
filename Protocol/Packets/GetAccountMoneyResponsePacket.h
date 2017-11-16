#ifndef GETACCOUNTMONEYRESPONSEPACKET_H
#define GETACCOUNTMONEYRESPONSEPACKET_H

#include "../Packet.h"

class GetAccountMoneyResponsePacket : public Packet
{
private:
    // Fields.
    quint64 _accountId;
    quint64 _amount;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    GetAccountMoneyResponsePacket();
    GetAccountMoneyResponsePacket(const quint64 accountId, const quint64 amount);
    ~GetAccountMoneyResponsePacket();
};

#endif // GETACCOUNTMONEYRESPONSEPACKET_H
