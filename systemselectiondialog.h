//
// Created by Angelo DeLuca on 3/30/21.
//

#ifndef GOOGLEWIFIDESKTOPCLIENT_SYSTEMSELECTIONDIALOG_H
#define GOOGLEWIFIDESKTOPCLIENT_SYSTEMSELECTIONDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class SystemSelectionDialog; }
QT_END_NAMESPACE

class SystemSelectionDialog : public QDialog {
Q_OBJECT

public:
    explicit SystemSelectionDialog(QWidget *parent = nullptr);

    ~SystemSelectionDialog() override;

private:
    Ui::SystemSelectionDialog *ui;
};

#endif //GOOGLEWIFIDESKTOPCLIENT_SYSTEMSELECTIONDIALOG_H
