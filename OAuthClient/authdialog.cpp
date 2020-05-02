#include "authdialog.h"
#include "ui_authdialog.h"
#include <QtNetwork>

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);


}

AuthDialog::~AuthDialog() {
    delete ui;
}

void AuthDialog::doLoginPageRequest() {
    // Gets the URI for the login page.
    QString data = "";
    QNetworkRequest request(QUrl("https://oauthaccountmanager.googleapis.com/v1/authadvice"));

    QNetworkAccessManager *manager;
//    manager->post(request, nullptr);
//    request.setMethod(QWebEngineHttpRequest::Post);

    // Because we're using the safarivc endpoint...
//    request.setHeader("User-Agent","User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko)");

}
