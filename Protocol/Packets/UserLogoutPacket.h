#ifndef USERLOGOUTPACKET_H
#define USERLOGOUTPACKET_H

#include "../Packet.h"

class UserLogoutPacket : public Packet
{
private:
    quint64 _token;
    quint32 _machineId;
    // NVI methods.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    UserLogoutPacket(const quint64 token = 0, const quint32 machineId = 0);
    virtual ~UserLogoutPacket();

    // Selectors-modifiers.
    inline quint64& token()
    {
        return _token;
    }

    inline quint32& machineId()
    {
        return _machineId;
    }

    // Selectors.
    inline quint64 token() const
    {
        return _token;
    }

    inline quint32 machineId() const
    {
        return _machineId;
    }
};

#endif // USERLOGOUTPACKET_H
