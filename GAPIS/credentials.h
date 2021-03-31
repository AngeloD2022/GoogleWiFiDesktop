//
// Created by Angelo DeLuca on 3/16/21.
//

#ifndef GOOGLEWIFIDESKTOPCLIENT_CREDENTIALS_H
#define GOOGLEWIFIDESKTOPCLIENT_CREDENTIALS_H


#define app_identity "OnHubDesktopClient"

#include <QString>
#include <QCoreApplication>
#include <keychain.h>
#include <iostream>
#include <QStandardPaths>



using namespace QKeychain;

class Credentials {

public:
    static int store(QString key, QString password){
        WritePasswordJob job(QLatin1String(app_identity));
        job.setAutoDelete(false);
        job.setKey(key);
        job.setTextData(password);
        QEventLoop loop;
        job.connect(&job, &QKeychain::Job::finished, &loop, &QEventLoop::quit);
        job.start();
        loop.exec();
        if ( job.error() ) {
            std::cerr << "Storing password failed: " << qPrintable(job.errorString()) << std::endl;
            return 0;
        }
        std::cout << "Password stored successfully" << std::endl;
        return 1;
    }

    static QString read(QString key){

        ReadPasswordJob job(app_identity);
        job.setAutoDelete(false);
        job.setKey(key);

        QEventLoop loop;
        job.connect(&job, &QKeychain::Job::finished, &loop, &QEventLoop::quit);
        job.start();
        loop.exec();

        if(job.error()){
            std::cout << "An error occured when reading from keychain: " << qPrintable(job.errorString());
            return "";
        }

        return job.textData();
    }


};
#endif //GOOGLEWIFIDESKTOPCLIENT_CREDENTIALS_H
