

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#include "QtWidgetsApplication2.h"
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "RaceCharts.h"
#include <windows.h>
#include <thread>
#include "Timer.h"
#include "SharedFileOut.h"



#define MAX_X 60000

struct AcDataObject {
	HANDLE hMapFile;
	unsigned char* mapFileBuffer;
};

AcDataObject physics_data;

AcDataObject graphics_data;

AcDataObject static_data;

void initPhysicsMap() {
	TCHAR szName[] = TEXT("Local\\acpmf_physics");
	physics_data.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFilePhysics), szName);
	if (!physics_data.hMapFile) {
		//	std::cout << "Failed to create this mapping object!" << std::endl;
		exit(1);
		//	return 1;
	}
	physics_data.mapFileBuffer = (unsigned char*)MapViewOfFile(physics_data.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics));
	if (!physics_data.mapFileBuffer) {
		//	std::cout << "Map View mem mapped creation failed!" << std::endl;
		exit(1);
		//	return 1;
	}
	wprintf(L"Physics Mem Map creation succesful!\n");
	//	std::cout << "Physics Memory Map Creation Successful!" << std::endl;
}


void initGraphicsMap() {
	TCHAR szName[] = TEXT("Local\\acpmf_graphics");
	graphics_data.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFileGraphic), szName);
	if (!graphics_data.hMapFile) {
		//	std::cout << "Failed to create this mapping object!" << std::endl;
		exit(1);
		//	return 1;
	}
	graphics_data.mapFileBuffer = (unsigned char*)MapViewOfFile(graphics_data.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphic));
	if (!graphics_data.mapFileBuffer) {
		//	std::cout << "Map View mem mapped creation failed!" << std::endl;
		exit(1);
		//	return 1;
	}
	wprintf(L"Graphics map creation successful!\n");
	//std::cout << "Graphics Memory Map Creation Successful!" << std::endl;
}

void initStaticMap() {
	TCHAR szName[] = TEXT("Local\\acpmf_static");
	static_data.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFileStatic), szName);
	if (!static_data.hMapFile)
	{
		exit(1);
	}
	static_data.mapFileBuffer = (unsigned char*)MapViewOfFile(static_data.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileStatic));
	if (!static_data.mapFileBuffer)
	{
		exit(1);
	}
}



void callThis(QVector<RaceCharts*> chart) {
	SPageFilePhysics* pf = (SPageFilePhysics*)physics_data.mapFileBuffer;
	SPageFileGraphic* gf = (SPageFileGraphic*)graphics_data.mapFileBuffer;
	int gearT = 4;

	//	chart->writeData(QPointF(1000, (float) gearT));
	if (gf->status != AC_OFF) {
		//	qDebug("Current Gear %d\n", pf->gear);
		int gear = pf->gear == 0 ? 0 : pf->gear - 1;
		int normalizedTime = gf->iCurrentTime;


		std::thread t1([=]() {
			chart[0]->writeData(QPointF(normalizedTime, gear));
			});
		std::thread t2([=]() {
			chart[1]->writeData(QPointF(normalizedTime, pf->rpms));
			});
		std::thread t3([=]() {
			chart[2]->writeData(QPointF(normalizedTime, pf->brake));
			});
		std::thread t4([=]() {
			chart[3]->writeData(QPointF(normalizedTime, pf->speedKmh));
			});

		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}

}

void timerCallBack(QVector<RaceCharts*> chart) {

	Timer* t = new Timer(1ms);
	t->setInterval(100ms, callThis, chart);
}


QT_CHARTS_USE_NAMESPACE

int main(int argc, char* argv[])
{
	initPhysicsMap();
	initGraphicsMap();
	initStaticMap();

	QApplication a(argc, argv);

	RaceChartSubject* chartManager = new RaceChartSubject();

	QWidget* window = new QWidget;
	window->setWindowTitle("Assetto Corsa Companion");

	QVector<RaceCharts*>chartObjects;
	const std::string gearChartTitle = "Gears Chart";
	const std::string gearAxisTitle = "Gear";
	RaceCharts* gearChart = new RaceCharts(gearChartTitle, gearAxisTitle, MAX_X, 6, nullptr, 1);
	gearChart->attachRaceChartSubject(chartManager);

	// TODO Extract the car's actual max revs from the static mapped memory
	const std::string rpmChartTitle = "RPM Chart";
	const std::string rpmAxisTitle = "RPM";
	RaceCharts* rpmChart = new RaceCharts(rpmChartTitle, rpmAxisTitle, MAX_X, 6000, nullptr, 2);
	rpmChart->attachRaceChartSubject(chartManager);

	const std::string brakeChartTitle = "Brake Chart";
	const std::string brakeAxisTitle = "Brake Pressure";
	RaceCharts* brakeChart = new RaceCharts(brakeChartTitle, brakeAxisTitle, MAX_X, 1, nullptr, 3);
	brakeChart->attachRaceChartSubject(chartManager);

	const std::string speedChartTitle = "Speed(kmh) Chart";
	const std::string speedAxisTitle = "Speed (km/h)";
	RaceCharts* speedChart = new RaceCharts(speedChartTitle, speedAxisTitle, MAX_X, 250, nullptr, 4);
	speedChart->attachRaceChartSubject(chartManager);


	chartObjects.push_back(gearChart);
	chartObjects.push_back(rpmChart);
	chartObjects.push_back(brakeChart);
	chartObjects.push_back(speedChart);


	QHBoxLayout* mainGrid = new QHBoxLayout;

	QVBoxLayout* colTwo = new QVBoxLayout;
	colTwo->addWidget(brakeChart);
	colTwo->addWidget(speedChart);

	QVBoxLayout* vBoxLayout = new QVBoxLayout;
	vBoxLayout->addWidget(gearChart);
	vBoxLayout->addWidget(rpmChart);


	mainGrid->addLayout(vBoxLayout);
	mainGrid->addLayout(colTwo);
	window->setLayout(mainGrid);

	std::thread timerThread(timerCallBack, chartObjects);

	window->show();
	timerThread.join();

	return a.exec();
}
