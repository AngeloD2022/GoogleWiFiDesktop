//
// Created by Angelo DeLuca on 3/30/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWidget.h" resolved

#define fu8(x) QString::fromUtf8(x.c_str())

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

void MainWidget::setupInterface(){
    QString networkName = fu8(system.get_group_settings().get_wlan_settings().get_private_ssid());
    QString headtext = "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600;\">"+networkName+" is &lt;status&gt;</span></p><p><span style=\" font-size:14pt;\"> 0 devices connected</span></p></body></html>";
    ui->headerLbl->setText(headtext);
}
