#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,q,a[MN];
bool flag[MN];
set<int> s;
int ans=0;

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        flag[x]^=1;
        if(flag[x]){
            s.insert(x);
            auto p=s.find(x);
            if(p!=s.begin()){
                auto lp=p;
                lp--;
                ans+=x-(*lp);      
            }
            if(p!=s.end()){
                auto rp=p;
                rp++;
                ans+=(*rp)-x;
            }
        }else {
            auto p=s.lower_bound(x),lp=p,rp=p;
            lp=p--;
            rp=p++;
            if(p==s.begin()){
                ans-=(*rp)-x;
            }
            if(rp==s.end()){
                ans-=x-(*lp);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
