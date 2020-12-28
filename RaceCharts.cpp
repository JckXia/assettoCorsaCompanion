#pragma once
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QVBoxLayout>
#include "RaceCharts.h"

QT_CHARTS_USE_NAMESPACE

RaceCharts::RaceCharts(qreal maxX, qreal maxY, QWidget* parent) : QWidget(parent), m_chart(new QChart), m_series(new QLineSeries) {
	QChartView* chartView = new QChartView(m_chart);
	chartView->setMinimumSize(800, 600);
	m_chart->addSeries(m_series);

	QValueAxis* xAxis = new QValueAxis;
	xAxis->setRange(0, maxX);
	xAxis->setLabelFormat("%g");
	xAxis->setTitleText("Sample");

	QValueAxis* yAxis = new QValueAxis;
	yAxis->setRange(0, maxY);	// Considering that this is gear ratio, this would be from 0 to 6. (Most cars have 6 gears)
	yAxis->setTitleText("Gears");

	m_chart->addAxis(yAxis, Qt::AlignLeft);
	m_chart->addAxis(xAxis, Qt::AlignBottom);
	m_series->attachAxis(xAxis);
	m_chart->legend()->hide();
	m_chart->setTitle("Rpm");

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(chartView);
}

void RaceCharts::writeData(const QPointF& dataPoint) {

}

RaceCharts::~RaceCharts() {

}