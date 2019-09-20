#include <functional>
template<typename T>
void broadcast(T data, std::function<void(T)> function)
{
    function(std::forward<T>(data));
}
template <typename T, typename... F>
void broadcast(T data, std::function<void(T)> function, F... funcs)
{
    broadcast(data, function);
    broadcast(data, funcs...);
}
template <typename... F>
void broadcast(std::function<void()>function, F... funcs)
{
    broadcast(function);
    broadcast(funcs...);
}
