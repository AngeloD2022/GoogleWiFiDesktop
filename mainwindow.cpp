#include <GAPIS/Auth/consentdialog.h>
#include <GAPIS/credentials.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(!Credentials::credential_exists("user_refresh_token")){
        ConsentDialog *consentDialog = new ConsentDialog();
        consentDialog->show();
        consentDialog->setWindowModality(Qt::ApplicationModal);

        connect(consentDialog, &ConsentDialog::authorizationComplete,[=](QString refreshToken){
            // Store refresh token in the native OS keychain.
            Credentials::store_refresh_token("user_refresh_token",refreshToken);
        });
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

