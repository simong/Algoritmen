/* 
 * File:   treesettest.cpp
 * Author: wijnand.schepens@hogent.be
 *
 * Last edit 2011/05/08
 */

#include <iostream>
#include <sstream>
#include <string>

#include "simpleunittest.h"

#include "functor.h"
#include "treeset.h"
//#include "treeset2.h"


int main() {

    TreeSet<int> s;
    s.add(25);
    s.add(1);
    s.add(4);
    s.add(7);
    s.add(9);
    s.add(14);
    s.add(21);
    s.add(17);
    s.add(40);
    s.add(33);
    s.add(57);
    s.add(45);
    try {
        std::cout << "K-de kleinste: " << s.k_de_kleinste(11) << std::endl;
        return 0;
    } catch (char* e) {
        std::cout << e << std::endl;
        return 1;
    }

    /*
     for (TreeSetIterator<int> it = s.begin(); it != s.end(); it++) {
     std::cout << *it << std::endl;
     }
     */

    ut_start_check_throw();
        TreeSet<int> set;

        ut_check(!set.contains(9));

        set.add(9);
        ut_check(set.contains(9));

        set.add(9);
        ut_check(set.contains(9));

        set.remove(9);
        ut_check(!set.contains(9));

        set.add(8);
        ut_check(set.contains(8));

        set.add(10);
        ut_check(set.contains(10));

        set.add(3);
        ut_check(set.contains(3));

        set.add(13);
        ut_check(set.contains(13));

        set.add(6);
        ut_check(set.contains(6));

        set.add(7);
        ut_check(set.contains(7));

        set.add(3);
        ut_check(set.contains(3));

        set.add(12);
        ut_check(set.contains(12));

        std::ostringstream ss;
        Printer p(" ", ss);
        set.visit(p);
        ut_check_equal(ss.str(), "3 6 7 8 10 12 13 ");

        set.remove(13); // left child
        ss.str("");
        set.visit(p);
        ut_check_equal(ss.str(), "3 6 7 8 10 12 ");

        set.remove(6); // right child
        ss.str("");
        set.visit(p);
        ut_check_equal(ss.str(), "3 7 8 10 12 ");

        set.remove(8); // root; two children
        ss.str("");
        set.visit(p);
        ut_check_equal(ss.str(), "3 7 10 12 ");

        set.clear();
        ut_check(!set.contains(8));

        set.add(8);
        ut_check(set.contains(8));

        set.add(10);
        ut_check(set.contains(10));
        ut_check(2 == set.size());

        ut_check_didnt_throw();

    ut_report();

    std::cin.get();
    return 0;
}

