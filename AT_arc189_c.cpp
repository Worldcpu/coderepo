#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,x,a[MN],b[MN],p[MN],q[MN],tmpa,tmpb,suma,sumb;
vector<int> opa,opb;

namespace LCS{
    vector<int> f;
    int mp[MN];

    int solve(){
        f.clear();
        for(int i=0;i<opa.size();i++){
            mp[opa[i]]=i+1;
        }
        for(auto p: opb){
            if(mp[p]==0) continue; 
            auto it = lower_bound(f.begin(), f.end(), mp[p]);
            if(it==f.end()) f.push_back(mp[p]);
            else *it = mp[p];
        }
        return f.size();
    }
}

signed main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        suma+=a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        sumb+=b[i];
    }
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        cin>>q[i];
    }

    int now=x;
    do{
        opa.push_back(now);
        tmpa+=a[now];      
        now=p[now];
    }while(now!=x);

    now=x;
    do{
        opb.push_back(now);
        tmpb+=b[now];      
        now=q[now];
    }while(now!=x);

    if(suma!=tmpa||sumb!=tmpb){
        cout<<-1<<'\n';
        return 0;
    }

    reverse(opa.begin(),opa.end());
    reverse(opb.begin(),opb.end());
    opa.pop_back();
    opb.pop_back();
    while(opa.size() && a[opa.back()]==0) opa.pop_back();
    while(opb.size() && b[opb.back()]==0) opb.pop_back();

    cout << opa.size() + opb.size() - LCS::solve() << '\n';
    return 0;
}
