#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr int MN=3e5+15;
int n,a[MN],nxt[MN],pre[MN],ans[MN];
ull b[MN];
priority_queue<int,vector<int>,greater<int>> pq[MN];
vector<int> v;
mt19937_64 mt(time(0));

struct BITXor{
    ull t[MN];

    int lowbit(int x){
        return x&-x;
    }

    ull query(int x){
        ull ret=0;
        while(x){
            ret^=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    ull query(int l,int r){
        return query(r)^query(l-1);
    }

    void modify(int x,ull k){
        while(x<MN){
            t[x]^=k;
            x+=lowbit(x);
        }
    }

}bit;

bool check(int l,int r){
    int op=(r-l+1)&1;
    auto ret=bit.query(l,r);
    if(op){
        return ret==b[v[l]];
    }else return ret==0;
}

int main(){
    srand(time(0));
    cin>>n;
    v.push_back(0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pq[a[i]].push(i);
        v.push_back(a[i]);
        b[a[i]]=mt();
    }
    for(int i=1;i<=n;i++){
        bit.modify(i,b[a[i]]);
    }
    for(int i=2;i<n;i++){
        if(v[i]==v[i-1]){
            int l=0,r=n-i+2;
            while(l+1<r){
                int mid=(l+r)>>1;
                if(check(i,i+mid)) l=mid;
                else r=mid;
            }
            int x=v[i],y=v[i+l+1];
            cerr<<i<<' '<<i+l+1<<' '<<l<<'\n';
            if(i+l+1>n){
                for(int j=i;j<=i+l;j++){
                    cerr<<v[j]<<' ';
                }
                cout<<-1;
                return 0;
            }
            bit.modify(i,b[y]);
            bit.modify(i+l+1,b[x]);
            swap(v[i],v[i+l+1]);
        }else continue;
    }
    if(v[n]==v[n-1]){
        int val=v[n];
        bool flag=0;
        for(int j=n-3;j>=0;j--){
            if(v[j]!=v[n-1]&&v[j+1]!=v[n-1]){
                v.pop_back();
                flag=1;
                v.insert(v.begin()+j+1,val);
                break;
            }
        }
        if(!flag){
            cout<<-1;
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<pq[v[i]].top()<<' ';
        pq[v[i]].pop();
    }


    return 0;
}