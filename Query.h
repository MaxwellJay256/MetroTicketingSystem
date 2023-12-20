#pragma once
#include "Line.h"
#include <QLabel>
#include <QString>
#include <QStringList>
#include <QStringListModel>

class Query
{
protected:
	QStringList queryResult;
	QStringListModel* model_QueryResult;

public:
	Query();
	~Query() {};

	virtual QStringListModel* StartQuery() = 0;
};

class Query_ID : public Query
{
private:
	QString query_id;

public:
	Query_ID() : query_id("") {};
	Query_ID(const QString& input) : query_id(input) {};
	~Query_ID() {};

	QStringListModel* StartQuery(void);
};

class Query_Name : public Query
{
private:
	QString query_name;

public:
	Query_Name() : query_name("") {};
	Query_Name(const QString& input) : query_name(input) {};
	~Query_Name() {};

	QStringListModel* StartQuery(void);
};