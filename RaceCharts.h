#pragma once
#ifndef  RACE_CHART_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>
#include <QMutex>
#include <QPair>
#include <vector>
#include <map>
#include "RaceChartSubject.h"
QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


class RaceChartSubject;

// Todo: Implement an adapter class
// between RaceCharts and ChartView
class RaceCharts : public QWidget
{
	Q_OBJECT
public:
	RaceCharts(const std::string& title, const std::string& yAxisTitle, qreal maxX, qreal maxY, QWidget* parent,unsigned short pid);
	void writeData(const QPointF& dataPoint);
	void setCursor(const QPointF& cursorPoint);
	void setCursorOnX(float xCoord);

	void attachRaceChartSubject(RaceChartSubject * rSubject);
	void setMouseStatus(bool status, QPointF mousePos);
	QPointF getLastMousePos();
	void setLastMousePos(QPointF mousePos);
	bool getMouseStatus();
	unsigned short getPid();
	~RaceCharts();
 
	
	struct ViewPort {
		ViewPort(int viewPortSize) : viewPortSize(viewPortSize) , leftViewPort(0), rightViewPort(viewPortSize) {}
		void setViewPort(int leftViewPort) { this->leftViewPort = leftViewPort; this->rightViewPort = leftViewPort + viewPortSize; };
		void setViewPort(int leftViewPort, int rightViewPort) {
			assert(leftViewPort >= 0);
			assert(rightViewPort - leftViewPort == viewPortSize);
			this->leftViewPort = leftViewPort;
			this->rightViewPort = rightViewPort;
		}
		void moveViewPortLeft(int tick) {
			if (leftViewPort - tick >= 0) {
				leftViewPort = leftViewPort - tick;
				rightViewPort = rightViewPort - tick;
			}
			else {
				leftViewPort = 0;
				rightViewPort = viewPortSize;
			}
			//}
		}

		void moveViewPortRight(int tick) {
			leftViewPort += tick;
			rightViewPort += tick;
		}

		QPair<float, float> getViewPort() {
			return qMakePair(leftViewPort, rightViewPort);
		}
	private:
		float leftViewPort;
		float rightViewPort;
		int	viewPortSize;
	};

	ViewPort* mainViewPort;
		
	QPointF lastMousePos;
	bool mouseClicked = false;
	std::vector<std::map<int, float>> lapTelemetry;
	int currentLapCount = 0;
	RaceChartSubject* m_subject;
	unsigned short m_pid;
	QChart* m_chart;
	QLineSeries* m_series;
	QScatterSeries* trace_points;
	const qreal incVal;
	qreal lastXCoord;
	QMutex m_lock;
	qreal maxXVal;
	QValueAxis* m_xAxis;
};

#endif // ! RACE_CHART_H