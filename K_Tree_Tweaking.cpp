#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MK=520,INF=0x3f3f3f3f3f3f3f3f;
int ch[MN][2],siz[MN],a[MN],b[MN],f[MK][MK],st[MN],sum[MN],top,n,L,R,ans;

void dfs(int u){
    if(!u||b[u]>R){
        st[++top]=siz[u];
        return;
    }
    dfs(ch[u][0]);
    dfs(ch[u][1]);
}

void dfs2(int u){
    if(!u) return;
    dfs2(ch[u][0]);
    cerr<<u<<' ';
    dfs2(ch[u][1]);
}

int solve(int x){
    top=0;
    dfs(x);
    for(int i=1;i<=top;i++) sum[i]=sum[i-1]+st[i];
    for(int i=top;i>=1;i--){
        for(int j=i+1;j<=top;j++){
            f[i][j]=INF;
            for(int k=i;k<j;k++){
                f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
            }
            f[i][j]+=j-i+sum[j]-sum[i-1];
        }
    }
    return f[1][top];
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[a[i]]=i;
    }
    cin>>L>>R;
    for(int i=1;i<=n;i++){
        while(top&&b[st[top]]>b[i]){
            ch[i][0]=st[top--];
        }
        if(top) ch[st[top]][1]=i;
        st[++top]=i;
    }
    for(int i=n;i>=1;i--){
        siz[a[i]]=siz[ch[a[i]][0]]+siz[ch[a[i]][1]]+1;
    }
    if(L==1){
        ans=solve(a[1]);
    }
    for(int i=1;i<=n;i++){
        if(b[i]<L||R<b[i]){
            ans+=siz[i];
            if(L<=b[ch[i][0]]&&b[ch[i][0]]<=R) ans+=solve(ch[i][0]);
            if(L<=b[ch[i][1]]&&b[ch[i][1]]<=R) ans+=solve(ch[i][1]);
        }
    }
    cout<<ans;
    return 0;
}