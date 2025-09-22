#include "testlib.h"
#include <string>
#define N 200010
using namespace std;

struct node
{
    int to,next;
}e[N];

int st[N],tot,t[N],outs[N<<1],cnt,vis[N],k,n,m,q,x,y;

void add(int x,int y)
{
    e[++tot].to=y;
    e[tot].next=st[x];
    st[x]=tot;
}

int main(int argc, char* argv[]) 
{
    registerTestlibCmd(argc, argv);
    
    string sa = ans.readLine();
    string so = ouf.readLine();
    
    if (sa == "NIE" && so == sa)
        quitf(_ok, "Correct.");
    else if (sa == "NIE" && sa != so)
        quitf(_wa, "Wrong answer. expected \"NIE\"");
    else if (sa == "TAK" && sa != so)
        quitf(_wa, "Wrong answer. expected \"TAK\"");
    else
    {
        while(!ouf.eof())
            outs[++cnt] = ouf.readInt(), ouf.readEoln();
        n = inf.readInt(),m = inf.readInt();
        for (int i = 1; i <= m; i++)
            x = inf.readInt(),y = inf.readInt(),add(x, y);
        q = inf.readInt();
        for (int i = 1; i <= q; i++)
        {
            k = inf.readInt();
            for (int j = 1; j <= k; j++)
                t[j] = inf.readInt();
            int correct = 0;
            for (int j = 1; j <= cnt; j++)
                if (t[1] == outs[j])
                {
                    int flag = 1;
                    for (int l = 1;l <= k; l++)
                        if (t[l] != outs[j+l-1])
                            flag = 0;
                    if (flag)
                    {
                        correct = 1;
                        break;
                    }
                }
            if (!correct)
            {
                quitf(_wa, "Wrong answer. Path isn't in your answer.");
                return 0;
            }
        }
        for (int i = 1; i < cnt; i++)
        {
            int now = -1;
            for (int j = st[outs[i]]; j ; j = e[j].next)
                if (e[j].to == outs[i + 1])
                    now = j;
            if (now == -1)
            {
                quitf(_wa, "Wrong answer. Path not found.");
                return 0;
            }
            if (vis[now])
            {
                quitf(_wa, "Wrong answer. Path used twice.");
                return 0;
            }
            vis[now]=1;
        }
        if (outs[1] != 1)
        {
            quitf(_wa, "Wrong answer. Must start with 1.");
            return 0;
        }
        if (outs[cnt] != 1)
        {
            quitf(_wa, "Wrong answer. Must end with 1.");
            return 0;
        }
        quitf(_ok, "Correct.");
    }
}
