#include<iostream>
using namespace std;
const int MN=5e4+15;
int n,k;
int pre[3*MN];
void initpre(){
    for(int i=1;i<=3*n;i++){
        pre[i]=i;
    }
}
int root(int x){
    if(pre[x]==x){
        return x;
    }else return pre[x]=root(pre[x]);
}
void merge(int x,int y){
    int rx=root(x),ry=root(y);
    pre[ry]=rx;
}
int main(){
    int ans=0;
    cin>>n>>k;
    initpre();
    while (k--)
    {
        int op,x,y;
        cin>>op>>x>>y;
        if(x>n||y>n){
            ans++;
        }else if(op==2&&x==y){
            ans++;
        }else{
            int fx=x+n,fy=y+n,ex=x+n*2,ey=y+n*2;
            if(op==1){
                if(root(fx)!=root(y)&&root(ex)!=root(y)){
                    merge(x,y);
                    merge(fx,fy);
                    merge(ex,ey);
                }else ans++;
            }
            if(op==2){
                if(root(x)!=root(y)&&root(y)!=root(ex)){
                    merge(x,ey);
                    merge(y,fx);
                    merge(ex,fy);
                }else ans++;
            }
        }
    }
    cout<<ans;
    return 0;
}