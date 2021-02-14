#include "RaceChartView.h"
#include "qdebug.h"
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
		auto thetaPos = valueGivenSeries.x() - lastMousePos.x();
		
		// Here we would need to scroll to the right
		if (thetaPos >= 0)
		{
			chart()->scroll(((chart()->plotArea().width())) / 60000, 0);
			m_chart->mainViewPort->moveViewPortRight(1);
		}
		else {
		// Scroll ot left, but have to make sure current x coord has to be greater than 0;
			auto viewPort = m_chart->mainViewPort->getViewPort();
 
			if (viewPort.first > 0) {
				chart()->scroll((chart()->plotArea().width() * -1) / 60000, 0);
			}
			m_chart->mainViewPort->moveViewPortLeft(1);
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