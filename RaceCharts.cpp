#pragma once
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCore/QVector>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QDateTimeAxis>
#include "RaceCharts.h"

QT_CHARTS_USE_NAMESPACE

RaceCharts::RaceCharts(qreal maxX, qreal maxY, QWidget* parent) : QWidget(parent), m_chart(new QChart), m_series(new QLineSeries), maxXVal(maxX) {
	QChartView* chartView = new QChartView(m_chart);
	chartView->setMinimumSize(800, 600);
	chartView->setRenderHint(QPainter::Antialiasing);
	//	m_series->append(4, 5);
	m_chart->addSeries(m_series);

	QValueAxis* xAxis = new QValueAxis;
	//	QDateTimeAxis* xAxis = new QDateTimeAxis;
	xAxis->setRange(0, maxX);
	xAxis->setTickCount(1);
	xAxis->setLabelFormat("%f");
	xAxis->setTitleText("Time");

	//QDateTimeAxis* axisX = new QDateTimeAxis;
	//axisX->setTickCount(10);
	//axisX->setFormat("MMM yyyy");
	//axisX->setTitleText("Date");
	//chart->addAxis(axisX, Qt::AlignBottom);
	//series->attachAxis(axisX);

	QValueAxis* yAxis = new QValueAxis;
	yAxis->setRange(0, maxY);	// Considering that this is gear ratio, this would be from 0 to 6. (Most cars have 6 gears)
	yAxis->setTickInterval(1);
	yAxis->setLabelFormat("%d");
	yAxis->setTitleText("Gears");

	m_chart->addAxis(yAxis, Qt::AlignLeft);
	m_series->attachAxis(yAxis);

	m_chart->addAxis(xAxis, Qt::AlignBottom);
	m_series->attachAxis(xAxis);
	m_chart->legend()->hide();
	m_chart->setTitle("Rpm");

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(chartView);

	connect(m_series, &QLineSeries::pointAdded, [=](int index) {
		qreal xCoord = m_series->at(index).x();
		if (xCoord > maxXVal) {
		//	m_series->clear();
			xAxis->setRange(maxXVal, xCoord + maxXVal);
			maxXVal = xCoord * 2;
			 
		}
	//	wprintf(L"Point Added!\n");
	});
}

void RaceCharts::writeData(const QPointF& dataPoint) {


	m_series->append(dataPoint);
	// Add Logic with regard to flushing data here
	// Essentially, if the xLimit is reached, 
	// set xMax = xMax * 2;
	// Range from (xMax, xMax * 2)
}

RaceCharts::~RaceCharts() {

}