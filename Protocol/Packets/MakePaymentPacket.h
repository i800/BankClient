#ifndef MAKEPAYMENTPACKET_H
#define MAKEPAYMENTPACKET_H

#include "../Packet.h"

class MakePaymentPacket : public Packet
{
private:
    //fields
    quint64 _token;
    quint64 _from;
    quint64 _to;
    quint64 _amount;
    quint32 _terminalId;
    QString _comment;
    //method configuration
    virtual char specificGetID() const;
    virtual PacketHolder specificClone() const;
    virtual QByteArray specificDump() const;
    virtual void specificLoad(QBuffer&);
public:
     MakePaymentPacket();
     MakePaymentPacket(const quint64 token, const quint64 from,
                       const quint64 to, const quint64 amount,
                       const quint32 terminalId,
                       const QString& comment);
     ~MakePaymentPacket();

     //selector-modifiers
     quint64& token()
     {
         return _token;
     }

     quint64& from()
     {
        return _from;
     }

     quint64& to()
     {
         return _to;
     }

     quint64& amount()
     {
         return _amount;
     }

     quint32& terminalId()
     {
         return _terminalId;
     }

     QString& comment()
     {
         return _comment;
     }

     //selectors
     quint64 token() const
     {
         return _token;
     }

     quint64 from() const
     {
        return _from;
     }

     quint64 to() const
     {
         return _to;
     }

     quint64 amount() const
     {
         return _amount;
     }

     quint32 terminalId() const
     {
         return _terminalId;
     }

     const QString& comment() const
     {
         return _comment;
     }
};

#endif // MAKEPAYMENTPACKET_H
