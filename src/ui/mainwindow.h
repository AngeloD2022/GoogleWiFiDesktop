//
// Created by Angelo DeLuca on 4/5/22.
//

#ifndef GOOGLEWIFIDESKTOP_MAINWINDOW_H
#define GOOGLEWIFIDESKTOP_MAINWINDOW_H

#include <QMainWindow>

namespace gwd {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
    QT_END_NAMESPACE

    class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);

        ~MainWindow() override;

    private:
        Ui::MainWindow *ui;
    };
} // gwd

#endif //GOOGLEWIFIDESKTOP_MAINWINDOW_H
