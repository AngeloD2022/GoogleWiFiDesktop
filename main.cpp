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

    QtWebEngine::initialize();
    QApplication a(argc, argv);
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    MainWindow w;
    w.show();


    return a.exec();
}
