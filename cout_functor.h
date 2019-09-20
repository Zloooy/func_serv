#ifndef COUT_FUNCTOR_H
#define COUT_FUNCTOR_H
#include <iostream>
#include <functional>
class CoutFunctor
{
    std::function<double(double)> f;
    std::string text;
    public:
    CoutFunctor(std::string t, std::function<double(double)> && f);
    void operator()(double d);
};
#endif
