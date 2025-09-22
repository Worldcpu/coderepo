#include <bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
int n,q;
set<pir> s;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        auto it=s.lower_bound(pir(x,-1));
        bool flag=1;
        if(it!=s.end()){
            int l=(*it).first,r=(*it).second;
            if(l<y&&r>y) flag=0;
        }
        if(it!=s.begin()){
            auto pre=it;
            --pre;
            int l=(*pre).first,r=(*pre).second;
            if(r<y&&r>x) flag=0;
        }
        if(flag){
            s.insert(pir(x,y));
            cout<<"Yes\n";
        }else cout<<"No\n";
    }

    return 0;
}
