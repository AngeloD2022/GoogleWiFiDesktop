#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <apiauthenticator.h>
#include <wifiapi.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ApiAuthenticator apiAuth;
    QString accessTkn;
    QString apiTkn;
private slots:
    void on_actionSign_In_triggered();

    void on_actionServer_Tokens_triggered();

    void on_devicesBtn_clicked();

private:
    // THIS IS VERY MUCH A WIP. I am still in the process of reversing the (OAuth) authentication API.
    // Open the HTML file in the TemporaryAuthSolution folder to get authenticated.
    QString refreshToken = "INSERT_OAUTH_REFRESH_TOKEN_HERE";
    WifiApi::System* system;
    WifiApi* client;

    Ui::MainWindow *ui;
    void refreshUi();

};
#endif // MAINWINDOW_H
