#ifndef WIFIAPI_H
#define WIFIAPI_H
#include <QtNetwork>
#include <QList>
class WifiApi
{
public:
    WifiApi(QString apiKey);

    // Data Structures



    struct AccessPoint {
        struct Settings{
            struct Lighting{
                int intensity;
            };
            Lighting* lighting = new Lighting();
        };
        struct Properties{
            QString name;
            QString ipAddress;
            QString lastSeenTime;
            QString firmwareVersion;
            QString hardwareModel;
            bool isPrimaryPoint;
            bool isBridged;
            QString meshResult;
        };
        QString id;
        Settings* settings = new Settings();
        Properties* properties = new Properties();
    };
    struct Station{
        struct Connection {
            bool connected;
            QString ip;
            QString wirelessBand;
        };
        QString macAddress;
        QString apId;
        QString id;
        QString name;
        QString type;
        QString ouiName;
        Connection* connection = new Connection();
    };
    struct StationGroup{
        struct Color{
            double red;
            double green;
            double blue;
        };
        int id;
        QString name;
        QStringList memberStationIDs;
        Color* color = new Color();
    };
    struct System{
        struct Manager {
            QString id;
            QString email;
            bool owner;
        };
        struct PortForwardMapping{
            int wanStartPort;
            int wanEndPort;
            int lanStartPort;
            bool forwardTcp;
            QString ip;
        };
        struct Network{
            struct WAN{
                QList<PortForwardMapping*> portForwardMappings;
                QString dnsMode;
            };

            struct LAN{
                struct PrioritizedStation{
                    QString endTime;
                    QString stationId;
                };
                PrioritizedStation* prioritizedStation = new PrioritizedStation();
                QString ipAddress;
                QString netMask;
                QString dhcpPoolBegin;
                QString dhcpPoolEnd;
            };
            WAN* wan = new WAN();
            LAN* lan = new LAN();
            QString wlanSSID;
        };
        struct GuestWireless{
            bool enabled;
            QString SSID;
            QString welcomeMatEnabled;
            QString pskVisible;
        };
        QList<Station*> devices;
        QString id;
        Network* network = new Network();
        GuestWireless* guestWireless;
        QList<StationGroup*> deviceGroups;
        QList<AccessPoint*> accessPoints;
        QList<Manager*> managers;
    };




    // API Methods

    /*!
     * \brief Fetches data and settings related to the user's WiFi system.
     *
     * Data includes the group ID, and all currently applied settings and properties.
     * \return
     */
     System* fetchSystem();

    /*!
     * \brief Fetches all devices on the network currently.
     *
     *
     * \return
     */
     QList<Station*> fetchDevices(QString groupId);

    /*!
     * \brief fetches connection statuses and IDs of all wifi points within group
     *
     * \return
     */
//     QNetworkReply fetchAccessPointStatus();

     QString getOperationId(QString groupId, QString operationObject, QString opName, QString query);

     QJsonObject getOperationResult(QString operationId, QString endpointSegment);

//     QNetworkReply checkOperation(QString operationElement,QString operationName);

     QJsonObject findValueFromJsonArray(QJsonArray arr, QString key, QString val);

     void prioritizeStation(Station* station, QString endTime, QString groupId);
     void removePrioritizedStation(QString groupId);
    QJsonObject fetchRealtimeMetrics(QString groupId);
     void setApiKey(QString apiKey);
     void pauseStations(QList<Station*> station, QString expiryTimestamp, QString groupId);

private:
    QString API_KEY;
};
Q_DECLARE_METATYPE(WifiApi::Station);
Q_DECLARE_METATYPE(WifiApi::Station*);

#endif // WIFIAPI_H
