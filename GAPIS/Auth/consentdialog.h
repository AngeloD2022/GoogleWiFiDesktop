#ifndef CONSENTDIALOG_H
#define CONSENTDIALOG_H

#include <QDialog>

#include <QtWebEngineWidgets>
#include <QWebEngineHttpRequest>
#include <QWebEngineCookieStore>
#include <QNetworkCookie>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include "RandomUtilities.h"

namespace Ui {
    class ConsentDialog;
}

class ConsentDialog : public QDialog {
Q_OBJECT

public:
    explicit ConsentDialog(QWidget *parent = nullptr);

    ~ConsentDialog();

signals:

    // Emitted when the refresh token has been obtained successfully.
    void authorizationComplete(QString refreshToken);
    void refreshTokenObtained(QString refreshToken);
    void consentUriObtained(QString uri);

private:

    void obtainConsentScreenUri();

    void loadConsentUri(QString uri);

    void getRefreshToken(QString oauthCode);

    Ui::ConsentDialog *ui;

    // Information to satisfy "auth advice" request...
    QString deviceName;
    QString deviceId;
    QString deviceChallenge;
    QString clientState;

    // WebEngine widget. This shows the consent screen.
    QWebEngineView *webEngineView;
    void webEngineCookieAdded(QNetworkCookie cookie);

    // Specific values used in authadvice request.
    struct Configuration {
        QString packageName = "com.google.OnHub";
        QString systemVersion = "13.4";
        QString appVersion = "2.25.1";
        QString libVer = "3.3";
        QString redirectUri = "com.google.sso.586698244315-vc96jg3mn4nap78iir799fc2ll3rk18s:/authCallback";
        QString clientId = "586698244315-vc96jg3mn4nap78iir799fc2ll3rk18s.apps.googleusercontent.com";
        QString mediatorClientId = "936475272427.apps.googleusercontent.com";
    } config;

    // API Endpoints...
    struct Endpoints {
        QString authAdvice = "https://oauthaccountmanager.googleapis.com/v1/authadvice";
        QString refreshTokenExchange = "https://www.googleapis.com/oauth2/v4/token";
    } endpoints;
};

#endif // CONSENTDIALOG_H
