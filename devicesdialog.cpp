#include "devicesdialog.h"
#include "ui_devicesdialog.h"
#include <QLayout>
#include <QtCharts>

DevicesDialog::DevicesDialog(WifiApi *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DevicesDialog)
{
    ui->setupUi(this);

    this->client = client;
    this->system = client->fetchSystem();
    updateInfoTimer = new QTimer(this);

    chart = new QChart();
    this->downLine = new QLineSeries();
    this->upLine = new QLineSeries();
    chartView = new QChartView();
    refreshUi();
}

DevicesDialog::~DevicesDialog()
{
    delete ui;
}

void DevicesDialog::refreshUi()
{


    chartView->setChart(chart);
    QPen dlPen(QColor::fromRgb(0,0,255));
    dlPen.setWidth(2);
    downLine->setPen(dlPen);
    QPen ulPen(QColor::fromRgb(238, 0, 255));
    ulPen.setWidth(2);
    upLine->setPen(ulPen);
    chart->addSeries(downLine);
    chart->addSeries(upLine);
    chart->createDefaultAxes();
    chart->legend()->hide();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(chartView);
    connect(updateInfoTimer,SIGNAL(timeout()),this,SLOT(updateData()));
    ui->statsBox->setLayout(layout);
    for(WifiApi::Station* e : system->devices){

        QListWidgetItem *i =  new QListWidgetItem();
        i->setForeground(QColor::fromRgb(0, 0, 0));
        if(e->connection->connected){
           i->setBackground(QColor::fromRgb(89, 255, 92));
        }else{
           i->setBackground(QColor::fromRgb(255, 79, 79));
        }
        i->setText(e->name);
        QVariant stationvar = QVariant::fromValue(e);
        i->setData(Qt::UserRole, stationvar);
        ui->deviceList->addItem(i);
    }
    ui->deviceList->setCurrentRow(0);
}

void DevicesDialog::updateData()
{
    qDebug() << "updateData()";
    if(!(!system)){
        QJsonObject metrics = client->fetchRealtimeMetrics(system->id);
        QJsonArray stationMetrics = metrics["stationMetrics"].toArray();
        if(!(!(selected))){
            for(auto e : stationMetrics){

                if(e.toObject()["station"].toObject()["id"].toString() == selected->id){
                    int downloadYVal = e.toObject()["traffic"].toObject()["receiveSpeedBps"].toString().toInt();
                    int uploadYVal = e.toObject()["traffic"].toObject()["transmitSpeedBps"].toString().toInt();
                    if(downloadYVal > maxval){
                        maxval = downloadYVal;
                        chart->axisY()->setRange(0,maxval);
                    }else if(uploadYVal > maxval){
                        maxval = uploadYVal;
                        chart->axisY()->setRange(0,maxval);
                    }
                    upLine->append(time*5,uploadYVal);
                    downLine->append(time*5,downloadYVal);

                    qDebug() << "Value: "+ e.toObject()["traffic"].toObject()["receiveSpeedBps"].toString();
                    chart->axisX()->setRange(0,downLine->count()*5);
                }

                chartView->setChart(chart);

            }
        }
        time++;
    }
}


void DevicesDialog::on_deviceList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

    QVariant var;
    var.setValue(current->data(Qt::UserRole));
    selected = var.value<WifiApi::Station*>();
    maxval = 1;
    chart->axisY()->setRange(0,1);
    chart->axisX()->setRange(0,1);
    if(!selected){

    }else{
//        updateData();
        ui->macAddressLabel->setText(selected->macAddress);
        ui->ipAddrLabel->setText(selected->connection->ip);
        ui->deviceNameLabel->setText("<html><head/><body><p><span style=\" font-size:24pt; font-weight:600;\">"+selected->name+"</span></p></body></html>");
        for(WifiApi::AccessPoint* ap : system->accessPoints){
            if(ap->id == selected->apId){
                ui->accessPointLabel->setText(ap->properties->name);
            }
        }
        ui->connTypeLabel->setText(selected->connection->wirelessBand);


        qDebug() << "SELECTED " + selected->id;
        downLine->clear();
        upLine->clear();
        updateInfoTimer->stop();
        time = 0;
        updateInfoTimer->start(5000);
    }



}
