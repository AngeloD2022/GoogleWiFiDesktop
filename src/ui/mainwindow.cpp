//
// Created by Angelo DeLuca on 4/5/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"

namespace gwd {
    MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);

        // Check whether the user is authenticated...


    }

    MainWindow::~MainWindow() {
        delete ui;
    }
} // gwd
