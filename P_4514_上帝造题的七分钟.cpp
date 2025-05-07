#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2520;
int n,m;

struct TBIT{
    int t1[MN][MN],t2[MN][MN],t3[MN][MN],t4[MN][MN];

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int y,int k){
        int k2=x*k,k3=y*k,k4=y*k*x;
        for(int i=x;i<=n;i+=lowbit(i)){
            for(int j=y;j<=m;j+=lowbit(j)){
                t1[i][j]+=k;
                t2[i][j]+=k2;
                t3[i][j]+=k3;
                t4[i][j]+=k4;
            }
        }
    }

    int query(int x,int y){
        int s1=0,s2=0,s3=0,s4=0;
        for(int i=x;i;i-=lowbit(i)){
            for(int j=y;j;j-=lowbit(j)){
                s1+=t1[i][j];
                s2+=t2[i][j];
                s3+=t3[i][j];
                s4+=t4[i][j];
            }
        }
        return (x+1)*(y+1)*s1-(y+1)*s2-(x+1)*s3+s4;
    }

}tb;

int main(){
    char luogu;
    cin>>luogu>>n>>m;
    char op;
    int a,b,c,d,delta;
    while(cin>>op){
        if(op=='L'){
            cin>>a>>b>>c>>d>>delta;
            tb.update(a,b,delta);
            tb.update(c+1,b,-delta);
            tb.update(a,d+1,-delta);
            tb.update(c+1,d+1,delta);
        }else{
            cin>>a>>b>>c>>d;
            cout<<tb.query(c,d)-tb.query(a-1,d)-tb.query(c,b-1)+tb.query(a-1,b-1)<<'\n';
        }
    }
    return 0;
}