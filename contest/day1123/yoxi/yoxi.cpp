#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e18+7;
int n,a[MN],c[MN],cmx[MN],cmxp[MN],ans;
pir mx,semx;
set<pir> st;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>c[i];
    }

    fill(cmx+1,cmx+1+n,-INF);
    for(int i=1;i<=n;i++){
        if(cmx[c[i]]<a[i]){
            cmx[c[i]]=a[i];
            cmxp[c[i]]=i;
        }
    }
    for(int i=1;i<=n;i++){
        if(cmx[i]==-INF) continue;
        st.insert(pir(cmx[i],i)); 
    }
    
    if(st.size()==1){
        cout<<0<<'\n';
        return 0;
    }

    mx=(*prev(st.end()));   
    semx=(*prev(prev(st.end())));   

    for(int i=1;i<=n;i++){
        if(c[i]!=mx.second){
            int k=a[i]+mx.first;
            ans+=max(k,0ll);
        }else if(i!=cmxp[c[i]]){
            int k=a[i]+semx.first;
            ans+=max(k,0ll);
        }
    }
    cout<<ans<<'\n';
    return 0;
}