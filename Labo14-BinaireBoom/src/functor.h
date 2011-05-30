/* 
 * File:   functor.h
 * Author: wijnand.schepens@hogent.be
 *
 * Created on 15 januari 2010, 16:05
 */

#ifndef _FUNCTOR_H
#define	_FUNCTOR_H

#include <string>
#include <iostream>


template <typename T>
void print(const T &x)
{
    std::cout << x << ' ';
}


class Printer
{
    std::ostream &os;
    std::string delim;
public:

    Printer(const std::string &delim_=" ", std::ostream &os_=std::cout)
    : delim(delim_), os(os_) {}
    
    template <typename T>
    void operator()(const T &x) const { os << x << delim; }
};


template <typename T>
struct Adder
{
    T sum;

    Adder() : sum(0) {}

    void operator()(const T& x) { sum += x; }
};


struct Counter
{
    int n;

    Counter() : n(0) {}

    template <typename T>
    void operator()(const T& x) { n++; }
};

#endif	/* _FUNCTOR_H */

