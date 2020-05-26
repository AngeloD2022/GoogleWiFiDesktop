//
// Created by Angelo DeLuca on 5/1/20.
//

#include <QString>
#include <QList>
#include <QUuid>
#include <QDebug>
#include "AuthenticationUtilities.h"

QString AuthenticationUtilities::generateClientState() {
    // Client state was analyzed to be formatted like so:
    // XXXXXXXXXXXXXXXXXXXX_XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // (20 random chars)_(36 random chars)

    // Both sides of client state will be stored within this list.
    QList<QString> clientstate;

    // Since GUID produces 32 characters (excluding the -'s), we must only use 20 of them.
    clientstate.push_back(QUuid::createUuid().toString().remove('-').remove("{").remove("}").mid(0, 20));

    // Same thing but for 36 chars.
    clientstate.push_back(
            QUuid::createUuid().toString().remove('-').remove("{").remove("}")
                    .append(QUuid::createUuid().toString().remove('-').remove("{").remove("}").mid(0, 4)));

    return clientstate[0] + "_" + clientstate[1];
}

// Just a standard uppercase UUID
QString AuthenticationUtilities::generateDeviceId() {
    return QUuid::createUuid().toString().remove("{").remove("}").toUpper();
}

QString AuthenticationUtilities::generateChallenge() {

    // 76 Random Bytes. That's it.
    QString result;
    for (int i = 0; i < 3; ++i) {
        result.append(QUuid::createUuid().toString().remove('-').remove("{").remove("}"));
    }

    return result.mid(0, 76).toUtf8().toBase64();
}

