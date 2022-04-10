//
// Created by Angelo DeLuca on 4/10/22.
//

#ifndef GOOGLEWIFIDESKTOP_AUTHORIZATION_H
#define GOOGLEWIFIDESKTOP_AUTHORIZATION_H

#include <QString>
#include <QList>
#include <QImage>
#include <QDateTime>

#define QTKEYCHAIN_NO_EXPORT
#include <qtkeychain/keychain.h>



namespace gwd::app {

    class GWDUser {
    public:
        // general user information
        QString first_name();
        QString last_name();
        QString email();
        QImage profile_picture();

        // authentication information
        bool signed_in();

    };


}

#endif //GOOGLEWIFIDESKTOP_AUTHORIZATION_H
