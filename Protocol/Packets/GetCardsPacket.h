#ifndef GETCARDSPACKET_H
#define GETCARDSPACKET_H

#include "../Packet.h"

class GetCardsPacket : public Packet
{
private:
    // Fields.
    quint64 _token;
    quint64 _userId;
    quint32 _terminalId;
    // MC.
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
    GetCardsPacket();
    GetCardsPacket(const quint64 token, const quint64 userId,
                   const quint32 terminalId);
    ~GetCardsPacket();

    // Selector-modifiers.
    quint64& token()
    {
        return _token;
    }

    quint64& userId()
    {
        return _userId;
    }

    // Selectors.
    quint64 token() const
    {
        return _token;
    }

    quint64 userId() const
    {
        return _userId;
    }
};

#endif // GETCARDSPACKET_H
