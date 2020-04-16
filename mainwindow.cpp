#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <wifiapi.h>
#include <devicesdialog.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TODO:
    // Allow the user to sign in to generate the access token
    //    this->accessTkn = apiAuth.getNewAccessToken();

    this->accessTkn = apiAuth.getNewAccessToken(this->refreshToken);
    this->apiTkn = apiAuth.getApiToken(accessTkn);
    this->client = new WifiApi(this->apiTkn);
    this->system = client->fetchSystem();
    refreshUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSign_In_triggered()
{



}

void MainWindow::on_actionServer_Tokens_triggered()
{
    QMessageBox::information(this,"-","Auth Token: "+accessTkn+"\nApiTkn: "+apiTkn);
    QMessageBox::information(this,"",system->accessPoints[0]->properties->name+"\n\n"+(system->accessPoints[0]->properties->isPrimaryPoint?"This is the primary point.":"This is not the primary point."));

}

void MainWindow::refreshUi()
{
    this->ui->networkNameLabel->setText("<html><head/><body><p><span style=\" font-size:36pt; font-weight:600;\">"+system->network->wlanSSID+"</span></p></body></html>");
    this->ui->ssidLabel->setText(system->network->wlanSSID);
    this->ui->lanIpLabel->setText(system->network->lan->ipAddress);
    this->ui->gatewayLabel->setText("N/A");
    this->ui->deviceCountLabel->setText(QString::number(system->devices.count()));
}
void MainWindow::on_devicesBtn_clicked()
{
    DevicesDialog* dialog = new DevicesDialog(client);
    dialog->show();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
}
