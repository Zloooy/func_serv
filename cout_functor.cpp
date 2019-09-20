#include "cout_functor.h"
CoutFunctor::CoutFunctor(std::string t, std::function<double(double)> && f):
f(f),
text(t)
{}

void CoutFunctor::operator()(double d)
{
    std::cout << text << f(d) << std::endl;
}
