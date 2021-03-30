#include <GAPIS/Auth/consentdialog.h>
#include <GAPIS/credentials.h>
#include <GAPIS/wifi/SessionAuthorize.h>

#include "mainwindow.h"
#include "./ui_mainwindow.h"


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
            QMessageBox::information(this,"","token1: "+SessionContext::at_content+"\n\n\n token2: "+SessionContext::ft_content);
        });

        authorize->authorize_ctx(refresh_token);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

