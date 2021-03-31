//
// Created by Angelo DeLuca on 3/30/21.
//

#ifndef GOOGLEWIFIDESKTOPCLIENT_FOYERCLIENT_H
#define GOOGLEWIFIDESKTOPCLIENT_FOYERCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "SessionContext.h"

class FoyerClient : public QObject {
Q_OBJECT

public:
    QNetworkAccessManager *manager;

    explicit FoyerClient(QObject *parent = nullptr) : QObject(parent) {
        manager = new QNetworkAccessManager();
        connect(manager, &QNetworkAccessManager::finished, this, &FoyerClient::finished);
    }

    void get(QNetworkRequest request){
        request.setRawHeader("Authorization",QString("Bearer " + SessionContext::ft_content).toUtf8());
        manager->get(request);
    }

    void post(QNetworkRequest request, QByteArray content){
        request.setRawHeader("Authorization",QString("Bearer " + SessionContext::ft_content).toUtf8());
        manager->post(request, content);
    }

    void put(QNetworkRequest request, QByteArray content){
        request.setRawHeader("Authorization",QString("Bearer " + SessionContext::ft_content).toUtf8());
        manager->put(request, content);
    }

    void deleteResource(QNetworkRequest request){
        request.setRawHeader("Authorization",QString("Bearer " + SessionContext::ft_content).toUtf8());
        manager->deleteResource(request);
    }

signals:
    void finished(QNetworkReply* reply);

};


#endif //GOOGLEWIFIDESKTOPCLIENT_FOYERCLIENT_H
