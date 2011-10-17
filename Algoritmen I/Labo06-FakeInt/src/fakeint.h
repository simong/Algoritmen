/* 
 * File:   fakeint.h
 * Author: Wijnand
 *
 * Created on 18 februari 2010, 10:43
 */

#ifndef _FAKE_INT_
#define	_FAKE_INT_

#include <iostream>

struct Counter
{
public:
    int n_def_ctor;
    int n_int_ctor;
    int n_copy_ctor;
    int n_dtor;
    int n_assign;
    int n_equal;
    int n_not_equal;
    int n_less_than;
    int n_less_than_or_equal;
    int n_greater_than;
    int n_greater_than_or_equal;
	int n_plus;
	int n_minus;
	int n_plus_equal;
	int n_minus_equal;

    Counter() { reset(); }

    void reset() {
        n_def_ctor = 0;
        n_int_ctor = 0;
        n_copy_ctor = 0;
        n_dtor = 0;
        n_assign = 0;
        n_equal = 0;
        n_not_equal = 0;
        n_less_than = 0;
        n_less_than_or_equal = 0;
        n_greater_than = 0;
        n_greater_than_or_equal = 0;
		n_plus = 0;
		n_minus = 0;
		n_plus_equal = 0;
		n_minus_equal = 0;
    }

    void report(const char *message="", std::ostream &out=std::cout) const
    {
        out << "--- " << message << " ---" << std::endl;
        out << "default constructor:" << n_def_ctor << std::endl;
        out << "int-constructor    :" << n_int_ctor << std::endl;
        out << "copy constructor   :" << n_copy_ctor << std::endl;
        out << "destructor         :" << n_dtor << std::endl;
        out << "operator=          :" << n_assign << std::endl;
        out << "operator==         :" << n_equal << std::endl;
        out << "operator!=         :" << n_not_equal << std::endl;
        out << "operator<          :" << n_less_than << std::endl;
        out << "operator<=         :" << n_less_than_or_equal << std::endl;
        out << "operator>          :" << n_greater_than << std::endl;
        out << "operator>=         :" << n_greater_than_or_equal << std::endl;
        out << "operator+          :" << n_plus << std::endl;
        out << "operator-          :" << n_minus << std::endl;
		out << "operator+=         :" << n_plus_equal << std::endl;
		out << "operator-=         :" << n_minus_equal << std::endl;
    }
};

struct FakeInt {
    static Counter counter;
    int value;

    static void report(const char *message="", std::ostream &out=std::cout)
    {
        counter.report(message, out);
    }

    static void reset()
    {
        counter.reset();
    }

    FakeInt() : value() {
        counter.n_def_ctor++;
    }

    FakeInt(int value_) : value(value_) {
        counter.n_int_ctor++;
    }

    FakeInt(const FakeInt &t_) : value(t_.value) {
        counter.n_copy_ctor++;
    }

//    FakeInt(int &value_) : value(value) {
//        counter.n_copy_ctor++;
//    }
//
    ~FakeInt() {
        counter.n_dtor++;
    }

    void operator=(const FakeInt &t_) {
        value = t_.value;
        counter.n_assign++;
    }

    void operator=(int value_) {
        value = value_;
        counter.n_assign++;
    }

    bool operator==(const FakeInt &t_) const {
        counter.n_equal++;
        return value == t_.value;
    }

    bool operator!=(const FakeInt &t_) const {
        counter.n_not_equal++;
        return value != t_.value;
    }

    bool operator<(const FakeInt &t_) const {
        counter.n_less_than++;
        return value < t_.value;
    }

    bool operator<=(const FakeInt &t_) const {
        counter.n_less_than_or_equal++;
        return value <= t_.value;
    }

    bool operator>(const FakeInt &t_) const {
        counter.n_greater_than++;
        return value > t_.value;
    }

    bool operator>=(const FakeInt &t_) const {
        counter.n_greater_than_or_equal++;
        return value >= t_.value;
    }

	FakeInt operator+(const FakeInt &t_) const {
        counter.n_plus++;
        return FakeInt(value + t_.value);
    }

	FakeInt operator-(const FakeInt &t_) const {
        counter.n_minus++;
        return FakeInt(value - t_.value);
    }

	FakeInt &operator+=(const FakeInt &t_) {
        counter.n_plus_equal++;
        value += t_.value;
		return *this;
    }

	FakeInt &operator-=(const FakeInt &t_) {
        counter.n_minus_equal++;
        value -= t_.value;
		return *this;
    }

};

std::ostream &operator<<(std::ostream &out, FakeInt f)
{
    return out << f.value;
}

Counter FakeInt::counter;

#endif	

