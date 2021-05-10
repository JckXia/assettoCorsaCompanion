#pragma once
#include <QtCharts/QChartView>
#include <QtCore/QVector>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QDateTimeAxis>
#include <QDebug>
#include <map>
#include "RaceChartView.h"
#include "RaceCharts.h"


QT_CHARTS_USE_NAMESPACE

RaceCharts::RaceCharts(const std::string& title, const std::string& yAxisTitle, qreal maxX, qreal maxY, QWidget* parent = nullptr, unsigned short pid = 0) : QWidget(nullptr), m_chart(new QChart), m_series(new QLineSeries), trace_points(new QScatterSeries), maxXVal(maxX), incVal(maxX), m_pid(pid) {
	//	QChartView* chartView = new QChartView(m_chart);
	RaceChartView* chartView = new RaceChartView(m_chart);
	std::map<int, float> u;
	lapTelemetry.push_back(u);

	chartView->setRaceChart(this);
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

	trace_points->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	trace_points->setMarkerSize(7.5);

	m_chart->addAxis(yAxis, Qt::AlignLeft);
	m_series->attachAxis(yAxis);
	trace_points->attachAxis(yAxis);

	m_chart->addAxis(xAxis, Qt::AlignBottom);
	m_series->attachAxis(xAxis);
	trace_points->attachAxis(xAxis);

	m_chart->legend()->hide();
	m_chart->setTitle(titleStr);

	mainViewPort = new ViewPort(maxXVal);
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(chartView);
}


void RaceCharts::attachRaceChartSubject(RaceChartSubject* subject)
{
	this->m_subject = subject;
	this->m_subject->attachRaceChartObv(this);
}


unsigned short RaceCharts::getPid()
{
	return m_pid;
}

// Here we check for a few things:
// 1. The x point is greater than 0
// TODO: The x coordinates exists within some buffer.
// std::unordered_map, with near constant O(1) insertion and lookup
// because data is indexed with time stamp, there's garantee that it
// will be unique
void RaceCharts::setCursor(const QPointF& cursorPoint)
{
	trace_points->clear();
	trace_points->setPointLabelsVisible(true);
	trace_points->setColor(Qt::red);
	if (cursorPoint.x() >= 0) {
		trace_points->append(cursorPoint);
		m_subject->update(getPid(), cursorPoint.x());
	}
}


// This is the 'on call' function which is called when another cursor is traced
void RaceCharts::setCursorOnX(float xCoord)
{
	trace_points->clear();
	trace_points->setColor(Qt::red);
	trace_points->setPointLabelsVisible(true);

	if (xCoord >= 0)
	{
		auto currentLapData = lapTelemetry[currentLapCount];
		auto low = currentLapData.lower_bound((int)xCoord);

		if (low == currentLapData.begin() && low != currentLapData.end())
		{
			auto dataPoint = currentLapData.begin();
			trace_points->append(QPointF(xCoord, dataPoint->second));
		}
		else if (low != currentLapData.end())
		{
			auto boundaryCheck = std::prev(low);
			if (boundaryCheck != currentLapData.end()) {
				if (abs(xCoord - boundaryCheck->first) < abs(low->first - xCoord))
				{
					// Take the boundaryCheck's y value
					trace_points->append(QPointF(xCoord, boundaryCheck->second));
				}
				else {
					// Take the low's y value;
					trace_points->append(QPointF(xCoord, low->second));
				}
			}
			else {
				auto dataPoint = low;
				trace_points->append(QPointF(xCoord, dataPoint->second));
			}
		}

	}
}


void RaceCharts::setMouseStatus(bool status, QPointF mousePos)
{
	 
	this->mouseClicked = status;
}

void RaceCharts::setLastMousePos(QPointF mousePos)
{
	lastMousePos = mousePos;
}

QPointF RaceCharts::getLastMousePos()
{
	return lastMousePos;
}

bool RaceCharts::getMouseStatus()
{
	return mouseClicked;
}

/*
	TODO: Right now a single thread has access to a single
		  chart. When there are multiple threads there will
		  likely be race conditions. Refactor this later
		
	Refactor this using the viewPort struct
	Problems: Would changing view port affect writing data to other
			  parts of the graph?
*/
void RaceCharts::writeData(const QPointF& dataPoint) {

	if ((dataPoint.x() > maxXVal))
	{
		// We can safely clear the old series
		m_series->clear();
		m_xAxis->setRange(maxXVal, maxXVal + incVal);
		mainViewPort->setViewPort(maxXVal, maxXVal + incVal);
		maxXVal = maxXVal + incVal;
	}

	// Lap complete
	if (dataPoint.x() < lastXCoord) {
		currentLapCount++;

		std::map<int, float> u;
		lapTelemetry.push_back(u);

		m_series->clear();
		m_xAxis->setRange(0, incVal);
		mainViewPort->setViewPort(0, incVal);
		maxXVal = incVal;	// Rest
	}

	lastXCoord = dataPoint.x();
	m_series->append(dataPoint);


	// Get the unordered map from the vector,
	// then index into the unordered map by the x coordinate(Time stamp)
	lapTelemetry[currentLapCount].insert({ (int)dataPoint.x(), dataPoint.y() });
}

RaceCharts::~RaceCharts() {
	delete m_chart;
	delete m_series;
	delete mainViewPort;
}