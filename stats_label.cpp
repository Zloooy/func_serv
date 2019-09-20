#include "stats_label.h"
#include <sstream>
StatsLabel::StatsLabel(QString text, QWidget * parent):
    QLabel(parent),
    default_text(text)
{}
void StatsLabel::set_value(const double& value)
{
    setText(default_text + QString::number(value));
}
