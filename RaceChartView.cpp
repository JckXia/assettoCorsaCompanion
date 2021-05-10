
#include "qdebug.h"
#include <include/raceChartView.h>
QT_USE_NAMESPACE

 
RaceChartView::RaceChartView(QChart* chart, QWidget* parent) : QChartView(chart, parent)
{

}

void RaceChartView::mouseMoveEvent(QMouseEvent* event) {
 
	 
	auto const widgetPos = event->localPos();
	auto const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
	auto const chartItemPos = chart()->mapFromScene(scenePos);
	auto const valueGivenSeries = chart()->mapToValue(chartItemPos);
	if (m_chart->getMouseStatus())
	{
		//Assuming a horizonal drag
		//Mouse is clicked, this is precieved as a drag motion
		QPointF lastMousePos = m_chart->getLastMousePos();
		auto thetaPos =  valueGivenSeries.x() - lastMousePos.x();
		
		QValueAxis* xAxis = dynamic_cast<QValueAxis*> (chart()->axisX());

		if (thetaPos >= 0)
		{
			 
			qreal beforeVal = xAxis->max();
			qreal data = (chart()->plotArea().width() + 10000 ) / 60000;
			chart()->scroll(data, 0);
			qreal afterVal = xAxis->max();
			 
			m_chart->mainViewPort->moveViewPortRight(1);
		}
		else {
			qDebug() << "Neg Tehta " << thetaPos << endl;
			auto viewPort = m_chart->mainViewPort->getViewPort();
			//qDebug() << "ViewPort " << viewPort.first << endl;
			 
			qreal min = xAxis->min();
			qreal beforeVal;
			qreal afterVal;
			if (  viewPort.first > 0) {
			//	qDebug() << " What the hec " << xAxis->min() <<  endl;
				qreal scrollX = (chart()->plotArea().width() - 10000) / 60000;

				 beforeVal = xAxis->min();
			//	qDebug() << "Data Plot Width " << chart()->plotArea().width() << endl;
				QValueAxis* axis = dynamic_cast<QValueAxis*>(chart()->axisX());

				qDebug() << "X val " << axis->min() << endl;
				chart()->scroll(scrollX, 0);
				 afterVal = xAxis->min();
				 m_chart->mainViewPort->moveViewPortLeft(1);
			}
			 
		}
		m_chart->setLastMousePos((QPointF)valueGivenSeries);
		event->accept();	
	}
	m_chart->setCursor(QPointF(valueGivenSeries.x(), valueGivenSeries.y()));
}

void RaceChartView::mousePressEvent(QMouseEvent* event) {
	auto const widgetPos = event->localPos();
	auto const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
	auto const chartItemPos = chart()->mapFromScene(scenePos);
	auto const valueGivenSeries = chart()->mapToValue(chartItemPos);
 
	m_chart->setMouseStatus(true, QPointF(valueGivenSeries.x(),valueGivenSeries.y()));
}

void RaceChartView::mouseReleaseEvent(QMouseEvent* event) {
	auto const widgetPos = event->localPos();
	auto const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
	auto const chartItemPos = chart()->mapFromScene(scenePos);
	auto const valueGivenSeries = chart()->mapToValue(chartItemPos);

	m_chart->setMouseStatus(false, QPointF(valueGivenSeries.x(), valueGivenSeries.y()));
}

void RaceChartView::setRaceChart(RaceCharts* rChart) {
	this->m_chart = rChart;
}