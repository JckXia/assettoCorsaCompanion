#pragma once
#include <QtCharts/QChartView>
#include <QtCore/QVector>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QDateTimeAxis>
#include "RaceChartView.h"
#include "RaceCharts.h"

QT_CHARTS_USE_NAMESPACE

RaceCharts::RaceCharts(const std::string& title, const std::string& yAxisTitle, qreal maxX, qreal maxY, QWidget* parent = nullptr) : QWidget(nullptr), m_chart(new QChart), m_series(new QLineSeries), trace_points(new QLineSeries), maxXVal(maxX), incVal(maxX) {
	//	QChartView* chartView = new QChartView(m_chart);
	RaceChartView* chartView = new RaceChartView(m_chart);
	
	
	chartView->setRenderHint(QPainter::Antialiasing);
	m_chart->setMinimumSize(600, 400);
	m_chart->addSeries(m_series);
	m_chart->addSeries(trace_points);
		
	QString titleStr(title.c_str());
	QValueAxis* xAxis = new QValueAxis;
	//	QDateTimeAxis* xAxis = new QDateTimeAxis;
	xAxis->setRange(0, maxX);
	xAxis->setTickCount(1);
	xAxis->setLabelFormat("%f");
	xAxis->setTitleText("Time");

	m_xAxis = xAxis;


	QString axisStr(yAxisTitle.c_str());
	QValueAxis* yAxis = new QValueAxis;
	yAxis->setRange(0, maxY);	// Considering that this is gear ratio, this would be from 0 to 6. (Most cars have 6 gears)
	yAxis->setTickInterval(1);
	yAxis->setTitleText(axisStr);

	 

	m_chart->addAxis(yAxis, Qt::AlignLeft);
	m_series->attachAxis(yAxis);
	trace_points->attachAxis(yAxis);

	m_chart->addAxis(xAxis, Qt::AlignBottom);
	m_series->attachAxis(xAxis);
	trace_points->attachAxis(xAxis);

	m_chart->legend()->hide();
	m_chart->setTitle(titleStr);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(chartView);

	//connect(m_series, &QLineSeries::pointAdded, [=](int index) {
	//	qreal xCoord = m_series->at(index).x();
	//	if (xCoord > maxXVal) {
	//		//	m_series->clear();
	//	//	xAxis->setRange(maxXVal, xCoord + maxXVal);
	////		maxXVal = xCoord * 2;

	//	}

	//	});
}


// Here we check for a few things:
// 1. The x point is greater than 0
// TODO: The x coordinates exists within some buffer.
// std::unordered_map, with near constant O(1) insertion and lookup
// because data is indexed with time stamp, there's garantee that it
// will be unique
void RaceCharts::setCursor(const QPointF& cursorPoint)
{
	trace_points->setColor(Qt::red);

	trace_points->append(cursorPoint);
}

void RaceCharts::writeData(const QPointF& dataPoint) {

	if ((dataPoint.x() > maxXVal))
	{
		// We can safely clear the old series
		m_series->clear();
		m_xAxis->setRange(maxXVal, maxXVal + incVal);
		maxXVal = maxXVal + incVal;
	}

	// Lap complete
	if (dataPoint.x() < lastXCoord) {

		m_series->clear();
		m_xAxis->setRange(0, incVal);
		maxXVal = incVal;	// Rest
	}

	//	m_lock.lock();
	lastXCoord = dataPoint.x();
	//	m_lock.unlock();
//	trace_points->setColor(Qt::green);
//	trace_points->append(dataPoint);
//	trace_points->append(dataPoint);
	m_series->append(dataPoint);
}

RaceCharts::~RaceCharts() {
	delete m_chart;
	delete m_series;
}