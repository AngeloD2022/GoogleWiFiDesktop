//
// Created by Angelo DeLuca on 5/1/20.
//

#ifndef ONHUBDESKTOP_AUTHENTICATIONUTILITIES_H
#define ONHUBDESKTOP_AUTHENTICATIONUTILITIES_H

#include <QString>
class AuthenticationUtilities {
public:
    static QString generateClientState();

    static QString generateDeviceId();

    static QString generateChallenge();
};


#endif //ONHUBDESKTOP_AUTHENTICATIONUTILITIES_H
