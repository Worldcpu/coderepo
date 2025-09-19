#include <iostream>
#include <cstdio>
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
        system("./gen");
        system("./sol < dp.in > sol.txt")?exit(0):void(0);

        double begin = clock();

        // 用 /usr/bin/time -v 获取内存
        int ret = system("/usr/bin/time -v ./mysol < dp.in > mysol.txt 2> memlog.txt");
        double end = clock();

        double t = (end - begin);
        
        // 解析 memlog.txt 检查内存
        FILE *fp = fopen("memlog.txt", "r");
        long maxrss = 0;
        if (fp)
        {
            char line[256];
            while (fgets(line, sizeof(line), fp))
            {
                if (sscanf(line, "Maximum resident set size (kbytes): %ld", &maxrss) == 1)
                    break;
            }
            fclose(fp);
        }

        // 假设 MLE 阈值 512MB
        if (maxrss > 1024 * 1024)
        {
            printf("测试点#%d Memory Limit Exceeded 用量 %.0lf MB\n", i, maxrss / 1024.0);
            break;
        }
        else if (system("diff sol.txt mysol.txt"))
        {
            printf("测试点#%d Wrong Answer\n", i);
            break;
        }
        else if (t > 1000) // 1秒
        {
            printf("测试点#%d Time Limited Exceeded 用时 %.0lfms\n", i, t);
        }
        else
        {
            cerr<<"ACCEPT\n";
            ok++;
        }
    }
    printf("\n");
    double res = 100.0 * ok / n;
    printf("共 %d 组测试数据，AC数据 %d 组。 得分%.1lf。\n", n, ok, res);
}
