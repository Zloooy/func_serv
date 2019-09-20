#ifndef GRAPH_H
#define GRAPH_H
#include "qcustomplot.h"
#include <iostream>
class Graph: public QCustomPlot
{
    Q_OBJECT
    QCPGraph * graphic;
    QTimer * animTimer = new QTimer(this);
    public:
        Graph(QWidget * parent = nullptr);
        void addData(double, double);
        void scale(const double&, const double&, const double&, const double&);
        void clear();
    signals:
        void selected_range(int, int);
    public slots:
        void selection_changed(bool);
};
#endif
