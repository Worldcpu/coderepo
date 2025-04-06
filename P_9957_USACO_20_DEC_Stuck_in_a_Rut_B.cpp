#include <bits/stdc++.h>
using namespace std;
const int MN = 1e5 + 15;
int n;
struct node
{
    int x, y, id;
    bool stop;
};
int ans[MN];
bool cmpx(node x, node y)
{
    return x.x < y.x;
}
bool cmpy(node x, node y)
{
    return x.y < y.y;
}
vector<node> north, east;
bool stop[MN];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        char fx;
        int x, y;
        cin >> fx >> x >> y;
        if (fx == 'N')
        {
            north.push_back({x, y, i});
        }
        else
            east.push_back({x, y, i});
    }
    sort(north.begin(), north.end(), cmpx);
    sort(east.begin(), east.end(), cmpy);
    for (auto ed : east)
    {
        for (auto nd : north)
        {
            if (ed.x >= nd.x || nd.y >= ed.y || stop[nd.id] || stop[ed.id])
                continue;
            int from = abs(nd.x - ed.x), to = abs(ed.y-nd.y);
            if (from < to)
            {
                ans[ed.id] += 1 + ans[nd.id];
                stop[nd.id] = 1;
            }
            else if(to<from)
            {
                ans[nd.id] += 1 + ans[ed.id];
                stop[ed.id] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << '\n';
    }
    return 0;
}