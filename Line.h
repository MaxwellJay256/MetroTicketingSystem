#pragma once

#include "Station.h"
#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QList>
#include <QStringList>
#include <QStringListModel>
#include <QTextStream>

class Line
{
private:
	QStringList list_Stations;

public:
	/// @brief 线路编号
	uint number;
	/// @brief 线路长度（线路包含地铁站数量）
	uint length;
	QList<Station*> stations;
	QStringListModel* model_Stations;

	QIcon icon;
	QString mapFileName;

	Line(int number);

	void AddStation(Station *station);
};

extern QList<Line*> lineList;

/// @brief 从文件读取站点信息
/// @param fileName 文件名
void ReadStationInfo(const QString fileName);

/// @brief 根据线路编号查找线路
/// @param stationId 
/// @return 指向该线路的指针
Line* FindLineByNumber(int number);

/// @brief 根据站点名称查找站点
/// @param stationName 站点名称
/// @return 包含所有该站点的列表
QList<Station*> FindStationsByName(QString stationName);

/// @brief 根据站点ID查找站点
/// @param stationId 站点ID
/// @return 指向该站点的指针
Station* FindStationById(QString stationId);