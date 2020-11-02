#include "consentdialog.h"
#include "ui_consentdialog.h"
#include <QDebug>

ConsentDialog::ConsentDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ConsentDialog) {

    ui->setupUi(this);

    // Prevents focusing of main window
    setWindowModality(Qt::ApplicationModal);

    // Information to satisfy "auth advice" request...
    deviceName = QSysInfo::machineHostName();
    deviceId = RandomUtilities::generateDeviceId();
    deviceChallenge = RandomUtilities::generateChallenge();
    clientState = RandomUtilities::generateClientState();

    // Embedded web browser...
    webEngineView = new QWebEngineView(this);

    // This should fix the CEF 2FA issue...
    webEngineView->page()->profile()->setHttpUserAgent("");
    webEngineView->page()->profile()->setHttpUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko)");

    // Upon initialization of ConsentDialog, we will request for the consent URI.
    connect(this, &ConsentDialog::consentUriObtained, [=](QString uri) {
        // Append WebView to layout and load URI
        ui->progressBar->setVisible(false);
        ui->gridLayout->addWidget(webEngineView);
        loadConsentUri(uri);
    });
    QWebEngineCookieStore *cookies = webEngineView->page()->profile()->cookieStore();
    cookies->loadAllCookies();
    connect(cookies, &QWebEngineCookieStore::cookieAdded, this, &ConsentDialog::webEngineCookieAdded);

    obtainConsentScreenUri();

    connect(this, &ConsentDialog::refreshTokenObtained, [=](QString rt){
        emit authorizationComplete(rt);
        close();
        deleteLater();
    });
}

ConsentDialog::~ConsentDialog() {
    delete ui;
}

/**
 * Gets the URI for the consent screen.
 * Emits to consentScreenObtained(QString)
 */
void ConsentDialog::obtainConsentScreenUri() {

    // Initialize our request...
    QNetworkRequest request((QUrl(endpoints.authAdvice)));

    // Construct request body...
    QJsonObject dataObject;
    dataObject.insert("external_browser", true);
    dataObject.insert("report_user_id", true);
    dataObject.insert("system_version", config.systemVersion);
    dataObject.insert("app_version", config.appVersion);
    dataObject.insert("user_id", QJsonArray());
    dataObject.insert("safari_authentication_session", true);
    dataObject.insert("supported_service", QJsonArray());
    dataObject.insert("request_trigger", "ADD_ACCOUNT");
    dataObject.insert("lib_ver", config.libVer);
    dataObject.insert("package_name", config.packageName);
    dataObject.insert("redirect_uri", config.redirectUri);
    dataObject.insert("device_name", deviceName);
    dataObject.insert("client_id", config.clientId);
    dataObject.insert("mediator_client_id", config.mediatorClientId);
    dataObject.insert("device_id", deviceId);
    dataObject.insert("hl", "en-US");
    dataObject.insert("device_challenge_request", deviceChallenge);
    dataObject.insert("client_state", clientState);

    QString data = QJsonDocument(dataObject).toJson();

    // Set request headers...
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *man = new QNetworkAccessManager();

    // Connect a lambda so we can emit proper information...
    connect(man, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {

        // Parse response and emit the URI...
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        if (json.contains("uri"))
                emit consentUriObtained(json["uri"].toString());
        else
                emit consentUriObtained("CURI_FAIL");

        // Delete reply.
        reply->deleteLater();
    });

    // Send request.
    man->post(request, data.toUtf8());
}

/**
 * Loads a given consent uri to the WebEngineView.
 * @param uri
 */
void ConsentDialog::loadConsentUri(QString uri) {
    QWebEngineHttpRequest request;

    // Disguise request as an apple product to satisfy uri parameter.
//    request.setHeader("User-Agent",
//                      "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko)");

    request.setUrl(QUrl(uri));

    // Tell the WebEngineView to load the request.
    webEngineView->load(request);


}

void ConsentDialog::webEngineCookieAdded(QNetworkCookie cookie) {
    qDebug() << "Cookie:"+cookie.name()+"="+cookie.value();
    if (cookie.name() == "oauth_code") {
        qDebug() << "cookie found";
        // exchange the oauth code cookie for a refresh token.
        getRefreshToken(cookie.value());
    }
}

void ConsentDialog::getRefreshToken(QString oauthCode) {
    QUrl url(endpoints.refreshTokenExchange);
    qDebug() << oauthCode;
    // Configure query...
    QUrlQuery query;
    query.addQueryItem("client_id", config.mediatorClientId);
    query.addQueryItem("grant_type", "authorization_code");
    query.addQueryItem("scope", "https://www.google.com/accounts/OAuthLogin");
    query.addQueryItem("code", oauthCode);

    url.setQuery(query);

    QNetworkRequest request(url);
    QNetworkAccessManager *man = new QNetworkAccessManager(this);

    // connect lambda to deserialize reply and emit correct information...
    connect(man, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        if (json.contains("refresh_token"))
                emit refreshTokenObtained(json["refresh_token"].toString());
        else
                emit refreshTokenObtained("RT_FAIL");

        // delete reply
        reply->deleteLater();
    });
    man->post(request,"");
}

