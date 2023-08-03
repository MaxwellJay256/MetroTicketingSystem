#include "Station.h"
#include <QDebug>
#include <QString>
#include <QFile>

bool Station::operator==(const Station& other) const
{
    if (line == other.line && id == other.id)
        return true;
    else
        return false;
}

QList<Station> readStation(QString fileName) {
    QFile file(fileName);
    QList<Station> stations;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << file.errorString();
        return stations;
    }
    QTextStream in(&file);

    // 跳过文件的前 3 行
    for (int i = 0; i < 3; i++) {
        in.readLine();
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        stations.append(Station(fields[0].toInt(), fields[0]+fields[1], fields[2]));
    }

    file.close();
    return stations;
}
