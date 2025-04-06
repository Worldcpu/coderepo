#include<iostream>
using namespace std;
int map[15][15];
int ci,cj,fi,fj,ff,cf;
bool iszhua(){
    if(ci==fi&&fj==cj){
        return 0;
    }
    return 1;
}
int vis[15][15][15][15];
void movecow(){
    if(cf==1){
        if(map[ci-1][cj]==1){
            ci--;
        }else cf=2;
    }
    else if(cf==2){
        if(map[ci][cj+1]==1){
            cj++;
        }else cf=3;
    }
    else if(cf==3){
        if(map[ci+1][cj]==1){
            ci++;
        }else cf=4;
    }
    else if(cf==4){
        if(map[ci][cj-1]==1){
            cj--;
        }else cf=1;
    }
}
void movefarm(){
    if(ff==1){
        if(map[fi-1][fj]==1){
            fi--;
        }else ff=2;
    }
    else if(ff==2){
        if(map[fi][fj+1]==1){
            fj++;
        }else ff=3;
    }else if(ff==3){
        if(map[fi+1][fj]==1){
            fi++;
        }else ff=4;
    }else if(ff==4){
        if(map[fi][fj-1]==1){
            fj--;
        }else ff=1;
    }
}
int main(){
    ff=cf=1;
    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            char t;
            cin>>t;
            if(t=='*'){
                map[i][j]=0;
            }else if(t=='.'){
                map[i][j]=1;
            }else if(t=='C'){
                ci=i;
                cj=j;
                map[i][j]=1;
            }else{
                fi=i;
                fj=j;
                map[i][j]=1;
            }
        }
    }
    // for(int i=1;i<=10;i++){
    //     for(int j=1;j<=10;j++){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    int ans=0;
    while (iszhua())
    {
        vis[ci][cj][fi][fj]++;
        if(vis[ci][cj][fi][fj]==4){
            cout<<0;
            return 0;
        }
        ans++;
        movecow();
        movefarm();
    }
    cout<<ans;
    return 0;
}