#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int ML = 35, MN = 105;
string s1, s2;
int n, m;
ll f[MN][ML];
void solve()
{
    memset(f, 0, sizeof(f));
    for (int i = 0; i < s1.size(); i++)
    {
        int cnt, pos = i;
        f[i][0]=0;
        for (int j = 0; j < s2.size(); j++)
        {
            cnt = 0;
            while (s1[pos] != s2[j])
            {
                pos = (pos + 1) % s1.size();
                cnt++;
                if (cnt >= s1.size())
                {
                    cout<<0<<'\n';
                    return;
                }
            }
            pos = (pos + 1) % s1.size();
            f[i][0]+=cnt+1;
        }
    }
    for(int i=1;i<=30;i++){
        for(int j=0;j<s1.size();j++){
            f[j][i]=f[j][i-1]+f[(j+f[j][i-1])%s1.size()][i-1];
        }
    }
    ll ans=0,x=0;
    for(int i=30;i>=0;i--){
        if(x+f[x%s1.size()][i]<=s1.size()*n){
            x+=f[x%s1.size()][i];
            ans+=1<<i;
        }
    }
    cout<<ans/m<<'\n';
}

int main(){
    while (cin>>s2>>m>>s1>>n)
    {
        solve();
    }
    
}