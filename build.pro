 win32 {

 
   contains(QMAKE_HOST.arch, x86):{
   message('Building with x86')
   QMAKE_LFLAGS *= /MACHINE:X86
}

contains(QMAKE_HOST.arch, x86_64):{
    message('Building with x86_64')
QMAKE_LFLAGS *= /MACHINE:X64
}
}

 
CONFIG += no_fixpath

INCLUDEPATH += include

HEADERS += ./include/raceChart.h ./include/raceChartSubject.h SharedFileout.h  ./include/timer.h RaceChartView.h
SOURCES += main.cpp  RaceCharts.cpp RaceChartSubject.cpp RaceChartView.cpp
QT += charts core gui multimedia widgets