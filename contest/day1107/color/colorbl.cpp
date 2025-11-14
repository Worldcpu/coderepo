#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=22;
int n,ans=1e9,a[MN],b[MN];
vector<pir> st;

bool check(){
    for(int i=0;i<st.size();i++){
        if(st[i].first!=st[i].second) return 0;
    }
    return 1;
}

void dfs(int stp){
    if(stp>ans||stp>18) return;
    if(check()){
        ans=min(ans,stp);
        return;
    }
    for(int i=0;i<st.size();i++){
        for(int j=0;j<st.size();j++){
            if(i==j) continue;
            if(st[j].second==0){
                if(st[i].first!=0){
                    swap(st[j].second,st[i].first);
                    dfs(stp+1);
                    swap(st[j].second,st[i].first);
                }else if(st[i].second!=0){
                    swap(st[j].second,st[i].second);
                    dfs(stp+1);
                    swap(st[j].second,st[i].second);
                }
            }else if(st[j].first==0){
                if(st[i].first!=0){
                    if(st[j].second==st[i].first){
                        swap(st[j].first,st[i].first);
                        dfs(stp+1);
                        swap(st[j].first,st[i].first);
                    }
                }else if(st[i].second!=0&&st[j].second==st[i].second){
                    swap(st[j].first,st[i].second);
                    dfs(stp+1);
                    swap(st[j].first,st[i].second);
                }
            }
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        st.push_back(pir(a[i],b[i]));
    }
    st.push_back(pir(0,0));
    dfs(0);
    cout<<(ans==1e9?-1:ans);
    return 0;
}