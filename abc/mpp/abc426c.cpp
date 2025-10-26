#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int INF=1e9;
int n,q;
set<pir> st;

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        st.insert(pir(i,1));
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        auto ret=(*st.lower_bound(pir(x+1,-INF)));
        int cnt=0;
        while((*st.begin())!=ret){
            cnt+=(*st.begin()).second;
            st.erase(st.begin());
        }
        cout<<cnt<<'\n';
        auto qwq=(*st.lower_bound(pir(y,-INF)));
        if(qwq.first==y){
            cnt+=qwq.second;
            st.erase(qwq);
        }
        st.insert(pir(y,cnt));
    }
    
    return 0;
}