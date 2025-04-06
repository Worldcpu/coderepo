#include<bits/stdc++.h>
#include<bits/extc++.h>
// #define int long long
#define ll long long
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
namespace pbds=__gnu_pbds;
const int MN=2010,MK=30;
const int INF=0x7fffffff;
int n,m,a[MN],cost[MN][MN],f[MN][MK];
pbds::priority_queue<int,less<int>,thin_heap_tag> y;
pbds::priority_queue<int,greater<int>,thin_heap_tag> x;

// int getz(int x){
//     return x<0?-x:x;
// }

void getmid2(){

        for(int i=1;i<=n;i++)
        {
            pbds::priority_queue<int,less<int>,thin_heap_tag> q1;
            pbds::priority_queue<int,greater<int>,thin_heap_tag> q2;
            q1.push(-INF),q2.push(INF);
            int sum1=0,sum2=0;
            for(int j=i;j<=n;j++)
            {
                if(q1.empty()||a[j]<=q1.top()) q1.push(a[j]),sum1+=a[j];
                else q2.push(a[j]),sum2+=a[j];
                if(q1.size()>q2.size()+1)
                {
                    int x=q1.top();
                    q2.push(x);
                    q1.pop();
                    sum1-=x,sum2+=x;
                }
                else if(q1.size()<q2.size()) 
                {
                    int x=q2.top();
                    q1.push(x);
                    q2.pop();
                    sum2-=x,sum1+=x;
                }
                int x=q1.top();
                cost[i][j]=q1.size()*x-sum1+sum2-q2.size()*x;
            }
        }
    }

// void getmid(int l,int r){
//     x.clear();
//     y.clear();
//     // while (!x.empty())
//     // {
//     //     x.pop();
//     // }
//     // while (!y.empty())
//     // {
//     //     y.pop();
//     // }
    
//     int sum1=0,sum2=0;
//     if(l==r) return void(cost[l][r]=0);
//     for(int i=l;i<=r;i++){
//         if(i==l){ 
//             x.push(a[i]);
//             sum1+=a[i];
//         }
//         if(i>l&&((i-l+1)&1)==0){
//             int c=x.top();
//             if(a[i]<=c){ 
//                 sum2+=a[i];
//                 y.push(a[i]);
//             }
//             else{
//                 sum1-=c;
//                 sum1+=a[i];
//                 sum2+=c;
//                 x.pop();
//                 x.push(a[i]);
//                 y.push(c);
//             }
//         }else if(i>l&&((i-l+1)&1)){
//             int c=y.top();
//             if(a[i]>=c){ 
//                 x.push(a[i]);
//                 sum1+=a[i];
//             }
//             else{
//                 sum2-=c;
//                 sum2+=a[i];
//                 sum1+=c;
//                 y.pop();
//                 y.push(a[i]);
//                 x.push(c);
//             }
//         }
//     }
//     int md=x.top();
//     cost[l][r]=getz(sum1-md*x.size())+getz((sum2-md*y.size()));
//     // if((r&1)==0){
//     //     return ((x.top()+y.top())>>1);
//     // }else return x.top();
// }

void solve(){

}

signed main(){
    // ios::sync_with_stdio(0);
    while (scanf("%d%d",&n,&m)!=EOF&&(n||m))
    {
        
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        // for(int i=1;i<=n;i++){
        //     for(int j=i;j<=n;j++){
        //         getmid(i,j);
        //         // cost[i][j]=sum[j]-sum[i-1]-md*(j-i+1);
        //         // cout<<"L:"<<i<<" R:"<<j<<" "<<cost[i][j]<<'\n';
        //     }
        // }
        getmid2();
        memset(f,0x3f,sizeof(f));
        f[0][0]=0;
        for(int i=1;i<=n;i++)
            for(int k=1;k<=m;k++)
                for(int j=0;j<i;j++)
                    f[i][k]=min(f[i][k],f[j][k-1]+cost[j+1][i]);
        printf("%d\n",f[n][m]);
    }
    
    return 0;
}