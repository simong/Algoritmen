/*
 * File:   simpletest.h
 * Author: wijnand.schepens@hogent.be
 *
 * Defines macro's and functions for simple unit testing.
 *
 *
 * Macro's are used instead of regular functions because they allow the precompiler
 * to give information about file and line number.
 *
 * To make a unit test, simply use macro's like 'ut_check(condition)' or 'ut_check_equal(a, b)'.
 *
 * It is also possible to check whether exceptions have been thrown.
 *
 * Failed tests are reported to std::cout.
 *
 * The number of failed and passed checks can be retrieved through static variables 'ut_fail_count' and 'ut_pass_count'.
 *
 * 'ut_report()' prints an overview of test results.
 *
 * 'ut_reset()' can be used to reset the pass- and failcounters to zero.
 * 
 * 16 januari 2010: created unittest.h
 * 5 feb 2011: modified unittest.h into this non-class version
 *             simplifications, renaming, ...
 * Tested in Visual Studio 2010
 */

/* --- EXAMPLE  ---
void simpleTest()
{
	ut_check(10 < 20);
	ut_check_equal(10, 5+5);

	ut_report();
}

template <class T>
void stacktest() {
	ut_reset();
	ut_verbose = false;
	ut_print_filename();

	Stack<int> stack;

	ut_start_check_throw()      // behaves like "try {"
		
		ut_check(stack.isEmpty());
		ut_check_equal(0, stack.size());

		stack.push(10);
		ut_check(!stack.isEmpty());
		ut_check_equal(1, stack.size());

		int r = stack.pop();
		ut_check_equal(10, r);
		ut_check(stack.isEmpty());
		ut_check_equal(0, stack.size());

	ut_check_didnt_throw()      // behaves like "} catch ..."

    ut_start_check_throw()      
		stack.pop();
	ut_check_did_throw(const char *)

	ut_report();
}

int main()
{
	simpleTest();
	stacktest();
	return 0;
}

*/

#ifndef _SIMPLEUNITTEST_H_
#define	_SIMPLEUNITTEST_H_


// ___ INTERFACE ___

static int  ut_pass_count = 0;
static int  ut_fail_count = 0;
static bool ut_verbose = true;

#define ut_pass()                            __pass(__LINE__)

#define ut_fail(msg)                         __fail(__LINE__, msg)

#define ut_check(condition)                  ( (condition) ? ut_pass() : ut_fail(#condition))

#define ut_check_equal(expected, actual)     ( (expected==actual) ? ut_pass() : ut_fail("expected " #expected "==" #actual " but got "+ __to_string(expected) + "!=" + __to_string(actual) ) )

#define ut_start_check_throw()               try {

#define ut_check_didnt_throw()               ut_pass(); } catch(...) { ut_fail("unexpected exception"); }

#define ut_check_did_throw_any()             ut_fail("expected exception"); } catch(...) { ut_pass(); }

#define ut_check_did_throw(exctype)          ut_fail("expected exception"); } catch(exctype&) { ut_pass(); } catch(...) { ut_fail("expected exception type " #exctype); }

#define ut_print_filename()                  __print(__FILE__)                    

void ut_reset();

void ut_report();



// ___ IMPLEMENTATION ___

#include <string>
#include <iostream>
#include <sstream>

void ut_reset()
{
	ut_pass_count = 0; 
	ut_fail_count = 0;
}

void ut_report()
{
    if (ut_fail_count==0)
        std::cout << "Successfully passed " << ut_pass_count << " test(s)" << std::endl;
    else
        std::cout << "!!! FAILED " << ut_fail_count << " test(s) !!!" << std::endl;
}
   
void __fail(int line, const std::string &msg)
{
    std::cout << "line " << line << ": fail: " << msg << std::endl;
    ut_fail_count++;
}

void __pass(int line)
{
    if (ut_verbose)
		std::cout << "line " << line << ": OK" << std::endl;
    ut_pass_count++;
}


void __print(const char *s)
{
	std::cout << s << std::endl;
}


template <class T>
std::string __to_string(const T &x)
{
    std::ostringstream ss;
    ss << x;
    return ss.str();
}


#endif	// _SIMPLETEST_H_


