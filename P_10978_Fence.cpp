#include<bits/stdc++.h>
using namespace std;
const int MN=16005;
struct node{
    int l,p,s;
}a[MN];
int n,m;
int f[MN][MN],q[MN];
bool cmp(node x,node y){
    return x.s<y.s;
}

int calc(int i,int k){
    return f[i-1][k]-a[i].p*k;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i].l>>a[i].p>>a[i].s;
    }
    sort(a+1,a+1+m,cmp);//先排序
    for(int i=1;i<=m;i++){
        int l=1,r=0;
        for(int k=max(0,a[i].s-a[i].l);k<=a[i].s-1;k++){
            // 加决策并维护里面的单点递减
            while(l<=r&&calc(i,q[r])<=calc(i,k)) r--;
            q[++r]=k;
        }
        for(int j=1;j<=n;j++){
            f[i][j]=max(f[i-1][j],f[i][j-1]);//罚坐与不涂
            if(j>=a[i].s){//如果当前j可以进行第三个转移方程
                while(l<=r&&q[l]<j-a[i].l){//排除过时决策
                    l++;
                }
                if(l<=r){//如果队不为空，转移
                    f[i][j]=max(f[i][j],calc(i,q[l])+a[i].p*j);
                }
            }
        }
    }
    cout<<f[m][n];
    return 0;
}