#include<iostream>
using namespace std;
const int MI=3e4+15,MT=5e5+15;
int dep[MI],pre[MI],sz[MI];
int t;
void initpre(){
    for(int i=1;i<MI;i++){
        pre[i]=i;
        dep[i]=0;
        sz[i]=1;
    }
}
int root(int x){
    if(pre[x]==x) return x;
    int tmp=pre[x];
    pre[x]=root(pre[x]);
    dep[x]+=dep[tmp];
    sz[x]=sz[pre[x]];
    return pre[x];
}
void merge(int x,int y){
    int rx=root(x),ry=root(y);
    pre[ry]=rx;
    dep[ry]+=sz[rx];
    sz[ry]+=sz[rx];
    sz[rx]=sz[ry];
}
bool issame(int i,int j){
    int ri=root(i),rj=root(j);
    return ri==rj;
}
int main(){
    initpre();
    cin>>t;
    while (t--)
    {
        char op;
        int i,j;
        cin>>op>>i>>j;
        if(op=='M'){
            merge(i,j);
        }else{
            if(!issame(i,j)){
                cout<<-1<<endl;
            }else{
                cout<<abs(dep[i]-dep[j])-1<<endl;
            }
        }
    }
    
    return 0;
}