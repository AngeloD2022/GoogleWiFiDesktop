#include "apiauthenticator.h"
//#include <QtNetwork>
#include <easyhttp.h>

ApiAuthenticator::ApiAuthenticator()
{

}


QString ApiAuthenticator::getNewAccessToken(QString refreshToken){
    QString base = "https://www.googleapis.com/oauth2/v4/token";
    QString params = "client_id=936475272427.apps.googleusercontent.com&refresh_token="+refreshToken+"&grant_type=refresh_token&scope=https%3A%2F%2Fwww.google.com%2Faccounts%2FOAuthLogin";
//    QEventLoop loop;
    QNetworkReply *reply = EasyHttp::postRequest(base,params,"application/x-www-form-urlencoded");
//    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
//    loop.exec();
    while(!reply->isFinished()){
        qApp->processEvents();
    }

    QString tkn = QJsonDocument::fromJson(reply->readAll()).object()["access_token"].toString();
    return tkn;
}

QString ApiAuthenticator::getApiToken(QString accessToken){
    QString base = "https://oauthaccountmanager.googleapis.com/v1/issuetoken";
    QString params = "app_id=com.google.OnHub&client_id=586698244315-vc96jg3mn4nap78iir799fc2ll3rk18s.apps.googleusercontent.com&device_id=<USER_DEVICE_ID>&hl=en-US&lib_ver=3.3&response_type=token&scope=https%3A%2F%2Fwww.googleapis.com%2Fauth%2Faccesspoints%20https%3A%2F%2Fwww.googleapis.com%2Fauth%2Fclouddevices";
//    QEventLoop loop;
    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+accessToken);
    QNetworkReply *reply = EasyHttp::postRequest(base,params,"application/x-www-form-urlencoded",headers);
//    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
//    loop.exec();
    while(!reply->isFinished()){
        qApp->processEvents();
    }

    QString tkn = QJsonDocument::fromJson(reply->readAll()).object()["token"].toString();
    return tkn;
}

