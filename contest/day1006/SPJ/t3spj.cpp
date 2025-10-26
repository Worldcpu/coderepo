#include "testlib.h"
#include <iostream>
#include <fstream>

int n,m;

std::vector < std::string > initial_field;
std::vector < std::string > contestant_field;

inline std::string inc(const std::string& v)
{
    std::string res(v);
    res[m - 1] ++;
    for (int i = m - 1; i >= 0; i --) {
        if (res[i] > '9')
        {
            res[i] = '0';
            if (i > 0)
                res[i - 1] ++;
        }
    }
    return res;
};

bool eq(char a, char b)
{
    if (a == '*' || b == '*') return true;
    return a == b;
};

int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);
    n = inf.readInt();
    m = inf.readInt();
    initial_field.resize(n);
	contestant_field.reserve(n);
    for (int i = 0; i < n; i++)
        initial_field[i] = inf.readToken("[0-9*]{1,100000}");
    std::string contestant_initial_string = ouf.readToken("[0-9]{1,100000}");
    if (contestant_initial_string.size() != m)
        quitf(_wa, "Provided string with incorrect length");
    for (int i = 0; i < n; i ++)
    {
        contestant_field.push_back(contestant_initial_string);
        if (i + 1 < n)
            contestant_initial_string = inc(contestant_initial_string);
    }
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++)
            if (!eq(contestant_field[i][j], initial_field[i][j]))
                quitf(_wa, "Expected %c on position (%d,%d), got %c.", initial_field[i][j], i + 1, j + 1, contestant_field[i][j]);
    quitf(_ok, "Ok n = %d m = %d", n, m);
    return 0;
}
