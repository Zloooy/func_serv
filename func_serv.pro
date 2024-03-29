######################################################################
# Automatically generated by qmake (3.1) Fri Sep 20 01:02:49 2019
######################################################################

TEMPLATE = app
TARGET = func_serv
INCLUDEPATH += .
QT += core gui widgets printsupport

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += broadcast_functions.h \
           cout_functor.h \
           function_argument_ignorator.h \
           main_window.h \
           stats_tab.h \
           qcustomplot.h \
           server.h \
           thread_safe_queue.h \
           graph.h \
           stats_label.h
SOURCES += cout_functor.cpp \
           data_processing_functions.cpp \
           main.cpp \
           main_window.cpp \
           stats_tab.cpp \
           qcustomplot.cpp \
           server.cpp \
           graph.cpp \
           stats_label.cpp
