#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int n,p[MN];
int ans[MN];

void dfs(int x,int cnt){
    if(cnt<0||cnt>n-x+1) return;
    if(x>n){
        if(cnt) return;
        for(int i=1;i<=n;i++){
            if(ans[i]==1) cout<<"(";
            else cout<<")";
        }
        exit(0);
    }
    if(ans[x]){
        dfs(x+1,cnt+(ans[x]==1?1:-1));
        return;
    }
    for(int i=1;i<=2;i++){
        int cur=x,now=i,len=0;
        do {
            ans[cur]=now;
            cur=p[cur];
            now=3-now;
            len++;
        }while (cur!=x);
        if(len==2){
            dfs(x+1,cnt+1);
            return;
        }
        dfs(x+1,cnt+(ans[x]==1?1:-1));
        do {
            ans[cur]=0;
            cur=p[cur];
        }while (cur!=x);

    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }

    dfs(1,0);
    return 0;
}
