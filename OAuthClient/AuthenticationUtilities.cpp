//
// Created by Angelo DeLuca on 5/1/20.
//

#include <QString>
#include <QList>
#include <QUuid>
#include "AuthenticationUtilities.h"

QString AuthenticationUtilities::generateClientState() {
    // Client state was analyzed to be formatted like so:
    // XXXXXXXXXXXXXXXXXXXX_XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // (20 random chars)_(36 random chars)

    // Both sides of client state will be stored within this list.
    QList<QString> clientstate;

    // Since GUID produces 32 characters (excluding the -'s), we must only use 20 of them.
    clientstate.push_back(QUuid::createUuid().toString().remove('-').mid(32, 20));

    clientstate.push_back(
            QUuid::createUuid().toString().remove('-')
                    .append(QUuid::createUuid().toString().remove('-').mid(32, 4)));

    return clientstate[0] + "_" + clientstate[1];
}