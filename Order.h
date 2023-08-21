#pragma once
#include "Station.h"
#include "Line.h"
#include <QDebug>
#include <QMap>

class Order
{
private:
	Station* startStation;
	Station* destinationStation;

public:
	uint numOfTickets;
	uint unitPrice;
	uint totalPrice;

	Order();
	~Order();

	void SetStartStation(Station* station);
	void SetDestinationStation(Station* station);
	void SetNumOfTickets(uint num);
	void GetUnitPrice(QMap<QString, uint>& _fareMap);
	void GetTotalPrice();
};

extern QMap<QString, uint> fareMap;

void ReadFareData(QString fileName, QMap<QString, uint> &_fareMap);
