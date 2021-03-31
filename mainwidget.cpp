//
// Created by Angelo DeLuca on 3/30/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWidget.h" resolved

#define fu8(x) QString::fromUtf8(x.c_str())

#include <GAPIS/wifi/FoyerClient.h>
#include <QMessageBox>
#include <GAPIS/jsontypes/SystemDevices.h>
#include "mainwidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(WifiSystem::Group system, QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWidget) {
    this->system = system;
    ui->setupUi(this);
    setupInterface();
}

MainWidget::~MainWidget() {
    delete ui;
}

void MainWidget::setupInterface() {
    // Create connections...
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWidget::restartBtnClicked);
    connect(ui->pauseTrafBtn, &QPushButton::clicked, this, &MainWidget::haltTrafficBtnClicked);
    connect(ui->devicesBtn, &QPushButton::clicked, this, &MainWidget::devicesBtnClicked);
    connect(ui->routersBtn, &QPushButton::clicked, this, &MainWidget::routersBtnClicked);
    connect(ui->prefBtn, &QPushButton::clicked, this, &MainWidget::prefBtnClicked);

    FoyerClient *client = new FoyerClient();
    connect(client, &FoyerClient::finished, [=](QNetworkReply *reply) {

        SystemDevices::Welcome devices;
        nlohmann::json obj = nlohmann::json::parse(reply->readAll().constData());
        nlohmann::from_json(obj, devices);

        // Count the connected devices...
        int i = 0;
        for (auto e : devices.get_stations()) {
            i += static_cast<bool>(e.get_connected().get()) ? 1 : 0;
        }

        // ... And update the "header" label
        QString networkName = fu8(system.get_group_settings().get_wlan_settings().get_private_ssid());
        QString headtext = "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600;\">" + networkName +
                           " is online</span></p><p><span style=\" font-size:14pt;\"> " + QString::number(i) +
                           " devices connected</span></p></body></html>";
        ui->headerLbl->setText(headtext);
    });

    QNetworkRequest request(
            QUrl("https://googlehomefoyer-pa.googleapis.com/v2/groups/" + fu8(system.get_id()) + "/stations"));
    client->get(request);
}


void MainWidget::restartBtnClicked() {

    // Show a dialog confirming the action...
    QMessageBox::StandardButton response = QMessageBox::question(this,
                                                                 "Restart network?",
                                                                 "Are you sure you want to restart the network?",
                                                                 QMessageBox::Ok | QMessageBox::Cancel
    );

    // Execute a network restart if given confirmation...
    if (response == QMessageBox::Ok) {

        // Call the API endpoint to restart the network...

        FoyerClient *client = new FoyerClient();

        connect(client, &FoyerClient::finished, [=](QNetworkReply *reply) {
            // TODO: Check for errors with the reply
            QMessageBox::information(this, "Success", "The network has successfully restarted.");
        });

        client->post(QNetworkRequest(
                QUrl("https://googlehomefoyer-pa.googleapis.com/v2/groups/" + fu8(system.get_id()) + "/reboot")), "");
    }

}


void MainWidget::haltTrafficBtnClicked() {
    QMessageBox::information(this, "", "Halt traffic clicked...");
}


void MainWidget::devicesBtnClicked() {
    QMessageBox::information(this, "", "Devices clicked...");
}


void MainWidget::routersBtnClicked() {
    QMessageBox::information(this, "", "Routers clicked...");
}


void MainWidget::prefBtnClicked() {
    QMessageBox::information(this, "", "System preferences clicked...");
}