#ifndef PACKET_H
#define PACKET_H

#include <QBuffer>
#include <unordered_map>

namespace Protocol
{
    class Packet
    {
    private:
        static std::unordered_map<char, Packet*> _packetsMap;
        static bool _isInited;
        static void init();
        // specific methods for each packets
        virtual char specificGetID() const = 0;
        virtual Packet* specificClone() const = 0;
        virtual QByteArray specificDump() const = 0;
        virtual void specificLoad(QBuffer&) = 0;
        virtual void specificHandle() const = 0;
    public:
        class BadPacket;
        virtual ~Packet() {}
        static Packet* getPacket(char id);
        static bool isPacket(const QByteArray&);
        static char getPacketId(const QByteArray&);
        static unsigned short getPacketSize(const QByteArray&);
        // NVI (NonVirtualInterface)
        QByteArray dump() const;
        void load(QByteArray& arr);

        inline char getID() const
        {
            return specificGetID();
        }

        inline Packet* clone() const
        {
            return specificClone();
        }

        inline void handle() const
        {
            return specificHandle();
        }
    };

    class Packet::BadPacket
    {
    private:
        const char* _info;
        BadPacket(const BadPacket&) = delete;
        BadPacket& operator=(const BadPacket&) = delete;

        inline const char* info() const
        {
            return _info;
        }

    public:
        BadPacket(const char* = "Invalid packet.");
        ~BadPacket() {}
        void diagnose() const;
    };

}

#endif // PACKET_H
