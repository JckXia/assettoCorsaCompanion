#include "RaceChartSubject.h"
#include <QDebug>
QT_CHARTS_USE_NAMESPACE
void RaceChartSubject::attachRaceChartObv(RaceCharts* raceChart) {
	m_observers.push_back(raceChart);
}
////
void RaceChartSubject::update(unsigned short callerPid) {
	for (int i = 0; i < m_observers.size(); i++)
	{
		if (m_observers[i]->getPid() != callerPid) {
			//qDebug() << m_observers[i]->getPid() << "\n";
			//  Call a function on the raceChart to display the corresponding x value
			//	m_observers[i]->setCursor();
		}
	}
}

void RaceChartSubject::update(unsigned short callerPid , float xCoord) {
	for (int i = 0; i < m_observers.size(); i++)
	{
		if (m_observers[i]->getPid() != callerPid) {
			m_observers[i]->setCursorOnX(xCoord);
			//qDebug() << m_observers[i]->getPid() << "\n";
			//  Call a function on the raceChart to display the corresponding x value
			//	m_observers[i]->setCursor();
		}
	}
}

void RaceChartSubject::updateChartScroll(unsigned short callerPid) {	
	for (int i = 0; i < m_observers.size(); i++)
	{
		if (m_observers[i]->getPid() != callerPid) {

		}
	}
}