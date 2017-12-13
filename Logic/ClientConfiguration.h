#ifndef CLIENTCONFIGURATION_H
#define CLIENTCONFIGURATION_H

#include <QString>

class ClientConfiguration
{
private:
    QString _configurationFile;
    //configuration parameters
    mutable QString _address;
    mutable quint16 _serverPort;
    //private methods
    void loadConfiguration(const QString&) const;
public:
    ClientConfiguration();
    ClientConfiguration(const QString&);
    ~ClientConfiguration();
    void loadConfiguration(const QString&);
    void saveConfiguration(const QString&) const;
    //selectors-modifiers
    inline QString& address()
    {
        return _address;
    }

    inline quint16& serverPort()
    {
        return _serverPort;
    }

    //selectors
    inline const QString& address() const
    {
        return _address;
    }
    inline quint16 serverPort() const
    {
        return _serverPort;
    }
};

#endif // CLIENTCONFIGURATION_H
