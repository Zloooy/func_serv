#include <utility>
#include <functional>
#include <string>
#include <vector>
void broadcast(std::function<void()> function)
{
    function();
}
/*class stats_reciever
{
    double operator()()
    {
    }
}*/
double min_counter(double d, double& prev_min)
{
    prev_min = std::min(d, prev_min);
    return prev_min;
}
double max_counter(double d, double& prev_max)
{
    prev_max = std::max(d, prev_max); 
    return prev_max;
}
double sum_counter(double d, double& last_sum)
{
    last_sum += d;
    return last_sum;
}
void counter(int& last_count)
{
    last_count++;
}
//double square_deviation_counter(const std::vector<double>& storage)
