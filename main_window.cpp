#include "main_window.h"
MainWindow::MainWindow():
    QWidget()
{
    QHBoxLayout * main_layout = new QHBoxLayout();
    QWidget::setLayout(main_layout);
    main_layout -> addWidget(tabs);
    QWidget * right_widget = new QWidget();
    right_widget -> setLayout(right_layout);
    main_layout -> addWidget(right_widget);
}
void MainWindow::addTab(QWidget * tab, const QString& name)
{
    tabs -> addTab(tab, name);
}
void MainWindow::addWidgetAtRight(QWidget * widget)
{
    right_layout -> addWidget(widget);
}
