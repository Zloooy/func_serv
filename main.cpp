#include <iostream>
#include <functional>
#include <vector>
#include <QApplication>
#include <QPushButton>
#include "broadcast_functions.h"
#include "cout_functor.h"
#include "server.h"
#include "function_argument_ignorator.h"
#include "main_window.h"
#include "stats_tab.h"
#include "graph.h"
#include "stats_label.h"

extern void broadcast(std::function<void()>);
extern double min_counter(double, double&);
extern double max_counter(double, double&);
extern double sum_counter(double, double&);
extern double square_deviation_counter(std::vector<double>&);

extern void counter(int&);
int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    //UI
    MainWindow main_window;
    StatsTab stats_tab;
    QPushButton cancel_button("Сброс"), zoom_out_button("Весь график");
    Graph graph;
    StatsLabel min_label("Минимум:"), max_label("Максимум:"), count_label("Количество:");
    main_window.addWidgetAtRight(&cancel_button);
    main_window.addWidgetAtRight(&zoom_out_button);
    main_window.addTab(&graph, "График");
    main_window.addTab(&stats_tab, "Статистика");
    stats_tab.addStats(&min_label);
    stats_tab.addStats(&max_label);
    stats_tab.addStats(&count_label);
    main_window.show();
    //Variables
    using std::placeholders::_1;
    double min, max, sum, buffer;
    int count;
    std::atomic<bool> is_cleared(true), is_running(true), variables_set(false);
    std::vector<double> storage;
    ThreadSafeQueue<double> q;
    //Functions
    std::vector<std::function<void(double)>> double_functions = {
        [&storage](double d){storage.push_back(d);},
        CoutFunctor("Sum:", std::bind(sum_counter, _1, std::ref(sum))),
        CoutFunctor("Min:", std::bind(min_counter, _1, std::ref(min))),
        CoutFunctor("Max:", std::bind(max_counter, _1, std::ref(max))),
        CoutFunctor("Avg:", FunctionArgumentIgnorator<double>(std::bind(std::divides<double>(), std::cref(sum), std::cref(count)))),
        std::bind(&Graph::addData, &graph, std::cref(count), _1)};
    std::vector<std::function<void()>> void_functions = {
        std::bind(counter, std::ref(count)),
    };
    std::vector<std::function<void()>> visualization_functions = {
        [&graph, &min, &max, &count](){graph.scale(0, min, count, max); graph.replot();},
        std::bind(&StatsLabel::set_value, &min_label, std::cref(min)),
        std::bind(&StatsLabel::set_value, &max_label, std::cref(max)),
        std::bind(&StatsLabel::set_value, &count_label, std::cref(count))
        /*[&storage](){
            for(std::vector<double>::iterator it = storage.begin();it != storage.end(); it++) std::cout << (*it) << " ";
            std::cout << std::endl;
        }*/
    };
    QObject::connect(&cancel_button, &QPushButton::clicked, [&is_cleared, &q](){is_cleared = true; q.push(1);});
    Server serv(&q, 8081);
    std::thread t([&is_running, &q, &is_cleared, &variables_set, &buffer, &min, &max, &sum, &count, &graph, &double_functions, &void_functions, &visualization_functions](){
    while(is_running){
        std::cout << "loop start" << std::endl;
        buffer = q.wait_and_get_front();
        if (is_cleared)
        {
            //q.clear();
            is_cleared = false;
            graph.clear();
            sum = 0;
            count = 0;
            variables_set = false;
        }
        else
        {
            if (!variables_set)
            {
                min = buffer;
                max = buffer;
                variables_set = true;
            }
                std::for_each(void_functions.begin(), void_functions.end(), [](std::function<void()> f){f();});
                std::for_each(double_functions.begin(), double_functions.end(), [&buffer](std::function<void(double)> f){f(buffer);});
                std::cout << "ran all necessary functions" << std::endl;
                std::cout << "loop end" << std::endl;
        }
            std::for_each(visualization_functions.begin(), visualization_functions.end(), [](std::function<void()> f){f();});
        }
   });
        t.detach();
    return app.exec();
}
