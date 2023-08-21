#include "Station.h"
#include <QDebug>
#include <QString>
#include <QFile>

bool Station::operator==(const Station& other) const
{
    if (name == other.name)
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

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        stations.append(Station(fields[0]+fields[1], fields[2]));
    }

    file.close();
    return stations;
}
