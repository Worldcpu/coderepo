#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,ans,num[MN][3];

bool check(int x,int y,int z){
    bool flag=0;
    for(int i=0;i<3;i++){
        if(num[x][i]>max(num[y][i],num[z][i])){
            flag=1;
            break;
        }
    }
    if(!flag) return 0;
    flag=0;
    swap(x,y);
    for(int i=0;i<3;i++){
        if(num[x][i]>max(num[y][i],num[z][i])){
            flag=1;
            break;
        }
    }
    if(!flag) return 0;
    flag=0;
    swap(x,z);
    for(int i=0;i<3;i++){
        if(num[x][i]>max(num[y][i],num[z][i])){
            flag=1;
            break;
        }
    }
    if(!flag) return 0;
    return 1;
}

int main(){
    freopen("team.in","r",stdin);
    freopen("team.ans","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>num[i][0]>>num[i][1]>>num[i][2];
    }
    ans=-1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            for(int k=1;k<=n;k++){
                if(i==k||j==k) continue;
                if(check(i,j,k)){
                    ans=max(ans,max({num[i][0],num[j][0],num[k][0]})+max({num[i][1],num[j][1],num[k][1]})+max({num[i][2],num[j][2],num[k][2]}));


                }
            }
        }
    }
    cout<<ans;
    return 0;
}