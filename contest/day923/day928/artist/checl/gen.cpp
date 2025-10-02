#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}


int main(){
    srand(time(0));
    int n=getrd(8,12),m=getrd(5,7);
    cout<<n<<' '<<m<<'\n';
    for(int i=1;i<=m;i++){
        map<int,bool> vis;
        int num=getrd(2,4);
        cout<<num<<' ';
        for(int j=1;j<=num;j++){
            int x=getrd(1,n);
            while(vis[x]){
                x=getrd(1,n);
            }
            vis[x]=1;
            cout<<x<<' ';
        }
        cout<<'\n';
    }
    return 0;
}