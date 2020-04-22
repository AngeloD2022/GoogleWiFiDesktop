#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QtWebEngine>
//#include <QtWebEngineCore>


namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);
    ~AuthDialog();

private:
    Ui::AuthDialog *ui;

};

#endif // AUTHDIALOG_H
