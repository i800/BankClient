#ifndef USERAUTHPACKET_H
#define USERAUTHPACKET_H

#include "../Packet.h"
#include <QBuffer>

class UserAuthPacket : public Packet
{
private:
    static const char _ID;
    long long _cardNumber;
    QString _password;
    quint32 _terminalId;
    // Interface methods.
    char specificGetID() const;
    PacketHolder specificClone() const;
    QByteArray specificDump() const;
    void specificLoad(QBuffer&);
public:
    UserAuthPacket();
    UserAuthPacket(const long long card, const QString& pass);
    UserAuthPacket(const UserAuthPacket&);
    // Selectors-modifiers.
    long long& card();
    QString& password();
    // Selectors.
    long long card() const;
    const QString& password() const;
};

#endif // UserAuthPacket_H
