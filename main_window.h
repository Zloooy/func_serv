#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
class MainWindow: public QWidget
{
    QTabWidget * tabs = new QTabWidget();
    QVBoxLayout * right_layout = new QVBoxLayout();
    public:
        MainWindow();
        void addTab(QWidget *, const QString&);
        void addWidgetAtRight(QWidget *);
};
#endif
