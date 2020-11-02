#include <GAPIS/Auth/consentdialog.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ConsentDialog *consentDialog = new ConsentDialog();
    consentDialog->show();
    consentDialog->setWindowModality(Qt::ApplicationModal);

    connect(consentDialog, &ConsentDialog::authorizationComplete,[=](QString refreshToken){
        QMessageBox::information(this,"Success","Refresh Token: "+refreshToken);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

