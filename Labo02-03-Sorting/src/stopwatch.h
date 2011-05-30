/* 
 * File:   stopwatch.h
 * Author: wijnand.schepens@hogent.be
 *
 * Klasse voor tijdsmetingen. Opgelet: nauwkeurigheid is platformafhankelijk!
 *
 * 30 dec 2009: created
 * 06 feb 2011: translated into English
 *              added func-versions with arguments
 */

#ifndef _STOPWATCH_H
#define	_STOPWATCH_H

#include <ctime>
#include <cassert>
#include <vector>
#include <algorithm>
#include <numeric>


class Stopwatch {
public:

    void start() {
        begin = clock();
    }

    void stop() {
        end = clock();
    }

    double time_in_sec() {
        return (double) (end - begin) / CLOCKS_PER_SEC;
    }

    // measure how long it takes to perform func(), in seconds
    template <typename FUNC>
    static double time_in_sec(FUNC &func)
    {
        Stopwatch sw;
        sw.start();
        func();
        sw.stop();
        return sw.time_in_sec();
    }

	// measure how long it takes to perform func(arg), in seconds
    template <typename FUNC, typename ARG>
    static double time_in_sec(FUNC &func, const ARG &arg)
    {
        Stopwatch sw;
        sw.start();
        func(arg);
        sw.stop();
        return sw.time_in_sec();
    }

	// measure how long it takes to perform func(arg), in seconds
    template <typename FUNC, typename ARG>
    static double time_in_sec(FUNC &func, ARG &arg)
    {
        Stopwatch sw;
        sw.start();
        func(arg);
        sw.stop();
        return sw.time_in_sec();
    }


	template <typename F>
	static void measure(unsigned int ncycles, F &func, std::vector<double> &times)
	{
		times.resize(0);
		times.reserve(ncycles);
		Stopwatch stopwatch;
		for (unsigned int i=0; i<ncycles; i++)
		{
			stopwatch.start();
			func();
			stopwatch.stop();
			times.push_back(stopwatch.time_in_sec());
		}									
	}

	template <typename FPRE, typename F, typename ARG>
	static void measure(unsigned int ncycles, FPRE &pre, F &func, ARG &arg, std::vector<double> &times)
	{
		times.resize(0);
		times.reserve(ncycles);
		Stopwatch stopwatch;
		for (unsigned int i=0; i<ncycles; i++)
		{
			pre(arg);
			stopwatch.start();
			func(arg);
			stopwatch.stop();
			times.push_back(stopwatch.time_in_sec());
		}									
	}

	// pre: times.size() > 2
	// post: times is sorted
	static void report_measurements(std::vector<double> &times)
	{
		using namespace std;

		unsigned int n = times.size();
		assert(n > 2);

		sort(times.begin(), times.end());

		double min = times[0];
		double max = times[n-1];

		double sum = accumulate(times.begin()+1, times.end()-1, 0.0); // exclude first and last
		double mean = sum / (n-2);

		double median = times[n/2];
	
		cout << "n      : " << n << endl
				  << " min   : " << min << endl
				  << " max   : " << max << endl
				  << " median: " << median << endl
				  << " mean* : " << mean << endl;
	}



private:
    clock_t begin, end;

};


#endif	/* _STOPWATCH_H */

