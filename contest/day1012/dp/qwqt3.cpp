#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=1e9+7;
int n,m,cnt[MN];
vector<vector<int>> f[MN]; // I don't like this 

void dodp(){
    f[1][0][cnt[1]]=1;
    for(int i=1;i<=m;i++){
        int limj=(i>1?cnt[i-1]:0),limk=cnt[i];
        for(int j=0;j<=limj;j++){
            for(int k=limk;k>=0;k--){
                if(k>0) f[i][j][k-1]=(f[i][j][k-1]+f[i][j][k])%MOD;
                if(i<m&&cnt[i+1]>=j&&k>=j) f[i+1][k-j][cnt[i+1]-j]=(f[i+1][k-j][cnt[i+1]-j]+f[i][j][k])%MOD;
            }
        }
    }
}

signed main(){
    random_device rd;
    cerr<<rd.entropy();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        cnt[x]++;
    }    
    for(int i=1;i<=m-1;i++){
        int p=cnt[i]%3;
        if(cnt[i]<0){
            cout<<0;
            return 0;
        }
        for(int j=i;j<=min(m,i+2);j++){
            cnt[j]-=p;
        }
    } 
    if(cnt[m]%3!=0){
        cout<<0;
        return 0;
    }
    if(m>1&&cnt[m-1]%3){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=m;i++){
        cnt[i]/=3;
        if(i>0){
            f[i].resize(cnt[i-1]+1);
            for(int j=0;j<=cnt[i-1];j++) f[i][j].resize(cnt[i]+1);
        }else f[i].resize(1),f[i][0].resize(cnt[i]+1);
    }
    dodp();
    cout<<f[m][0][0];
    return 0;
}

// 我在tm干什么？