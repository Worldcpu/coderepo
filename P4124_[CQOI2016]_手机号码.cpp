#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=15;
int a[MN],tot,f[MN][11][11][2][2][2];

int dfs(int pos,int lim,int lst2,int lst1,bool issame,bool head4,bool head8){
    if(!pos) return issame&&!(head4&&head8)?1:0;
    if(!lim&&(~f[pos][lst2][lst1][issame][head4][head8])) return f[pos][lst2][lst1][issame][head4][head8];
    int ret=0,up,down=pos==tot?1:0;
    if(lim) up=a[pos];
    else up=9;
    for(int i=down;i<=up;i++){
        bool tmp=issame||(lst2==i&&lst1==i);
        if(i==4&&!head8){
            ret+=dfs(pos-1,lim&&i==up,lst1,i,tmp,1,0);
        }else if(i==8&&!head4){
            ret+=dfs(pos-1,lim&&i==up,lst1,i,tmp,0,1);
        }else if(i!=4&&i!=8){
            ret+=dfs(pos-1,lim&&i==up,lst1,i,tmp,head4,head8);
        }
    }
    if(!lim) f[pos][lst2][lst1][issame][head4][head8]=ret;
    return ret;
}

int solve(int x){
    if(x<1e10) return 0;
    tot=0;
    while(x>0){
        a[++tot]=x%10;
        x/=10;
    }
    return dfs(tot,1,10,10,0,0,0);
}

signed main(){
    memset(f,-1,sizeof(f));
    int l,r;
    cin>>l>>r;
    cout<<solve(r)-solve(l-1);
    return 0;
}
