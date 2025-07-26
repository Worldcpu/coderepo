#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,m,mn,cnt[MN],a[MN],b[MN],ans,lst;
priority_queue<pir> aq,bq;

int getf(pir x){
    if(cnt[x.second]+1==4) return 0;
    return (cnt[x.second]&1?a[x.second]:b[x.second]);
}

void pusha(pir x){
    if(x.first==0) return;
    aq.push(x);
}

void pushb(pir x){
    if(x.first==0) return;
    bq.push(x);
}

signed main(){
    freopen("coin.in","r",stdin);
    freopen("coin.out","w",stdout);
    cin>>n>>m;
    mn=3*n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        aq.push(pir(a[i],i));
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=min(mn,m);i++){
        auto ma=aq.top();
        pir mb;
        if(bq.empty()){
            mb={0,0};
        }else mb=bq.top();
        if(ma.first>mb.first){
            lst+=ma.first;
            ans^=lst;
            aq.pop();
            pushb(pir(getf(ma),ma.second));
        }else if(ma.first<mb.first){
            lst+=mb.first;
            ans^=lst;
            bq.pop();
            pusha(pir(getf(mb),mb.second));
        }else{
            int fa=getf(ma),fb=getf(mb);
            if(fa==fb){
            lst+=mb.first;
            ans^=lst;
            bq.pop();
            pusha(pir(getf(mb),mb.second));
            }else if(fa>fb){
            lst+=ma.first;
            ans^=lst;
            aq.pop();
            pushb(pir(getf(ma),ma.second));
            }else{
            lst+=mb.first;
            ans^=lst;
            bq.pop();
            pusha(pir(getf(mb),mb.second));
            }
        }
    }
    for(int i=min(mn,m)+1;i<=m;i++) ans^=lst;
    cout<<ans;
    return 0;
}