#include "easyhttp.h"

EasyHttp::EasyHttp()
{

}


QNetworkReply* EasyHttp::postRequest(QString base, QString params, QString contentType){
    QNetworkRequest *request = new QNetworkRequest(QUrl(base));

    QByteArray postData;
    postData.append(params);
    request->setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    QNetworkAccessManager *man = new QNetworkAccessManager();
    QNetworkReply *reply = man->post(*request,postData);
    return reply;
}


QNetworkReply* EasyHttp::postRequest(QString base, QString params, QString contentType, QMap<QString,QString> headers){
    QNetworkRequest *request = new QNetworkRequest(QUrl(base));

    QByteArray postData;
    postData.append(params);
    request->setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    for(auto e : headers.toStdMap()){
        QByteArray name;
        QByteArray value;
        name.append(e.first);
        value.append(e.second);

        request->setRawHeader(name,value);
    }

    QNetworkAccessManager *man = new QNetworkAccessManager();
    QNetworkReply *reply = man->post(*request,postData);
    return reply;
}


QNetworkReply* EasyHttp::putRequest(QString base, QString params, QString contentType, QMap<QString,QString> headers){
    QNetworkRequest *request = new QNetworkRequest(QUrl(base));

    QByteArray postData;
    postData.append(params);
    request->setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    for(auto e : headers.toStdMap()){
        QByteArray name;
        QByteArray value;
        name.append(e.first);
        value.append(e.second);

        request->setRawHeader(name,value);
    }

    QNetworkAccessManager *man = new QNetworkAccessManager();
    QNetworkReply *reply = man->put(*request,postData);
    return reply;
}

QNetworkReply *EasyHttp::deleteRequest(QString base, QString contentType, QMap<QString, QString> headers)
{
    QNetworkRequest *request = new QNetworkRequest(QUrl(base));

    request->setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    for(auto e : headers.toStdMap()){
        QByteArray name;
        QByteArray value;
        name.append(e.first);
        value.append(e.second);
        request->setRawHeader(name,value);
    }

    QNetworkAccessManager *man = new QNetworkAccessManager();
    QNetworkReply *reply = man->deleteResource(*request);
    return reply;
}


QNetworkReply* EasyHttp::getRequest(QString base){
    QNetworkRequest *request = new QNetworkRequest(QUrl(base));

    QNetworkAccessManager *man = new QNetworkAccessManager();
    QEventLoop loop;
    QNetworkReply *reply = man->get(*request);
    return reply;
}

QNetworkReply* EasyHttp::getRequest(QString base, QMap<QString,QString> headers){
    QNetworkRequest *request = new QNetworkRequest(QUrl(base));



    for(auto e : headers.toStdMap()){
        QByteArray name;
        QByteArray value;
        name.append(e.first);
        value.append(e.second);

        request->setRawHeader(name,value);
    }

    QNetworkAccessManager *man = new QNetworkAccessManager();
    QEventLoop loop;
    QNetworkReply *reply = man->get(*request);
    return reply;
}
