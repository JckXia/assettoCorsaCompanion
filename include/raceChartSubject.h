#pragma once
#ifndef  RaceChartSubject_H
#include <QVector>
#include <include/raceChart.h>

class RaceCharts;
/*
*	This class is a modification on the observers pattern. Essentially, the raceCharts will keep
*	a reference to this class. When onMouseEvent is detected, RaceChartSubject subject*
*	subject->update(int calledId) is called, where all of the RaceCharts instances under
*	subject calls raceChart->setCursor();
*   As of now we will simply make sure the coordinates get displayed at the same X coords,
*   after of which we will make more checks with respects to the buffer data, etc
*	TODO: This is not a good solution, we need to dervie from a more generic observer class
*/
class RaceChartSubject {
public:
	void attachRaceChartObv(RaceCharts* raceChart);
	void update(unsigned short callerPid);
	void update(unsigned short calledPid, float xCoord);
	void updateChartScroll(unsigned short callerPid);
private:
	QVector<RaceCharts*> m_observers;
};

#endif