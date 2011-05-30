#include <string>
#include <iostream>

//#include "fastlist1.h"
#include "FastList.h"
#include "simpleunittest.h"

using namespace std;

struct StringHasher: public Hasher<string> {
    uint operator()(string s) {
        return (uint) (unsigned char) s[0];
    }
};

int main()
{


    StringHasher hasher;
	FastList<string> flist(hasher, 100);

	flist.add("aap");
	flist.add("noot");
	flist.add("mies");
	flist.add("wim");
	flist.add("zus");

	ut_check(flist.contains("aap"));
	ut_check(flist.contains("noot"));
	ut_check(flist.contains("mies"));
	
	ut_check(!flist.contains("kap"));
	ut_check(!flist.contains("ap"));

	string s = "";
	for (FastList<string>::const_iterator it = flist.begin(); it != flist.end(); it++)
	{
		s += *it;
	}
	ut_check_equal("aapnootmieswimzus", s);

	ut_report();

	//cin.get();
	return 0;
}
