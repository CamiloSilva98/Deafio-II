TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        estacionservicio.cpp \
        main.cpp \
        rednacional.cpp \
        surtidor.cpp \
        tanque.cpp

HEADERS += \
    estacionservicio.h \
    rednacional.h \
    surtidor.h \
    tanque.h
