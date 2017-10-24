#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QObject>
#include "datatype.h"

namespace FP {
enum EntryType
{
    Machine = 1,
    Obstacle = 2,
    LoadType = 3,
    Landmark_Loadport = 11,
    Landmark_ChargeStation = 12,
    Landmark_Waypoint = 13,
    Link = 5,
};


class FileParser : public QObject
{
    Q_OBJECT
public:
    explicit FileParser(QObject *parent = nullptr);

    bool load_file();

signals:
    void sig_machine(QString);
    void sig_loadtype(QString);
    void sig_obstacle(ObstacleInfo);
    void sig_landmark(LandmarkInfo);
    void sig_link(QPair<int,int>);

private:
    //funcs
    void process_line(QByteArray line);
    void emit_prev();

private:
    //vars
    QString tObstacleStr;
    QStringList tLandInfoStr, tLinkStr;

    EntryType entryType;
};

}

#endif // FILEPARSER_H
