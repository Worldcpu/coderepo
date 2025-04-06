#include<bits/stdc++.h>
using namespace std;
const int MN=1e7+15;
struct node{
    int son[2],fa;
    int num;
    int isend;
}t[MN];
int cnt=0,n,m;
void insert(vector<int> vt){
    int now=0;
    for(int i=0;i<vt.size();i++){
        if(!t[now].son[vt[i]]){
            t[now].son[vt[i]]=++cnt;
        }
        now=t[now].son[vt[i]];
        t[now].num++;
    }
    t[now].isend++;
}

int query(vector<int> vt){
    int now=0,ans=0,cnt=0;
    for(int i=0;i<vt.size();i++){
        if(!t[now].son[vt[i]])return ans;
        now=t[now].son[vt[i]];
        ans+=t[now].isend;
    }
    return ans+t[now].num-t[now].isend;
    // now=t[now].fa;
    // while(now){
    //     if(t[now].isend){
    //         ans+=t[now].num;
    //         if(t[now].son[0]) ans-=t[t[now].son[0]].num;
    //         if(t[now].son[1]) ans-=t[t[now].son[1]].num;
    //     }
    //     now=t[now].fa;
    // }
}

int main(){
    cin>>n>>m;
    int tot,tmp;
    for(int i=1;i<=n;i++){
        vector<int> vt;
        cin>>tot;
        for(int j=1;j<=tot;j++){
            cin>>tmp;
            vt.push_back(tmp);
        }
        insert(vt);
    }
    while (m--)
    {
        vector<int> vt;
        cin>>tot;
        for(int i=1;i<=tot;i++){
            cin>>tmp;
            vt.push_back(tmp);
        }
        cout<<query(vt)<<'\n';
    }
    
}