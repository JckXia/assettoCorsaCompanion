

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>
#include <QtCharts/QLineSeries>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtCharts/QChartView>
#include "Widget.h"
#include "Dialog.h" 
#include "RaceCharts.h"
#include <windows.h>
#include "SharedFileOut.h"


struct AcDataObject {
	HANDLE hMapFile;
	unsigned char* mapFileBuffer;
};

AcDataObject physics_data;

AcDataObject graphics_data;

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




QT_CHARTS_USE_NAMESPACE

int main(int argc, char* argv[])
{
	initPhysicsMap();
	initGraphicsMap();
	QApplication a(argc, argv);

	RaceCharts* rChart = new RaceCharts(10, 5, nullptr);

	rChart->show();

	/*SPageFilePhysics* pf = (SPageFilePhysics*)physics_data.mapFileBuffer;
	SPageFileGraphic* gf = (SPageFileGraphic*)graphics_data.mapFileBuffer;

	while (gf->status != AC_OFF) {
		wprintf(L"Enter Assetto Corsa! \n");
	}


	QApplication a(argc, argv);

	const QAudioDeviceInfo inputDevice = QAudioDeviceInfo::defaultInputDevice();

	if (inputDevice.isNull())
	{
		return -1;
	}

	Widget w(inputDevice);
	w.show();*/

	//	Dialog dialog;

	//	dialog.show();
		//QtWidgetsApplication2 w;
		//QLineSeries* series = new QLineSeries();
		//series->append(0, 6);
		//series->append(2, 4);
		//series->append(3, 8);
		//series->append(7, 4);
		//series->append(10, 5);

		//QChart* chart = new QChart();
		//chart->legend()->hide();
		//chart->addSeries(series);
		//chart->createDefaultAxes();
		//chart->setTitle("Simple line chart example");


		//QChartView* chartView = new QChartView(chart);
		//chartView->setRenderHint(QPainter::Antialiasing);


		//QMainWindow window;

		//window.setCentralWidget(chartView);
		//window.resize(400, 300);
		//window.show();



		// w.show();
	return a.exec();
}
