#include <bits/stdc++.h>
using namespace std;
const int MN = 128;
char op[MN];
int num[MN], n, maxx[MN][MN], minn[MN][MN];
vector<int> ans;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> op[i] >> num[i];
        op[i + n] = op[i];
        num[i + n] = num[i];
    }
    memset(maxx, 128, sizeof(maxx));
    memset(minn, 0x3f, sizeof(minn));
    for (int i = 1; i <= 2 * n; i++)
    {
        maxx[i][i] = minn[i][i] = num[i];
    }
    for (int len = 2; len <= n; len++)
    {
        for (int l = 1; l + len - 1 <= 2 * n; l++)
        {
            int r = l + len - 1;
            for (int k = l; k < r; k++)
            {
                if (op[k+1] == 't')
                { //+
                    maxx[l][r] = max(maxx[l][r], maxx[l][k] + maxx[k + 1][r]);
                    minn[l][r] = min(minn[l][r], minn[l][k] + minn[k + 1][r]);
                }
                else
                {
                    maxx[l][r] = max({maxx[l][r], maxx[l][k] * maxx[k + 1][r], minn[l][k] * minn[k + 1][r], minn[l][k] * maxx[k + 1][r],maxx[l][k]*minn[k+1][r]});
                    minn[l][r] = min({minn[l][r], maxx[l][k] * maxx[k + 1][r], minn[l][k] * minn[k + 1][r], minn[l][k] * maxx[k + 1][r],maxx[l][k]*minn[k+1][r]});
                }
            }
        }
    }
    int ma=-1e9;
    for(int i=1;i<=n;i++){
        if(maxx[i][i+n-1]>ma){
            ma=maxx[i][i+n-1];
            ans.clear();
            ans.push_back(i);
        }
        else if(ma==maxx[i][i+n-1]){
            ans.push_back(i);
        }
    }
    cout<<ma<<'\n';
    for(auto v:ans){
        cout<<v<<" ";
    }
    return 0;
}