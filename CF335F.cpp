#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],tmp[MN],ttot,ans,sum,num[MN],cnt[MN],dtot;
priority_queue<int,vector<int>,greater<int>> q;

bool cmp(int x,int y){
    return x>y;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        ans+=a[i];
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        if(i==1||a[i]!=a[i-1]){
            num[++dtot]=a[i];
            cnt[dtot]++;
        }else cnt[dtot]++;
    }
    for(int i=1;i<=dtot;i++){
        int ok=min(sum-(int)q.size()*2,cnt[i]),rst=min(cnt[i]-ok,sum-ok);
        ttot=0;
        for(int j=1;j<=ok;j++){
            tmp[++ttot]=num[i];
        }
        for(int j=1;j<=rst;j+=2){
            int k=q.top();
            q.pop();
            if(k<num[i]){
                tmp[++ttot]=num[i];
                if(j<rst){
                    tmp[++ttot]=num[i];
                }
            }else{
                tmp[++ttot]=k;
                if(j<rst){
                    tmp[++ttot]=2*num[i]-k;
                }
            }
        }
        for(int j=1;j<=ttot;j++){
            if(tmp[j]>=0){
                q.push(tmp[j]);
            }
        }
        sum+=cnt[i];
    }
    while(!q.empty()){
        ans-=q.top();
        q.pop();
    }
    cout<<ans;
    return 0;
}