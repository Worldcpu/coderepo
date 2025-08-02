#include <iostream>
#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    system("chcp 65001");
    int ok = 0;
    int n = 10000;
    for (int i = 1; i <= n; ++i)
    {
        system("gen.exe");
        system("sol.exe < dp.in > sol.txt");
        cerr<<"OK'\n";
        double begin = clock();
        system("mysol.exe < dp.in > mysol.txt");
        double end = clock();

        double t = (end - begin);
        if (system("fc sol.txt mysol.txt"))
        {
            printf("测试点#%d Wrong Answer\n", i);
            break;
        }
        else if (t > 1000) //1秒
        {
            printf("测试点#%d Time Limited Exceeded 用时 %.0lfms\n", i, t);
        }
        else
        {
            printf("测试点#%d Accepted 用时%.0lfms\n", i, t);
            ok++; //AC数量+1
        }
    }
    printf("\n");
    double res = 100.0 * ok / n;
    printf("共 %d 组测试数据，AC数据 %d 组。 得分%.1lf。", n, ok, res);
    system("pause");
}
