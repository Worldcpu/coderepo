#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int a[MN],n,m,ans=1;
set<int> s;
bool flag[MN];

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i];
        flag[a[i]]^=1;
        if(flag[a[i]]){
            s.insert(a[i]);
            auto p=s.find(a[i]);
            if(p!=s.begin()){
                auto lp=p;
                lp--;
                ans+=a[i]-(*lp)-1;
            }
            auto rp=p;
            rp++;
            if(rp!=s.end()){
                ans+=(*rp)-a[i]-1;
            }
        }else{
            auto p=s.lower_bound(a[i]);
            auto lp=p,rp=p;
            bool lpf=0,rpf=0;
            if(p!=s.begin()){
                lp--;
                lpf=1;
                ans-=a[i]-(*lp)-1;
            }
            if(p!=s.end()&&(++rp)!=s.end()){
                rpf=1;
                rp++;
                ans-=(*rp)-a[i]-1;
            }
            if(rpf&&lpf){
                ans+=(*rp)-(*lp)-1;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}