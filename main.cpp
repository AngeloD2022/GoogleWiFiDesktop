#include "mainwindow.h"

#include <QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QLegend>
#include <QtWebEngine>
//#include <QtWebEngineCore>
#include <QtWebEngineWidgets>


QT_CHARTS_USE_NAMESPACE
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    QtWebEngine::initialize();
    return a.exec();
}
