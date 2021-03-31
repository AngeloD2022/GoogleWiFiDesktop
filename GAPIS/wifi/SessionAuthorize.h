//
// Created by Angelo DeLuca on 3/22/21.
//

#ifndef GOOGLEWIFIDESKTOPCLIENT_SESSIONAUTHORIZE_H
#define GOOGLEWIFIDESKTOPCLIENT_SESSIONAUTHORIZE_H

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include "SessionContext.h"


class SessionAuthorize : public QObject {
Q_OBJECT

public:

    explicit SessionAuthorize(QObject *parent = nullptr) : QObject(parent) {};


    void authorize_ctx(QString refresh_token) {

        QUrl access_endpoint("https://www.googleapis.com/oauth2/v4/token");

        QUrlQuery query;

        query.addQueryItem("client_id", "936475272427.apps.googleusercontent.com");
        query.addQueryItem("grant_type", "refresh_token");
        query.addQueryItem("refresh_token", refresh_token);

        access_endpoint.setQuery(query);

        QNetworkRequest req;

        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        req.setUrl(access_endpoint);

        QNetworkAccessManager *manager = new QNetworkAccessManager(parent());

        connect(manager, &QNetworkAccessManager::finished, [this](QNetworkReply *reply) {
            second_step(reply);
        });

        manager->post(req, "");
    }

signals:

    void auth_finished();

private:

    void second_step(QNetworkReply *reply) {
        // first, get the access token..

        QJsonObject at_object = QJsonDocument::fromJson(reply->readAll()).object();

        QString token = at_object["access_token"].toString();
        int expires = at_object["expires_in"].toInt();

        // Set its shared static value...
        SessionContext::at_content = token;
        SessionContext::at_exp = expires;

        QUrl token_endpoint("https://oauthaccountmanager.googleapis.com/v1/issuetoken");

        QUrlQuery query;

        query.addQueryItem("app_id", "com.google.OnHub");
        query.addQueryItem("client_id", "586698244315-vc96jg3mn4nap78iir799fc2ll3rk18s.apps.googleusercontent.com");
        query.addQueryItem("hl", "en-US");
        query.addQueryItem("lib_ver", "3.3");
        query.addQueryItem("response_type", "token");
        query.addQueryItem("scope",
                           "https://www.googleapis.com/auth/accesspoints https://www.googleapis.com/auth/clouddevices");

        token_endpoint.setQuery(query);

        QNetworkRequest req;

        req.setRawHeader("Authorization", QString("Bearer " + token).toUtf8());
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        req.setUrl(token_endpoint);

        QNetworkAccessManager *manager = new QNetworkAccessManager(parent());

        // When done, set the other shared value and emit signal of completion...
        connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
            get_foyer(reply);
        });

        manager->post(req, "");
    }

    void get_foyer(QNetworkReply *reply) {
        QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();

        SessionContext::ft_content = obj["token"].toString();
        SessionContext::ft_exp = obj["expires_in"].toInt();

        emit auth_finished();
    }


};

#endif //GOOGLEWIFIDESKTOPCLIENT_SESSIONAUTHORIZE_H
