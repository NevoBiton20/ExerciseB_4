#include "Complex.hpp"

bool operator==(const Complex &first,const Complex &second)
{
    return (first.magnitude() == second.magnitude());
}

bool operator!=(const Complex &first,const Complex &second)
{
    return !(first == second);
}

bool operator<(const Complex &first,const Complex &second)
{
    return (first.magnitude() < second.magnitude());
}

bool operator>(const Complex &first,const Complex &second)
{
    return (first.magnitude() > second.magnitude());
}

bool operator<=(const Complex &first,const Complex &second)
{
    return (first == second || first < second);
}

bool operator>=(const Complex &first,const Complex &second)
{
    return (first == second || first > second);
}

ostream& operator<<(ostream& os, const Complex& cmp)
{
    os << cmp.getRe();
    os << " + ";
    if(cmp.getIm() != 1)
    {
        os << cmp.getIm();
    }
    os << "i";
    return os;
}