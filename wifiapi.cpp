#include "wifiapi.h"
#include <easyhttp.h>
WifiApi::WifiApi(QString apiKey)
{
    this->API_KEY = apiKey;
}

WifiApi::System* WifiApi::fetchSystem(){

    // API Request
    QString base = "https://googlehomefoyer-pa.googleapis.com/v2/groups?prettyPrint=false";


    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+API_KEY);
    QNetworkReply* reply = EasyHttp::getRequest(base,headers);
    while(!reply->isFinished()){
        qApp->processEvents();
    }
    QJsonObject root = QJsonDocument::fromJson(reply->readAll()).object()["groups"].toArray()[0].toObject();
    System *system = new System();

    // ID
    system->id = root["id"].toString();

    // NETWORK
    QJsonObject lan = root["groupSettings"].toObject()["lanSettings"].toObject();
    QJsonObject wlansettings = root["groupSettings"].toObject()["wlanSettings"].toObject();
    system->network->lan->netMask = lan["netmask"].toString();
    system->network->lan->ipAddress = lan["ipAddress"].toString();
    system->network->lan->dhcpPoolEnd = lan["dhcpPoolEnd"].toString();
    system->network->lan->dhcpPoolBegin = lan["dhcpPoolBegin"].toString();
    system->network->lan->prioritizedStation->endTime = lan["prioritizedStation"].toObject()["prioritizationEndTime"].toString();
    system->network->lan->prioritizedStation->stationId = lan["prioritizedStation"].toObject()["stationId"].toString();
    //WLAN
    system->network->wlanSSID = wlansettings["privateSsid"].toString();

    // ACCESS POINTS
    QJsonArray points = root["accessPoints"].toArray();
//    system.accessPoints = new;

    for(int i = 0; i < points.size(); i++){
        AccessPoint* ap = new AccessPoint();
        ap->id = points[i].toObject()["id"].toString();

        // Light Intensities
        ap->settings->lighting->intensity =
                points[i].toObject()["accessPointSettings"].toObject()["lightingSettings"].toObject()["intensity"].toInt();

        ap->properties->name =
                points[i].toObject()["accessPointSettings"].toObject()["accessPointOtherSettings"].toObject()["apName"].toString().split(" - ")[0];

        ap->properties->ipAddress = points[i].toObject()["accessPointProperties"].toObject()["ipAddress"].toString();

        ap->properties->isBridged =
                (points[i].toObject()["accessPointProperties"].toObject()["isBridged"] == QJsonValue::Type::Undefined ?
                    false : points[i].toObject()["accessPointProperties"].toObject()["isBridged"].toBool());

        ap->properties->meshResult =
                points[i].toObject()["accessPointProperties"].toObject()["joinMeshResult"].toObject()["result"].toString();

        ap->properties->lastSeenTime = points[i].toObject()["accessPointProperties"].toObject()["lastSeenTime"].toString();

        ap->properties->hardwareModel = points[i].toObject()["accessPointProperties"].toObject()["hardwareType"].toString();

        ap->properties->isPrimaryPoint =
                (points[i].toObject()["accessPointProperties"].toObject()["isGroupRoot"] == QJsonValue::Type::Undefined ?
                    false : points[i].toObject()["accessPointProperties"].toObject()["isGroupRoot"].toBool());

        ap->properties->firmwareVersion = points[i].toObject()["accessPointProperties"].toObject()["firmwareVersion"].toString();
        system->accessPoints.append(ap);
    }

    // MANAGERS
    QJsonArray managers = root["managers"].toArray();
//    system.managers = new System::Manager[managers.size()];

    for(int i = 0; i < managers.size(); i++){
        WifiApi::System::Manager* manager = new WifiApi::System::Manager();
        manager->id = managers[i].toObject()["managerId"].toString();
        manager->email = managers[i].toObject()["emailAddress"].toString();
        manager->owner = (managers[i].toObject()["managerId"] == QJsonValue::Undefined?false:managers[i].toObject()["managerId"].toBool());
        system->managers.append(manager);
    }

    // DEVICE GROUPS
    QJsonArray dgroups = root["groupSettings"].toObject()["stationSets"].toArray();
//    system.deviceGroups = new StationGroup[dgroups.size()];
    for(int i = 0; i < dgroups.size(); i++){
        WifiApi::StationGroup* devicegroup = new WifiApi::StationGroup();
        devicegroup->id = dgroups[i].toObject()["id"].toInt();
        devicegroup->name = dgroups[i].toObject()["name"].toString();
        devicegroup->color->red = dgroups[i].toObject()["color"].toObject()["red"].toDouble();
        devicegroup->color->green = dgroups[i].toObject()["color"].toObject()["green"].toDouble();
        devicegroup->color->blue = dgroups[i].toObject()["color"].toObject()["blue"].toDouble();

        QJsonArray members = dgroups[i].toObject()["members"].toArray();
        for(int j = 0; j < members.size(); j++){
            devicegroup->memberStationIDs.append(members[j].toObject()["stationId"].toString());
        }
        system->deviceGroups.append(devicegroup);
    }
    system->devices = fetchDevices(system->id);
    return system;
}

QList<WifiApi::Station*> WifiApi::fetchDevices(QString groupId)
{
    QString base = "https://googlehomefoyer-pa.googleapis.com/v2/groups/"+groupId+"/stations?prettyPrint=false";

    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+API_KEY);
    QNetworkReply* reply = EasyHttp::getRequest(base,headers);
    while(!reply->isFinished()){
        qApp->processEvents();
    }
    QJsonArray stations = QJsonDocument::fromJson(reply->readAll()).object()["stations"].toArray();
    QList<Station*> s;

    QJsonObject operationInp;

    QJsonArray stationIds;

    for(auto e : stations){
        stationIds.push_back(QJsonValue(e.toObject()["id"]));
    }
    operationInp.insert("stationIds",stationIds);
    QString opId = getOperationId(groupId, "stations","sensitiveInfo", QJsonDocument(operationInp).toJson());

    // Fetch MAC addresses...
    QJsonArray stationMacs = getOperationResult(opId,"sensitiveInfo")["stationSensitiveInfos"].toArray();

    for(int i = 0; i < stations.size(); i++){
        Station* c = new Station();
        QJsonValue currentStation = stations[i];
        c->id = currentStation["id"].toString();
        c->apId = currentStation["apId"].toString();
        c->name = currentStation["friendlyName"].toString();
        c->type = currentStation["friendlyType"].toString();
        c->ouiName = currentStation["curatedOuiName"].toString();
        c->connection->ip = currentStation["ipAddress"].toString();
        c->connection->connected = currentStation["connected"].toBool();
        c->connection->wirelessBand = currentStation["wirelessBand"].toString();
        QJsonValue mac = findValueFromJsonArray(stationMacs,"stationId",stations[i].toObject()["id"].toString())["macAddress"];
        if(mac != QJsonObject()){
            c->macAddress = mac.toString();
        }else{
            c->macAddress = "";
        }
        s.append(c);
    }
    return s;
}

//Stackoverflow
QJsonObject WifiApi::findValueFromJsonArray(QJsonArray arr, QString key, QString val) {
    for (const auto obj : arr) {
        if (obj.toObject().value(key) == val)
            return obj.toObject();
    }
    return QJsonObject();
}



QString WifiApi::getOperationId(QString groupId, QString operationObject, QString opName, QString query)
{
    QString base = "https://googlehomefoyer-pa.googleapis.com/v2/groups/"+groupId+"/"+operationObject+"/operations/"+opName+"?prettyPrint=false";

    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+API_KEY);
    QNetworkReply* reply = EasyHttp::postRequest(base,query,"application/json",headers);
    while(!reply->isFinished()){
        qApp->processEvents();
    }
    return QJsonDocument::fromJson(reply->readAll()).object()["operation"].toObject()["operationId"].toString();
}

QJsonObject WifiApi::getOperationResult(QString operationId,QString endpointSegment)
{
    QString base = "https://googlehomefoyer-pa.googleapis.com/v2/operations/"+operationId+"/"+endpointSegment+"?prettyPrint=false";

    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+API_KEY);
    QNetworkReply* reply = EasyHttp::getRequest(base,headers);
    while(!reply->isFinished()){
        qApp->processEvents();
    }
    return QJsonDocument::fromJson(reply->readAll()).object();
}



void WifiApi::setApiKey(QString apiKey)
{
    this->API_KEY = apiKey;
}




// OPERATIONS
void WifiApi::prioritizeStation(WifiApi::Station *station,QString endTime, QString groupId)
{
    QJsonObject request;
    request.insert("stationId", station->id);
    request.insert("prioritizatitonEndTime",endTime);
    QString base = "https://googlehomefoyer-pa.googleapis.com/v2/groups/"+groupId+"/prioritizedStation?prettyPrint=false";
    QString data = QJsonDocument(request).toJson();
    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+API_KEY);
    EasyHttp::putRequest(base,data,"application/json",headers);
//    while(!reply->isFinished()){
//        qApp->processEvents();
//    }

}


void WifiApi::removePrioritizedStation(QString groupId)
{
    QString base = "https://googlehomefoyer-pa.googleapis.com/v2/groups/"+groupId+"/prioritizedStation?prettyPrint=false";
    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+API_KEY);
    EasyHttp::deleteRequest(base,"application/json",headers);
//    while(!reply->isFinished()){
//        qApp->processEvents();
    //    }
}

void WifiApi::pauseStations(QList<WifiApi::Station*> stations, QString expiryTimestamp, QString groupId)
{
    QJsonObject request;
    QJsonArray idArray;
    request.insert("blocked",true);
    request.insert("expiryTimestamp", expiryTimestamp);
//    request.insert("stationId", station->id);
    for(Station* s : stations){
        idArray.append(s->id);
    }
    request.insert("stationId",request);
    QString base = "https://googlehomefoyer-pa.googleapis.com/v2/groups/"+groupId+"/stationBlocking?prettyPrint=false";
    QString data = QJsonDocument(request).toJson();
    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+API_KEY);
    EasyHttp::putRequest(base,data,"application/json",headers);
}

QJsonObject WifiApi::fetchRealtimeMetrics(QString groupId)
{
    QString base = "https://googlehomefoyer-pa.googleapis.com/v2/groups/"+groupId+"/realtimeMetrics?prettyPrint=false";
    QMap<QString,QString> headers;
    headers.insert("Authorization",QString("Bearer ")+API_KEY);
    QNetworkReply *reply = EasyHttp::getRequest(base,headers);
    while(!reply->isFinished()){
        qApp->processEvents();
    }
    return QJsonDocument::fromJson(reply->readAll()).object();
}
