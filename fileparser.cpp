#include "fileparser.h"
#include <QFile>
#include <QDebug>

namespace FP{

FileParser::FileParser(QObject *parent) : QObject(parent)
{
}

bool FileParser::load_file()
{
    QFile tFile("Factory8");
    if (!tFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qFatal("Cannot Open File To Read");
        return false;
    }else
    {
        while (!tFile.atEnd()){
            QByteArray line = tFile.readLine();
            process_line(line);
        }
        emit_prev();

        qDebug()<<"Finished Reading File";
        return true;
    }
}

void FileParser::process_line(QByteArray line)
{
    QString flag = QString(line).split(":").first();
    if(flag == "Machine" || flag == "LoadType" ||
            flag == "Obstacle" || flag == "LoadPort" || flag == "ChargeStation" || flag == "Waypoint" ||
            flag == "Link")
    {
        //get a new entry
        //emit the previous entry first
        emit_prev();

        //process the new entry
        //single line entry
        if(flag=="Machine")
        {
            entryType=Machine;
            emit sig_machine(QString(line).split(":").last());
        }
        else if(flag=="LoadType")
        {
            entryType=LoadType;
            emit sig_loadtype(QString(line).split(":").last());
        }
        //multi line entry
        else if(flag=="Obstacle")
        {
            entryType=Obstacle;
        }
        else if(flag=="LoadPort"||flag=="ChargeStation"||flag=="Waypoint")
        {
            if(flag == "LoadPort")
            {
                entryType=Landmark_Loadport;
            }
            else if(flag == "ChargeStation")
            {
                entryType=Landmark_ChargeStation;
            }
            else if(flag == "Waypoint")
            {
                entryType=Landmark_Waypoint;
            }
        }
        else if(flag=="Link")
        {
            entryType=Link;
        }
    }
    else
    {
        //for multi line entry
        //without flag, process data
        if(entryType==Obstacle)
        {
            tObstacleStr=QString(line);
        }
        else if(entryType==Landmark_Loadport||
                entryType==Landmark_ChargeStation||
                entryType==Landmark_Waypoint)
        {
            tLandInfoStr.append(QString(line));
        }
        else if(entryType==Link)
        {
            tLinkStr.append(QString(line));
        }
    }
}

void FileParser::emit_prev()
{
    if(entryType==Obstacle)
    {
        ObstacleInfo tObstacle;
        QStringList tGeoStr = tObstacleStr.split(",");
        tObstacle.mPos.first=tGeoStr[0].toInt();
        tObstacle.mPos.second=tGeoStr[1].toInt();
        tObstacle.mSize.first=tGeoStr[2].toInt();
        tObstacle.mSize.second=tGeoStr[3].toInt();
        emit sig_obstacle(tObstacle);
    }
    else if(entryType==Landmark_Loadport)
    {
        LandmarkInfo tLandInfo;
        tLandInfo.mId=tLandInfoStr[0].toInt();
        tLandInfo.mType=ChargeStation;
        tLandInfo.mMachine=tLandInfoStr[1];
        tLandInfo.mLoadType=tLandInfoStr[2];

        QStringList tGeoStr = tLandInfoStr[3].split(",");
        tLandInfo.mPos.first=tGeoStr[0].toInt();
        tLandInfo.mPos.second=tGeoStr[1].toInt();
        tLandInfo.mSize.first=tGeoStr[2].toInt();
        tLandInfo.mSize.second=tGeoStr[3].toInt();

        emit sig_landmark(tLandInfo);
        tLandInfoStr.clear();
    }
    else if(entryType==Landmark_ChargeStation)
    {
        LandmarkInfo tLandInfo;
        tLandInfo.mId=tLandInfoStr[0].toInt();
        tLandInfo.mType=ChargeStation;
        tLandInfo.mLoadType=tLandInfoStr[1];

        QStringList tGeoStr = tLandInfoStr[2].split(",");
        tLandInfo.mPos.first=tGeoStr[0].toInt();
        tLandInfo.mPos.second=tGeoStr[1].toInt();
        tLandInfo.mSize.first=tGeoStr[2].toInt();
        tLandInfo.mSize.second=tGeoStr[3].toInt();

        emit sig_landmark(tLandInfo);
        tLandInfoStr.clear();
    }
    else if(entryType==Landmark_Waypoint)
    {
        LandmarkInfo tLandInfo;
        tLandInfo.mId=tLandInfoStr[0].toInt();
        tLandInfo.mType=Waypoint;

        QStringList tGeoStr = tLandInfoStr[1].split(",");
        tLandInfo.mPos.first=tGeoStr[0].toInt();
        tLandInfo.mPos.second=tGeoStr[1].toInt();
        tLandInfo.mSize.first=tGeoStr[2].toInt();
        tLandInfo.mSize.second=tGeoStr[3].toInt();

        emit sig_landmark(tLandInfo);
        tLandInfoStr.clear();
    }
    else if(entryType==Link)
    {
        QPair<int,int> tLink;

        tLink.first = tLinkStr[0].toInt();
        tLink.second = tLinkStr[1].toInt();

        emit sig_link(tLink);
        tLinkStr.clear();
    }
}

}
