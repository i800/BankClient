#ifndef GETACCOUNTSMONEY_H
#define GETACCOUNTSMONEY_H

#include "../Packet.h"

class GetAccountMoneyPacket : public Packet
{
private:
    // Fields.
    quint64 _token;
    quint64 _accountId;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
    virtual PacketHolder specificHandle() const;
public:
    GetAccountMoneyPacket();
    ~GetAccountMoneyPacket();

    // Selector-modifiers.
    quint64& token()
    {
        return _token;
    }

    quint64& accountId()
    {
        return _token;
    }

    // Selectors.
    quint64 token() const
    {
        return _token;
    }

    quint64 accountId() const
    {
        return _token;
    }
};

#endif // GETACCOUNTSMONEY_H
