#ifndef EASYHTTP_H
#define EASYHTTP_H
#include <QtNetwork>

class EasyHttp
{
public:
    EasyHttp();

    static QNetworkReply* postRequest(QString base, QString params, QString contentType);
    static QNetworkReply* postRequest(QString base, QString params, QString contentType, QMap<QString,QString> headers);
    static QNetworkReply* getRequest(QString base);
    static QNetworkReply* getRequest(QString base, QMap<QString,QString> headers);
    static QNetworkReply* putRequest(QString base, QString params, QString contentType, QMap<QString,QString> headers);
    static QNetworkReply* deleteRequest(QString base, QString contentType, QMap<QString,QString> headers);
};

#endif // EASYHTTP_H
