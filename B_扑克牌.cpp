#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int MN=55,MP=5e8+15;
int n,m,num[MN];
bool check(int k){
    int awa=0;
    for(int i=1;i<=n;i++){
        awa+=max((long long)0,k-num[i]);

    }
    // if(k>m){
    //     return 0;
    // }
    return awa<=min(m,k);
    // int cnt=0,t[MN];
    // for(int i=1;i<=n+1;i++){
    //     t[i]=num[i];
    // }
    // for(int i=1;i<=n+1;i++){
    //     // cout<<"I:"<<id[i]<<endl;
    //     int di=id[i];
    //     if(t[di]){
    //         while (t[di])
    //         {
    //             // cout<<"NOWCNT "<<cnt<<endl;
    //             // for(int i=1;i<=n+1;i++){
    //             //     cout<<t[i]<<" ";
    //             // }
    //             // cout<<endl;
    //             t[di]--;
    //             int p=0;
    //             for(int k=i+1;k<=n+1&&p!=2;k++){
    //                 int dk=id[k];
    //                 if(t[dk]){
    //                     p++;
    //                     t[dk]--;
    //                 }
    //                 if(p==2) break;
    //             }
    //             if(p==2){
    //                 cnt++;
    //             }
    //         }
    //     }
    // }
    // if(cnt>=k) return 1;
    // else return 0;
}
// bool cmp(int x,int y){
//     return num[x]>num[y];
// }
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>num[i];
    }
    int l=0,r=1e10,ret;
    // for(int i=1;i<=n+1;i++){
    //     cout<<id[i]<<" ";
    // }        id[i]=i;
    // cout<<endl;
    // cout<<check(3);
    while (l+1<r)
    {
        int mid=l+r>>1;
        if(check(mid)){
            ret=mid;
            l=mid;
        }else r=mid;
    }
    cout<<ret;
    return 0;
}
