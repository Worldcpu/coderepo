#include<bits/stdc++.h>
using namespace std;
constexpr int MN=80,MM=2520;
int m,n=1,a[MN],ret[MM],tmp[MM],ans[MN][MN];
bool f[MN][MN][MM];

bool cmp(int x,int y){
    return ret[x]<ret[y];
}

void dfs(int x,int y,int z){
    if(!x) return;
    ret[x]=a[y];
    z-=a[y];
    x--;
    if(f[x][y][z]) dfs(x,y,z);
    else dfs(x,y-1,z);
}

void getans(){
    for(int i=1;i<=n;i++) tmp[i]=i;
    for(int i=1;i<=n;i++){
        sort(tmp+i,tmp+n+1,cmp);
        for(int j=i+1;j<=i+ret[tmp[i]];j++){
            ans[tmp[i]][tmp[j]]=1;
        }
        for(int j=i+ret[tmp[i]]+1;j<=n;j++){
            ans[tmp[j]][tmp[i]]=1;
            ret[tmp[j]]--;
        }
    }
}

int main(){
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+m);
    f[1][1][a[1]]=1;
    while(n<62&&(n<m||!f[n][m][n*(n-1)/2])){
        n++;
        for(int i=1;i<=m;i++){
            for(int j=(n-1)*(n-2)/2;j<=(n-1)*a[m];j++){
                if(f[n-1][i][j]){
                    f[n][i][j+a[i]]=1;
                    if(i+1<=m) f[n][i+1][j+a[i+1]]=1;
                }
            }
        }
    }
    if(n>61){
        cout<<"=(";
        return 0;
    }
    dfs(n,m,n*(n-1)/2);
    getans();
    cout<<n<<'\n';
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<ans[i][j];
        }
        cout<<'\n';
    }
    return 0;
}
