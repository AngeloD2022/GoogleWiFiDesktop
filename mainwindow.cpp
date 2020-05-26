#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <wifiapi.h>
#include <devicesdialog.h>
#include <OAuthClient/authdialog.h>
#include <Encryption/qaesencryption.h>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // TODO:
    // Allow the user to sign in to generate the access token
    //    this->accessTkn = apiAuth.getNewAccessToken();


    QFile auth("./gacc/auth.bin");
    if (auth.exists()) {

        auth.open(QIODevice::ReadOnly);
        QJsonObject obj = QJsonDocument::fromJson(auth.readAll()).object();
        auth.close();

        QByteArray iv = obj["IV"].toString().toUtf8();
        iv = QByteArray::fromBase64(iv);
        QByteArray data = obj["dat"].toString().toUtf8();
        data = QByteArray::fromBase64(data);

        QString key = QSysInfo::machineUniqueId() +
                      QCryptographicHash::hash(QSysInfo::currentCpuArchitecture().toUtf8(), QCryptographicHash::Sha512);

        QByteArray keyHash = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
        QAESEncryption *encryption = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::CBC);
        QByteArray decode = encryption->decode(data, keyHash, iv);

        QString token = QString(encryption->removePadding(decode));
        refreshToken = token;

        startApiService();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::authComplete(QString refreshTkn) {
    this->refreshToken = refreshTkn;
    startApiService();
}


void MainWindow::startApiService() {
    this->accessTkn = apiAuth.getNewAccessToken(this->refreshToken);
    this->apiTkn = apiAuth.getApiToken(accessTkn);
    this->client = new WifiApi(this->apiTkn);
    this->system = client->fetchSystem();
    refreshUi();
}

void MainWindow::on_actionSign_In_triggered() {
    AuthDialog *authdialog = new AuthDialog();
    authdialog->setVisible(true);
    connect(authdialog, &AuthDialog::authComplete, this, &MainWindow::authComplete);
}

void MainWindow::on_actionServer_Tokens_triggered() {
    QMessageBox::information(this, "-", "Auth Token: " + accessTkn + "\nApiTkn: " + apiTkn);
    QMessageBox::information(this, "", system->accessPoints[0]->properties->name + "\n\n" +
                                       (system->accessPoints[0]->properties->isPrimaryPoint
                                        ? "This is the primary point." : "This is not the primary point."));

}

void MainWindow::refreshUi() {
    this->ui->networkNameLabel->setText(
            "<html><head/><body><p><span style=\" font-size:36pt; font-weight:600;\">" + system->network->wlanSSID +
            "</span></p></body></html>");
    this->ui->ssidLabel->setText(system->network->wlanSSID);
    this->ui->lanIpLabel->setText(system->network->lan->ipAddress);
    this->ui->gatewayLabel->setText("N/A");
    this->ui->deviceCountLabel->setText(QString::number(system->devices.count()));
}

void MainWindow::on_devicesBtn_clicked() {
    DevicesDialog *dialog = new DevicesDialog(client);
    dialog->show();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
}
