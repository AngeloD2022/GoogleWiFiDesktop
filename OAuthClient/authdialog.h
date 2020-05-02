#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QtWebEngineWidgets>
//#include "HTTP/requestmanager.h"
#include <QtNetwork>
//#include <QtWebEngineCore>


namespace Ui {
    class AuthDialog;
}

class AuthDialog : public QDialog {
Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);

    ~AuthDialog();

    void doLoginPageRequest();

    void loginPageRequestComplete(QString reply);


private:

    Ui::AuthDialog *ui;
    QWebEngineView *view = new QWebEngineView();

};

#endif // AUTHDIALOG_H
