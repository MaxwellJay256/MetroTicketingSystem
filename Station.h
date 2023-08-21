#pragma once
#include <QString>
#include <QList>

class Station
{
private:

public:
	QString id;
	QString name;
	int lineNo;
	int index;

	Station(QString id, QString name) :
		id(id), name(name) {
		lineNo = id.left(2).toInt();
		index = id.right(2).toInt();
	}

	bool operator==(const Station& other) const;
};

QList<Station> readStation(QString fileName);