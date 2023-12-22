#include "Line.h"

Line::Line(int number)
{
    this->number = number;
	this->length = 0;
    this->mapFileName = QString(":/maps/resources/maps/Line%1.png").arg(number);
    this->model_Stations = new QStringListModel();
}

void Line::AddStation(Station *station)
{
	stations.append(station);
    list_Stations << station->name;
    model_Stations->setStringList(list_Stations);
    length ++;
}

QList<Line*> lineList;

void ReadStationInfo(const QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString textLine = in.readLine();
        QStringList fields = textLine.split(',');

        // 解析并添加站点信息
        QString idTemp = fields[0] + fields[1];
        int lineNoTemp = fields[0].toInt();
        QString nameTemp = fields[2];

        Station* newStation = new Station(idTemp, nameTemp);

        // 查找或创建对应线路，添加站点
        Line* currentLine = nullptr;
        for (Line* line : lineList) {
            if (line->number == (uint)lineNoTemp) {
                currentLine = line;
                break;
            }
        }

        if (currentLine == nullptr) {
            currentLine = new Line(lineNoTemp);
            lineList.append(currentLine);
            // qDebug() << "New line: " << lineNoTemp;
        }

        currentLine->AddStation(newStation);
        //qDebug() << "Add station:" << nameTemp << " to line" << lineNoTemp;
    }

    qDebug() << "Finish reading" << fileName;
    file.close();
}

Line* FindLineByNumber(int number)
{
    for (Line* line : lineList) {
        if (line->number == (uint)number) {
			return line;
		}
	}

    qDebug() << "Error: Line " << number << " not found.";
    return nullptr;
}

QList<Station*> FindStationsByName(QString stationName)
{
    QList<Station*> matchingStations;

    for (Line* line : lineList) {
        for (Station* station : line->stations) {
            if (station->name == stationName) {
                matchingStations.append(station);
                break;
            }
        }
    }

    return matchingStations;
}

Station* FindStationById(QString stationId)
{
    for (Line* line : lineList) {
        for (Station* station : line->stations) {
            if (station->id == stationId) {
                return station;
            }
        }
    }

    return nullptr;  // 未找到对应站点
}

