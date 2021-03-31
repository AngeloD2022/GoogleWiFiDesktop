//
// Created by Angelo DeLuca on 3/30/21.
//

#ifndef GOOGLEWIFIDESKTOPCLIENT_MAINWIDGET_H
#define GOOGLEWIFIDESKTOPCLIENT_MAINWIDGET_H

#include <QWidget>
#include "GAPIS/jsontypes/WifiSystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget {
Q_OBJECT


public:
    explicit MainWidget(WifiSystem::Group system, QWidget *parent = nullptr);

    WifiSystem::Group system;

    ~MainWidget() override;


private:
    Ui::MainWidget *ui;

    void restartBtnClicked();

    void setupInterface();

    void haltTrafficBtnClicked();

    void devicesBtnClicked();

    void routersBtnClicked();

    void prefBtnClicked();
};

#endif //GOOGLEWIFIDESKTOPCLIENT_MAINWIDGET_H
