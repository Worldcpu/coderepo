#include<bits/stdc++.h>
using namespace std;
const int MN=256,MK=3e4+256;
struct previous{
    int i,j;
};
vector<previous> pre[MN][MK];
int n,a[MN],m,f[MN][MK],c[MN],cnt=0;

int dopy(int x){
    return x+10000;
}

void getans(int w){
    for(int i=n;i>=2;i--){
        c[i]=f[i][dopy(w)];
        if(c[i]==1) w-=a[i];
        else w+=a[i];
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    f[1][dopy(a[1])]=1;
    f[2][dopy(a[1]-a[2])]=-1;
    for(int i=3;i<=n;i++){
        for(int j=-10000;j<=10000;j++){
            if(f[i-1][dopy(j)]!=0){
                f[i][dopy(j+a[i])]=1;
                pre[i][dopy(j+a[i])].push_back({i-1,j});
                f[i][dopy(j-a[i])]=-1;
                pre[i][dopy(j-a[i])].push_back({i-1,j});
            }
        }
    }
    getans(m);
    // for(int i=1;i<=n;i++){
    //     cout<<c[i]<<" ";
    // }
    // cout<<'\n';
    for(int i=2;i<=n;i++){
        if(c[i]==1){
            cout<<i-cnt-1<<"\n";
            cnt++;
        }
    }
    for(int i=2;i<=n;i++){
        if(c[i]==-1){
            cout<<1<<"\n";
        }
    }
    return 0;
}