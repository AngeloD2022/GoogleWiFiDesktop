#include <GAPIS/Auth/consentdialog.h>
#include <GAPIS/credentials.h>
#include <GAPIS/wifi/SessionAuthorize.h>
#include <GAPIS/wifi/FoyerClient.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "GAPIS/jsontypes/WifiSystem.h"
#include "mainwidget.h"
#include <vector>

#define fu8(x) QString::fromUtf8(x.c_str())

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString refresh_token = Credentials::read("user_refresh_token");

    if(refresh_token.isEmpty()){
        ConsentDialog *consentDialog = new ConsentDialog();
        consentDialog->show();
        consentDialog->setWindowModality(Qt::ApplicationModal);

        connect(consentDialog, &ConsentDialog::authorizationComplete,[=](QString refreshToken){
            // Store refresh token in the native OS keychain.
            Credentials::store("user_refresh_token", refreshToken);
        });

    }else{
        refresh_token = Credentials::read("user_refresh_token");

        SessionAuthorize *authorize = new SessionAuthorize(this);

        connect(authorize, &SessionAuthorize::auth_finished, [=](){
            loadInterface();
        });

        authorize->authorize_ctx(refresh_token);
    }
}

void MainWindow::loadInterface(){
    //TODO: Make a dialog for selecting the system later.
    FoyerClient *client = new FoyerClient();

    connect(client, &FoyerClient::finished, [=](QNetworkReply* reply){
        WifiSystem::Welcome system;
        nlohmann::json obj = nlohmann::json::parse(reply->readAll().constData());
        nlohmann::from_json(obj, system);

        QMessageBox::information(this,"",fu8(system.get_groups()[0].get_id()));

        MainWidget *mw = new MainWidget(system.get_groups()[0],this);

//        this->layout()->removeWidget(this->ui->container);
        this->setCentralWidget(mw);

    });

    QNetworkRequest request(QUrl("https://googlehomefoyer-pa.googleapis.com/v2/groups"));
    client->get(request);
}

MainWindow::~MainWindow()
{
    delete ui;
}

