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

HEADERS += ./include/raceChart.h ./include/raceChartSubject.h ./include/sharedFileout.h  ./include/timer.h  ./include/raceChartView.h
SOURCES +=  ./src/main.cpp  ./src/RaceCharts.cpp ./src/RaceChartSubject.cpp ./src/RaceChartView.cpp
QT += charts core gui multimedia widgets