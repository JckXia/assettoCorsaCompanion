 
 

win32 {

    ## Windows common build here

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
HEADERS += Dialog.h event.h  RaceCharts.h RaceChartSubject.h RaceChartView.h SharedFileout.h Timer.h
SOURCES += main.cpp Dialog.cpp  RaceCharts.cpp RaceChartSubject.cpp RaceChartView.cpp
QT += charts core gui multimedia widgets