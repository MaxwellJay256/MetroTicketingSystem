#include "Order.h"
constexpr auto DEFAULT_UNIT_PRICE = 2;

Order::Order()
{
	startStation = nullptr;
	destinationStation = nullptr;
	unitPrice = DEFAULT_UNIT_PRICE;
	numOfTickets = 1;
    GetTotalPrice();
    qDebug() << "[Order]New order is created.";
}

Order::~Order()
{
	qDebug() << "Last order deleted.";
}

void Order::SetStartStation(Station* station)
{
	startStation = station;
    qDebug() << "[Order]Set start: " << station->name;
}
void Order::SetDestinationStation(Station* station)
{
	destinationStation = station;
    qDebug() << "[Order]Set destination: " << station->name;
}

void Order::SetNumOfTickets(uint num)
{
    numOfTickets = num;
	qDebug() << "[Order]Set number of tickets: " << num;
}

QMap<QString, uint> fareMap;

void ReadFareData(QString fileName, QMap<QString, uint> &_fareMap)
{
    qDebug() << "Loading fare data...";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << file.errorString();
        return;
    }

    QTextStream in(&file);
    QStringList destinationList = in.readLine().split(",");

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(",");

        QString startStationId = tokens[0];
        for (qsizetype i = 1; i < tokens.size(); ++i) {
            QString destinationStationId = destinationList[i];
            uint price = tokens[i].toUInt();

            _fareMap.insert(startStationId + destinationStationId, price);
        }
    }

    qDebug() << "Fare data read successfully.";
    file.close();
}

void Order::GetUnitPrice(QMap<QString, uint>& _fareMap)
{
    if (startStation == nullptr || destinationStation == nullptr) {
        qDebug() << "[Order]Error: Start station or destination station is not set.";
        return;
    }

    // 查找价格
    QString key = startStation->id + destinationStation->id;
    if (_fareMap.contains(key)) {
		unitPrice = _fareMap[key];
        qDebug() << "[Order]Get unit price: " << unitPrice << "￥| Route: " << key;
	} else {
        unitPrice = DEFAULT_UNIT_PRICE;
		qDebug() << "[Order]Error: No fare data for this route: " << key;
	}
}

void Order::GetTotalPrice()
{
    totalPrice = unitPrice * numOfTickets;
	qDebug() << "[Order]Get total price: " << totalPrice << "￥";
}
