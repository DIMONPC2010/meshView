################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
###################################################################

QWT_ROOT = C:/Qt/qwt-6.1.1
include( $${QWT_ROOT}/qwtconfig.pri )
include( $${QWT_ROOT}/qwtbuild.pri )
include( $${QWT_ROOT}/qwtfunctions.pri )

#QWT_OUT_ROOT = $${OUT_PWD}/../..
#QWT_OUT_ROOT = $${PWD}
QWT_OUT_ROOT = C:/Qt/Qwt-6.1.1

TEMPLATE     = app

INCLUDEPATH += $${QWT_ROOT}/src
DEPENDPATH  += $${QWT_ROOT}/src

!debug_and_release {

#    DESTDIR      = $${QWT_OUT_ROOT}/examples/bin
    DESTDIR      = $${QWT_OUT_ROOT}/MyBuild/bin
#    DESTDIR      = $${QWT_OUT_ROOT}
}
else {
    CONFIG(debug, debug|release) {

#        DESTDIR      = $${QWT_OUT_ROOT}/examples/bin_debug
        DESTDIR      = $${QWT_OUT_ROOT}/MyBuild/bin_debug
#        DESTDIR      = $${QWT_OUT_ROOT}
    }
    else {

#        DESTDIR      = $${QWT_OUT_ROOT}/examples/bin
        DESTDIR      = $${QWT_OUT_ROOT}/MyBuild/bin
#        DESTDIR      = $${QWT_OUT_ROOT}
    }
}

QMAKE_RPATHDIR *= $${QWT_OUT_ROOT}/lib

contains(QWT_CONFIG, QwtFramework) {

    LIBS      += -F$${QWT_ROOT}/lib
}
else {

    LIBS      += -L$${QWT_ROOT}/lib
}

qwtAddLibrary(qwt)

greaterThan(QT_MAJOR_VERSION, 4) {

    QT += printsupport
    QT += concurrent
}

contains(QWT_CONFIG, QwtOpenGL ) {

    QT += opengl
}
else {

    DEFINES += QWT_NO_OPENGL
}

contains(QWT_CONFIG, QwtSvg) {

    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}


win32 {
    contains(QWT_CONFIG, QwtDll) {
        DEFINES    += QT_DLL QWT_DLL
    }
}
