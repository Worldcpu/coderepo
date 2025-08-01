#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int qwq,n,q;
vector<int> nxt[MN];


int main(){
    cin>>qwq>>n>>q>>qwq;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        nxt[x].push_back(i);
    }
    while(q--){
        int len,flag=1;
        cin>>len;
        for(int i=1,pos=0;i<=len;i++){
            int x;
            cin>>x;
            if(!flag) continue;
            auto ret=lower_bound(nxt[x].begin(),nxt[x].end(),pos+1);
            if(ret==nxt[x].end()) flag=0;
            else pos=*ret;
        }
        cout<<(flag?"Yes\n":"No\n");
    }
    return 0;
}