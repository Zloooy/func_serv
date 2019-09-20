#include "graph.h"
Graph::Graph(QWidget * parent):
    QCustomPlot(parent)
{
    setInteractions(QCP::iSelectPlottables);
    setSelectionRectMode(QCP::srmSelect);
    graphic = QCustomPlot::addGraph();
    graphic -> setPen(QColor(50, 50, 255, 255));
    graphic -> setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    graphic -> setAdaptiveSampling(true);
    graphic -> setSelectable(QCP::stDataRange);
    QCustomPlot::xAxis -> setRange(0, 100);
    QCustomPlot::replot();
    QObject::connect(graphic, qOverload<bool>(&QCPGraph::selectionChanged), this, &Graph::selection_changed);
}

void Graph::clear()
{
    graphic -> data() -> clear();
}

void Graph::addData(double x, double y)
{
    graphic -> addData(x, y);
}

void Graph::scale(const double& min_x, const double& min_y, const double& max_x, const double& max_y)
{
    QCustomPlot::xAxis -> setRange(min_x, max_x);    
    QCustomPlot::yAxis -> setRange(min_y, max_y);
}

void Graph::selection_changed(bool selected)
{
    if (selected)
    {
        QCPDataRange range = graphic -> selection().dataRange(0);
        selected_range(range.begin(), range.end());
    }
}
