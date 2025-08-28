#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
struct Node{
    int cnt,pos,val;

    bool operator<(const Node &x)const{
        if(cnt==x.cnt) return pos<x.pos;
        return cnt>x.cnt;
    }
};
int a[MN],nxt[MN],lst[MN],cnt[MN],cur[MN],n;
set<Node> s1;
set<pir> s2;

int main(){
    freopen("food.in","r",stdin);
    freopen("food.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cnt[a[i]]++;
        if(lst[a[i]]) nxt[lst[a[i]]]=i;
        else cur[a[i]]=i;
        lst[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        if(cnt[i]) s1.insert({cnt[i],cur[i],i});
    }
    for(int i=1;i<=n;i++){
        if(cur[i]) s2.insert(pir(cur[i],i));
    }
    if((*s1.begin()).cnt>(n+1)/2){
        cout<<-1;
        return 0;
    }
    for(int i=1,lst=0;i<=n;i++){
        auto it=*s1.begin();
        if(it.cnt>(n-i+1)/2){
            cout<<it.pos<<' ';
            lst=it.val;
            s1.erase(s1.begin());
            s2.erase(pir(cur[lst],lst));
            cnt[lst]--;
            if(cnt[lst]>0){
                cur[lst]=nxt[cur[lst]];
                s1.insert((Node){cnt[lst],cur[lst],lst});
                s2.insert(pir(cur[lst],lst));
            }
        }else{
            auto itt=s2.begin();
            if((*itt).second!=lst){
                cout<<cur[(*itt).second]<<' ';
                lst=(*itt).second;
                s1.erase((Node){cnt[lst],cur[lst],lst});
                s2.erase(pir(cur[lst],lst));
                cnt[lst]--;
                if(cnt[lst]>0){
                    cur[lst]=nxt[cur[lst]];
                    s1.insert((Node){cnt[lst],cur[lst],lst});
                    s2.insert(pir(cur[lst],lst));
                }
            }else{
                ++itt;
                cout<<cur[(*itt).second]<<' ';
                lst=(*itt).second;
                s1.erase((Node){cnt[lst],cur[lst],lst});
                s2.erase(pir(cur[lst],lst));
                cnt[lst]--;
                if(cnt[lst]>0){
                    cur[lst]=nxt[cur[lst]];
                    s1.insert((Node){cnt[lst],cur[lst],lst});
                    s2.insert(pir(cur[lst],lst));
                }
            }
        }
    }
    return 0;
}