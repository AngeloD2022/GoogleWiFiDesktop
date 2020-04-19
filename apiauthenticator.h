#ifndef APIAUTHENTICATOR_H
#define APIAUTHENTICATOR_H

#include <QObject>
#include <QtNetwork>

class ApiAuthenticator : public QObject
{
    Q_OBJECT


public:
    ApiAuthenticator();
    QString getNewAccessToken(QString refreshToken);
    QString getApiToken(QString accessToken);
private:
    QString accessToken;
    QString deviceId = "INSERT_DEVICEID_HERE";
};

#endif // APIAUTHENTICATOR_H
