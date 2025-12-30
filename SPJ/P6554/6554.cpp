#include<bits/stdc++.h>
#include"../testlib.h"
using namespace std;
int main(int argc, char *argv[])
{
	registerTestlibCmd(argc,argv);
	double standard_out=ans.readReal(),
			your_out=ouf.readReal();
	if(fabs(standard_out-your_out)<=1e-2)
		quitf(_ok,"Answer is correct.");
	else quitf(_wa,"Answer is too big or too small.");
	return 0;
}