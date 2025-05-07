#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e4+15;
int n,m,pre[MN],l[MN],r[MN],a[MN],tot;
string s[MN];

void init(){
    for(int i=1;i<MN;i++) pre[i]=i;
}

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

int main(){
    init();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int st,ed;
        cin>>l[i]>>r[i]>>s[i];
        l[i]++;
        r[i]++;
        a[++tot]=l[i];
        a[++tot]=r[i];
    }
    sort(a+1,a+1+tot);
    tot=unique(a+1,a+1+tot)-a-1;
    for(int i=1;i<=m;i++){
        int x=lower_bound(a+1,a+1+tot,l[i]-1)-a;
        int y=lower_bound(a+1,a+1+tot,r[i])-a;
        // cout<<x<<" "<<y<<'\n';
        int xo=root(x),xe=root(x+tot),yo=root(y),ye=root(y+tot);
        if(s[i][0]!='o'){
            if(xo==ye){
                cout<<i-1;
                return 0;
            }
            pre[xo]=yo;
            pre[xe]=ye;
        }else{
            if(xo==yo){
                cout<<i-1;
                return 0;
            }
            pre[xo]=ye;
            pre[xe]=yo;
        }
    }
    cout<<m;
    return 0;
}