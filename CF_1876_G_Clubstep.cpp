#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],q,ans[MN],pre[MN],sum[MN],x[MN];
priority_queue<pir> pq;
vector<pir> qry[MN],chg[MN];

int root(int x){
    if(pre[x]==x) return pre[x];
    if(pre[pre[x]]==pre[x]) return pre[x];
    int fa=root(pre[x]);
    sum[x]+=sum[pre[x]];
    pre[x]=fa;
    return pre[x];
}

void initpre(){
    for(int i=0;i<MN;i++){
        pre[i]=i;
        sum[i]=0;
    }
}

signed main(){
    initpre();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r>>x[i];
        qry[l].push_back(pir(r,i));
        chg[r].push_back(pir(114514,i));
    }
    for(int i=n;i>=1;i--){
        vector<pir> tmp;
        for(auto p:chg[i]){
            pq.push(pir(x[p.second],p.second));           
        }
        while(!pq.empty()&&pq.top().first>=a[i]){
            tmp.push_back(pq.top());
            pq.pop();
        }
        for(int j=tmp.size()-1,lst=-1,lstn;j>=0;j--){
            auto p=tmp[j];
            int x=p.first,d=(x-a[i]+1)/2;
            x-=d;
            sum[p.second]+=d*i;
            if(lst!=-1&&lstn==x){
                pre[p.second]=lst;
                sum[p.second]-=sum[lst];
            }else pq.push(pir(x,p.second)),lst=p.second,lstn=x;
        }
        for(auto p:qry[i]){
            root(p.second);
            ans[p.second]=sum[p.second];
            if(pre[p.second]!=p.second){
                ans[p.second]+=sum[pre[p.second]];
            }
        }
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }


    return 0;
}