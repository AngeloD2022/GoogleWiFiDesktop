//
// Created by Angelo DeLuca on 3/30/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SystemSelectionDialog.h" resolved

#include "systemselectiondialog.h"
#include "ui_SystemSelectionDialog.h"

SystemSelectionDialog::SystemSelectionDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SystemSelectionDialog) {
    ui->setupUi(this);
}

SystemSelectionDialog::~SystemSelectionDialog() {
    delete ui;
}
