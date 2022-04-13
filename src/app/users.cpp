//
// Created by Angelo DeLuca on 4/11/22.
//

#include "users.h"

#define QTKEYCHAIN_NO_EXPORT
#include <qtkeychain/keychain.h>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

const QString user_data_path = "users.json";
const QString app_identifier = "GOOGLE_WIFI_DESKTOP";


QList<gwd::auth::GWDUser *> gwd::get_users() {

    // parse users.json
    // deserialize file to a list of GWDUser objects.

    // read in file contents...
    QFile file(user_data_path);
    file.open(QFile::ReadOnly);
    QTextStream raw(&file);

    // parse and deserialize...
    QJsonDocument json = QJsonDocument::fromJson(raw.readAll().toUtf8());
    QJsonArray users = json.array();

    QList<auth::GWDUser*> result;

    // users.json should be a list of google user ids
    for (const auto &item : users) {
        // for each user id,
    }


    return result;
}

void gwd::store_secure(QString id, QString value, std::function<void(bool)> callback) {
    QKeychain::WritePasswordJob job(app_identifier);
    job.setAutoDelete(false);
    job.setKey(id);
    job.setTextData(value);

    // connect callback...
    QObject::connect(&job, &QKeychain::Job::finished, [&](){
        callback(job.error());
    });

    job.start();
}

void gwd::read_secure(QString id, std::function<void(QString)> callback) {

    QKeychain::ReadPasswordJob job(app_identifier);
    job.setKey(id);

    // connect callback...
    QObject::connect(&job, &QKeychain::Job::finished, [&](){
        callback(job.textData());
    });

    job.start();
}



