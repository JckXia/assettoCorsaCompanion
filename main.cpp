#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "Dialog.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Dialog dialog;

	dialog.show();
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
