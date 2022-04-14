//
// Created by Angelo DeLuca on 4/11/22.
//

#ifndef GOOGLEWIFIDESKTOP_USERS_H
#define GOOGLEWIFIDESKTOP_USERS_H

#include "../core/authorization.h"

namespace gwd {

    QList<gwd::auth::GWDUser *> get_users();

    void store_secure(QString id, QString value, std::function<void(bool)> callback);

    void read_secure(QString id, std::function<void(QString)> callback);
}

#endif //GOOGLEWIFIDESKTOP_USERS_H