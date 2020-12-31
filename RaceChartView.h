#pragma once
#ifndef RACE_CHART_VIEW
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class RaceChartView : public QChartView
{
	Q_OBJECT
public:
	RaceChartView(QChart* chart, QWidget* parent = nullptr);

protected:
	virtual void mouseMoveEvent(QMouseEvent * event) override;
};

#endif