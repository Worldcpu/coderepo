#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15;
int n,nx,ny;
char fx;
struct node{
    int x,y,id;
};
bool cmpx(node x,node y){
    return x.x<y.x;
}
bool cmpy(node x,node y){
    return x.y<y.y;
}
bool stop[MN];
int ans[MN];
vector<node> east,north;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>fx>>nx>>ny;
        if(fx=='E'){
            east.push_back({nx,ny,i});
        }else north.push_back({nx,ny,i});
    }
    sort(north.begin(),north.end(),cmpx);
    sort(east.begin(),east.end(),cmpy);
    for(auto ed:east){
        for(auto nd:north){
            if(ed.x<nd.x&&nd.y<ed.y&&!stop[nd.id]&&!stop[ed.id]){
                int elen=nd.x-ed.x,nlen=ed.y-nd.y;
                if(elen<nlen){
                    ans[ed.id]+=ans[nd.id]+1;
                    stop[nd.id]=1;
                }
                if(nlen<elen){
                    ans[nd.id]+=ans[ed.id]+1;
                    stop[ed.id]=1;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}