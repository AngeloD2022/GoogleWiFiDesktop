//
// Created by Angelo DeLuca on 4/10/22.
//

#ifndef GOOGLEWIFIDESKTOP_AUTHORIZATION_H
#define GOOGLEWIFIDESKTOP_AUTHORIZATION_H

#include <QString>
#include <QList>
#include <QImage>
#include <QDateTime>
#include <QUrl>

namespace gwd::auth {

    class GWDUser {
    public:
        // general user information
        QString first_name();
        QString last_name();
        QString email();
        QImage profile_picture();


    };

    struct SSOAuthParameters {
        QString client_id;
        QString mediator_client_id;
        QString app_version;
        QString redirect_uri;
        QString package_name;
        QString user_agent;
        bool code_verifier;
    };

    class SSOAuth {
    public:
        explicit SSOAuth(SSOAuthParameters parameters);

        QUrl consent_url();

        QString refresh_token(QString oauth_code);
        QString access_bearer(QString refresh_token);
        QString token_for_scopes(QList<QString> scopes);

    };

}

#endif //GOOGLEWIFIDESKTOP_AUTHORIZATION_H
