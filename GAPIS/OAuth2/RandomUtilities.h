//
// Created by Angelo DeLuca on 8/10/20.
//

#ifndef GOOGLEWIFIDESKTOPCLIENT_RANDOMUTILITIES_H
#define GOOGLEWIFIDESKTOPCLIENT_RANDOMUTILITIES_H
#include <QString>
#include <QList>
#include <QUuid>

/**
 * Class includes methods that generate random information and are used for obtaining the oauth consent screen.
 */
class RandomUtilities {
public:

    static QString generateClientState() {
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


    // Random "Device ID"
    static QString generateDeviceId() {
        return QUuid::createUuid().toString().remove("{").remove("}").toUpper();
    }


    QString generateChallenge() {
        // 76 Random Bytes. That's it.
        QString result;
        for (int i = 0; i < 3; ++i) {
            result.append(QUuid::createUuid().toString().remove('-').remove("{").remove("}"));
        }

        return result.mid(0, 76).toUtf8().toBase64();
    }

};


#endif //GOOGLEWIFIDESKTOPCLIENT_RANDOMUTILITIES_H
