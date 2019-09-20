#ifndef STATS_LABEL_H
#define STATS_LABEL_H
#include <QLabel>
class StatsLabel: public QLabel
{
        QString default_text;
        public:
            StatsLabel(QString, QWidget * parent = nullptr);
            void set_value(const double& value);
};
#endif
