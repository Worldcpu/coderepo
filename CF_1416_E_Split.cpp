#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN];
set<pir> st;

void init(){
    st.clear();
    for(int i=1;i<=n;i++){
        a[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    int ze=0,two=-1,sh=0,f=1,ans=2*n;
    set<pir>::iterator it;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a[i]=x;
        if(two!=-1){
            st.clear();
            sh=0,f=1,ze+=2;
            if(x>two){
                st.insert(pir(x-two,x-two));
            }
        }else if(!st.empty()){
            ze++;
            if(f==-1){
                int lim=sh-x;
                while(!st.empty()&&(*st.begin()).second<=lim) st.erase(st.begin());
                if(!st.empty()&&(*st.begin()).first<=lim){
                    it=st.begin();
                    int tmp=(*it).second;
                    st.erase(it);
                    st.insert(pir(lim,tmp));
                }
            }else{

                int lim=sh-x;
                while(!st.empty()&&(*st.rbegin()).first>=lim) st.erase(--st.end());
                if(!st.empty()&&(*st.rbegin()).second>=lim){
                    int tmp=(*st.rbegin()).first;
                    st.erase(--st.end());
                    st.insert(pir(tmp,lim-1));
                }
            }
            sh=x-sh;
            f*=-1;
        }else{
            f=-1;
            sh=x;
            int lim=min(a[i-1]-1,x-1);
            if(lim>=1) st.insert(pir(1,lim));
        }
        two=-1;
        if(!(x&1)){
            int y=x/2,val=(y-sh)/f,pd=0;
            it=st.lower_bound(pir(val+1,-1e18));
            if(it!=st.begin()){
                it--;
                if(val>=(*it).first&&val<=(*it).second){
                    pd=1;
                }
            }
            if(pd) two=x/2;
            else st.insert(pir(val,val));
        }
    }
    if(two!=-1) ans-=ze+2;
    else if(!st.empty()) ans-=ze+1;
    else ans-=ze;
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}