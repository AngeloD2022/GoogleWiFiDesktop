#ifndef DEVICESDIALOG_H
#define DEVICESDIALOG_H

#include <QDialog>
#include <wifiapi.h>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QLegend>
#include <QListWidget>

namespace Ui {
class DevicesDialog;
}

class DevicesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DevicesDialog(WifiApi *client,QWidget *parent = nullptr);
    ~DevicesDialog();
    void refreshUi();


private slots:
    void on_deviceList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void updateData();
private:
    QThread thread;

    QtCharts::QChartView *chartView;
    QtCharts::QChart* chart;
    QtCharts::QLineSeries* downLine;
    QtCharts::QLineSeries* upLine;
    QtCharts::QCategoryAxis* xAxis;
    QtCharts::QCategoryAxis* yAxis;
    Ui::DevicesDialog *ui;
    WifiApi *client;
    WifiApi::System *system;
    QTimer* updateInfoTimer;
    int time = 0;
    WifiApi::Station* selected;
    int maxval = 0;
};

#endif // DEVICESDIALOG_H
