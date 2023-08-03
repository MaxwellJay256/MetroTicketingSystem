#pragma once
#include <QString>
#include <QList>

class Station
{
public:
	int line;

	QString id;
	QString name;

	Station(int line, QString id, QString name) : line(line), id(id), name(name) {}

	bool operator==(const Station& other) const;

};

QList<Station> readStation(QString fileName);