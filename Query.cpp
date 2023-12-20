#include "Query.h"

Query::Query()
{
    model_QueryResult = new QStringListModel();
}

QStringListModel* Query_ID::StartQuery(void)
{
    // 对于 Query_Id，一个 ID 最多只可能搜索到一个结果
    queryResult.clear();
    model_QueryResult->setStringList(queryResult); // 清空结果
    Station* station = FindStationById(query_id);
    if (station == nullptr) {
		qDebug() << "No station found.";
    } else
        queryResult << station->name + " - " + QString::number(station->lineNo) + " 号线";

    model_QueryResult->setStringList(queryResult);
    return model_QueryResult;
}

QStringListModel* Query_Name::StartQuery(void)
{
    // 对于 Query_Name，一个 Name 可能搜索到多个结果
    queryResult.clear();
    QList<Station*> stations = FindStationsByName(query_name);
    if (stations.size() == 0) {
        qDebug() << "No station found.";
    }
    else {
        for (Station* station : stations) {
            queryResult << station->name + " - " + QString::number(station->lineNo) + " 号线";
        }
    }
    model_QueryResult->setStringList(queryResult);
	return model_QueryResult;
}
