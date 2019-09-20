#include "stats_tab.h"
StatsTab::StatsTab(QWidget * parent):
    QWidget(parent)
{
    setLayout(layout);
}
void StatsTab::addStats(QLabel * stats)
{
    layout -> addWidget(stats);
}
