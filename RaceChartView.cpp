#include "RaceChartView.h"
#include <QDebug>
QT_USE_NAMESPACE
RaceChartView::RaceChartView(QChart* chart, QWidget* parent) : QChartView(chart, parent)
{

}

void RaceChartView::mouseMoveEvent(QMouseEvent* event) {
//	QDebug("%f\n", event->x());
	auto const widgetPos = event->localPos();
	auto const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
	auto const chartItemPos = chart()->mapFromScene(scenePos);
	auto const valueGivenSeries = chart()->mapToValue(chartItemPos);
	qDebug() << "VakSerues:" << valueGivenSeries;
//	qDebug("x %d y %d\n", event->x(), event->y());
	wprintf(L"Hello we are here\n");
	wprintf(L"Testin");
}