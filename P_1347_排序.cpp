#include<bits/stdc++.h>
using namespace std;
constexpr int MN=650;
struct Node{
    int x,y,z;
}nd[MN];
bool mat[MN][MN];
int n,m,ans[MN]; 

int floyd(int p){
    memset(mat,0,sizeof(mat));
    for(int i=1;i<=p;i++){
        mat[nd[i].x][nd[i].y]=1;
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                mat[i][j]|=(mat[i][k]&mat[k][j]);
            }
        }
    }
    bool flag=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(mat[i][j]&&mat[j][i]) return 0;
            if((!mat[i][j])&&(!mat[j][i])) flag=1;
        }
    }
    for(int i=1;i<=n;i++) if(mat[i][i]) return 0;
    if(!flag) return 1;
    return 2;
}

void getrank(){
    for(int i=1;i<=n;i++){
        int cnt=0;
        for(int j=1;j<=n;j++){
            if(mat[i][j]&&i!=j) cnt++;
        }
        // cout<<cnt<<'\n';
        ans[n-cnt]=i;
    }
    for(int i=1;i<=n;i++){
        cout<<(char)(ans[i]+'A'-1);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        char a,b,c;
        cin>>a>>b>>c;
        //cout<<a-'A'+1<<" "<<c-'A'+1<<" "<<(b=='>'?1:0)<<'\n';
        nd[i]={a-'A'+1,c-'A'+1,1};
    }
    if(floyd(m)==2){
        cout<<"Sorted sequence cannot be determined.";
        return 0;
    }
    int l=0,r=m;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(floyd(mid)==2) l=mid;
        else r=mid;
    }
    if(floyd(r)==1){
        cout<<"Sorted sequence determined after "<<r<<" relations: ";
        getrank();
        cout<<".";
    }else cout<<"Inconsistency found after "<<r<<" relations.";
    return 0;
}