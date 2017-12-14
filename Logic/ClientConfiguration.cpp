#include "ClientConfiguration.h"
#include <QSettings>

//default configuration
ClientConfiguration::ClientConfiguration():
    _configurationFile("BankClientConfig.ini")
{
    loadConfiguration(_configurationFile);
}

ClientConfiguration::ClientConfiguration(const QString& filename):
    _configurationFile(filename)
{
    loadConfiguration(filename);
}

ClientConfiguration::~ClientConfiguration()
{
    saveConfiguration(_configurationFile);
}

void ClientConfiguration::loadConfiguration(const QString& filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    _address = settings.value("address", "127.0.0.1"/*"platinium.ddns.net"*/).toString();
    _serverPort = settings.value("port", 45654).toInt();
}

void ClientConfiguration::loadConfiguration(const QString& filename) const
{
    QSettings settings(filename, QSettings::IniFormat);
    _address = settings.value("address", "localhost").toString();
    _serverPort = settings.value("port", 45654).toInt();
}

void ClientConfiguration::saveConfiguration(const QString& filename) const
{
    QSettings settings(filename, QSettings::IniFormat);
    settings.setValue("address", _address);
    settings.setValue("port", _serverPort);
}
