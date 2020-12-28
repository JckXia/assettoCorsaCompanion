#pragma once
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCore/QVector>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QDateTimeAxis>
#include "RaceCharts.h"

QT_CHARTS_USE_NAMESPACE

RaceCharts::RaceCharts(const std::string& title, const std::string & yAxisTitle, qreal maxX, qreal maxY, QWidget * parent = nullptr) : QWidget(nullptr), m_chart(new QChart), m_series(new QLineSeries), maxXVal(maxX) {
	QChartView* chartView = new QChartView(m_chart);
	
	chartView->setRenderHint(QPainter::Antialiasing);
	m_chart->setMinimumSize(600, 400);
	//	m_series->append(4, 5);
	m_chart->addSeries(m_series);
	
	QString titleStr(title.c_str());
	QValueAxis* xAxis = new QValueAxis;
	//	QDateTimeAxis* xAxis = new QDateTimeAxis;
	xAxis->setRange(0, maxX);
 	xAxis->setTickCount(1);
	xAxis->setLabelFormat("%f");
	xAxis->setTitleText("Time");

 

	QString axisStr(yAxisTitle.c_str());
	QValueAxis* yAxis = new QValueAxis;
	yAxis->setRange(0, maxY);	// Considering that this is gear ratio, this would be from 0 to 6. (Most cars have 6 gears)
	yAxis->setTickInterval(1);
	yAxis->setTitleText(axisStr);

	m_chart->addAxis(yAxis, Qt::AlignLeft);
	m_series->attachAxis(yAxis);

	m_chart->addAxis(xAxis, Qt::AlignBottom);
	m_series->attachAxis(xAxis);
	m_chart->legend()->hide();
	m_chart->setTitle(titleStr);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(chartView);

	connect(m_series, &QLineSeries::pointAdded, [=](int index) {
		qreal xCoord = m_series->at(index).x();
		if (xCoord > maxXVal) {
		//	m_series->clear();
			xAxis->setRange(maxXVal, xCoord + maxXVal);
			maxXVal = xCoord * 2;
			 
		}

	});
}

void RaceCharts::writeData(const QPointF& dataPoint) {


	m_series->append(dataPoint);
 
}

RaceCharts::~RaceCharts() {
	delete m_chart;
	delete m_series;
}