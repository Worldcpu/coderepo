#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    int ok = 0;
    int n = 5200;
    for (int i = 1; i <= n; ++i)
    {
        system("./gen");
        system("./sol < dp.in > sol.txt")?exit(0):void(0);
        double begin = clock();
        system("./mysol < dp.in > mysol.txt")?exit(0):void(0);
        double end = clock();

        double t = (end - begin);
        if (system("diff sol.txt mysol.txt"))
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
            printf("测试点#%d Accept 用时 %.0lfms\n", i, t);
            ok++; //AC数量+1
        }
    }
    printf("\n");
    double res = 100.0 * ok / n;
    printf("共 %d 组测试数据，AC数据 %d 组。 得分%.1lf。", n, ok, res);
}
