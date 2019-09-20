#ifndef FUNCTION_ARGUMENT_IGNORATOR
#define FUNCTION_ARGUMENT_IGNORATOR
#include <functional>
#include <iostream>
template <typename Rtype>
class FunctionArgumentIgnorator
{
    std::function<Rtype()> function;
    public:
    FunctionArgumentIgnorator(std::function<Rtype()>&& f):
        function(f)
        {}
    template<typename... Args>
    Rtype operator()(Args... args)
    {
       return function(); 
    }
    
};
#endif
