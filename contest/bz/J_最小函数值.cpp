#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Node
{
    int a, b, c, x,v;

    Node(int aa = 0, int bb = 0, int cc = 0, int xx = 0)
    {
        a = aa, b = bb, c = cc, x = xx;
        setv();
    }

    void setv(){
        v=a*x*x+b*x+c;
    }

    friend bool operator<(const Node &X, const Node &Y)
    {
        return X.v>Y.v;
    }
};
int n, m;
priority_queue<Node> q;

signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        q.push(Node(a, b, c, 1));
    }
    while (m--)
    {
        auto tp = q.top();
        q.pop();
        cout << tp.v << ' ';
        tp.x++;
        tp.setv();
        q.push(tp);
    }
    return 0;
}