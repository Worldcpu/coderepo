#include<iostream>
#include<cstring>
using namespace std;
const int MN=1e6+15,ML=20;
string s;
int m,fa[MN][40],dep[MN],pre[MN],n;
int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=__lg(n)+1;i>=0;i--){
        if(dep[x]-(1<<i)>=dep[y])x=fa[x][i];
    }
    if(x==y) return x;
    for(int i=__lg(n)+1;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
int main(){
    cin>>s;
    n=s.length();
    s=" "+s;
    //cout<<"N:"<<n<<endl;
    for(int i=2,j=0;i<=n;i++){
        while(j&&s[i]!=s[j+1]){
            j=pre[j];
        }
        if(s[i]==s[j+1])j++;
        pre[i]=j;
        fa[i][0]=j;
        dep[i]=dep[j]+1;
    }
    for(int i=1;i<=n;i++){
        cout<<pre[i]<<" ";
    }
    cout<<endl;
    for(int k=1;k<=__lg(MN)+1;k++){
        for(int j=1;j<=n;j++){
            fa[j][k]=fa[fa[j][k-1]][k-1];
        }
    }
    cin>>m;
    for(int i=1;i<=n;i++){
        cout<<i<<" "<<fa[i][0]<<endl;
    }
    while (m--)
    {
        int p,q;
        cin>>p>>q;
        cout<<lca(fa[p][0],fa[q][0])<<endl;
    }
    
    return 0;
}