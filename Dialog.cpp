
/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "dialog.h"

QT_CHARTS_USE_NAMESPACE
//! [0]
Dialog::Dialog()
{
	createMenu();
	createHorizontalGroupBox();
	createGridGroupBox();
	createFormGroupBox();
	//! [0]

	//! [1]
	bigEditor = new QTextEdit;
	bigEditor->setPlainText(tr("This widget takes up all the remaining space "
		"in the top-level layout."));

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
	//! [1]

	//! [2]
	//QVBoxLayout* mainLayout = new QVBoxLayout;
	////! [2] //! [3]
	//QPushButton* button1 = new QPushButton("One");
	//QPushButton* button2 = new QPushButton("Two");
	//QPushButton* button3 = new QPushButton("Three");
	//QVBoxLayout* verlayout = new QVBoxLayout;
	//verlayout->addWidget(button1);
	//verlayout->addWidget(button2);
	//verlayout->addWidget(button3);



	QGroupBox* raceChartsGroupBox = new QGroupBox;

	QLineSeries* series = new QLineSeries();

	series->append(0, 6);
	series->append(2, 4);
	series->append(3, 8);
	series->append(7, 4);

	QChart* chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(series);
	chart->createDefaultAxes();

	chart->setTitle("Simple Line Chart Example");

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QVBoxLayout* raceChartLayout = new QVBoxLayout;
	raceChartLayout->addWidget(chartView);
	raceChartsGroupBox->setLayout(raceChartLayout);


	QGroupBox* raceChartGroupBoxTwo = new QGroupBox;
	
	
	QLineSeries* secondSeies = new QLineSeries();
	secondSeies->append(0, 5);
	secondSeies->append(1, 5);
	secondSeies->append(4, 12);
	secondSeies->append(5, 1);
	QChart* chartTwo = new QChart();
	chartTwo->legend()->hide();
	chartTwo->addSeries(secondSeies);
	chartTwo->createDefaultAxes();
	chartTwo->setTitle("Second chart example");

	QChartView* chartViewTwo = new QChartView(chartTwo);
	chartViewTwo->setRenderHint(QPainter::Antialiasing);

	QVBoxLayout* raceChartLayoutTwo = new QVBoxLayout;
	raceChartLayout->addWidget(chartViewTwo);
	raceChartGroupBoxTwo->setLayout(raceChartLayoutTwo);


	QLineSeries* speedSeries = new QLineSeries();
	speedSeries->append(4, 5);
	speedSeries->append(100, 50);
	speedSeries->append(14, 23);
	speedSeries->append(2, 3);

	QChart* chartThree = new QChart();
	chartThree->legend()->hide();
	chartThree->addSeries(speedSeries);
	chartThree->createDefaultAxes();
	chartThree->setTitle("Third chart example");

	QChartView* chartViewThree = new QChartView(chartThree);
	chartViewThree->setRenderHint(QPainter::Antialiasing);
	raceChartLayout->addWidget(chartViewThree);




	
	QHBoxLayout* hBoxLayout = new QHBoxLayout;
	hBoxLayout->setMenuBar(menuBar);
	hBoxLayout->addWidget(raceChartsGroupBox);

	setLayout(hBoxLayout);
//	hBoxLayout->setMenuBar(menuBar);
	//hBoxLayout->addWidget(raceChartsGroupBox);
	//	hBoxLayout->addLayout(verlayout);
		//hBoxLayout->addWidget(gridGroupBox);
		//hBoxLayout->addWidget(gridGroupBoxTwo);

		//  mainLayout->setMenuBar(menuBar);
		  //! [3] //! [4]
		//  mainLayout->addWidget(horizontalGroupBox);
		 // mainLayout->addWidget(gridGroupBox);
		 // mainLayout->addWidget(gridGroupBox);
		  //! [4] //! [5]
//	setLayout(hBoxLayout);


	setWindowTitle(tr("Basic Layouts"));
}
//! [5]

//! [6]
void Dialog::createMenu()
{
	menuBar = new QMenuBar;

	fileMenu = new QMenu(tr("&File"), this);
	exitAction = fileMenu->addAction(tr("E&xit"));
	menuBar->addMenu(fileMenu);

	connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}
//! [6]

void Dialog::createVerticalGroupBox()
{

	QVBoxLayout* verticalBox = new QVBoxLayout;


}

//! [7]
void Dialog::createHorizontalGroupBox()
{
	horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
	QHBoxLayout* layout = new QHBoxLayout;

	for (int i = 0; i < NumButtons; ++i) {
		buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
		layout->addWidget(buttons[i]);
	}
	horizontalGroupBox->setLayout(layout);
}
//! [7]

//! [8]
void Dialog::createGridGroupBox()
{
	gridGroupBox = new QGroupBox(tr("Grid layout"));
	//! [8]
	QGridLayout* layout = new QGridLayout;

	//! [9]
	for (int i = 0; i < NumGridRows; ++i) {
		labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
		lineEdits[i] = new QLineEdit;
		layout->addWidget(labels[i], i + 1, 0);
		layout->addWidget(lineEdits[i], i + 1, 1);
	}

	//! [9] //! [10]
	smallEditor = new QTextEdit;
	smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
		"grid layout."));
	layout->addWidget(smallEditor, 0, 2, 4, 1);
	//! [10]

	//! [11]
	layout->setColumnStretch(1, 10);
	layout->setColumnStretch(2, 20);
	gridGroupBox->setLayout(layout);


	gridGroupBoxTwo = new QGroupBox(tr("Grid layout"));
	//! [8]
	QGridLayout* layoutTwo = new QGridLayout;

	//! [9]
	for (int i = 0; i < NumGridRows; ++i) {
		labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
		lineEdits[i] = new QLineEdit;
		layoutTwo->addWidget(labels[i], i + 1, 0);
		layoutTwo->addWidget(lineEdits[i], i + 1, 1);
	}

	//! [9] //! [10]
	smallEditorTwo = new QTextEdit;
	smallEditorTwo->setPlainText(tr("This is the second widget"));
	layoutTwo->addWidget(smallEditorTwo, 0, 2, 4, 1);
	//! [10]

	//! [11]
	layoutTwo->setColumnStretch(1, 10);
	layoutTwo->setColumnStretch(2, 20);
	gridGroupBoxTwo->setLayout(layoutTwo);
}
//! [11]

//! [12]
void Dialog::createFormGroupBox()
{
	formGroupBox = new QGroupBox(tr("Form layout"));
	QFormLayout* layout = new QFormLayout;
	layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
	layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
	layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
	formGroupBox->setLayout(layout);
}
//! [12]
