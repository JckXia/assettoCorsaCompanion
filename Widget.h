#ifndef  WIDGET_AUDIO_H

#include<QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
class XYSeriesIODevice;

QT_BEGIN_NAMESPACE
class QAudioInput;
class QAudioDeviceInfo;
QT_END_NAMESPACE


class Widget : public QWidget
{
	Q_OBJECT
public:
	explicit Widget(const QAudioDeviceInfo & deviceInfo, QWidget * parent = nullptr);
	~Widget();

private:
	XYSeriesIODevice* m_device = nullptr;
	QChart* m_chart;
	QLineSeries* m_series;
	QAudioInput* m_audioInput = nullptr;
};





#endif WIDGET_AUDIO_H