#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e5+15;

struct ACAuto{
    int siz[MN],rt[MN],cnt,tot,fail[MN],t1[MN][26],t2[MN][26],end[MN],val[MN];

    void insert(string s,int rt){
        int p=rt;
        for(auto c:s){
            int k=c-'a';
            if(!t1[p][k]) t1[p][k]=++tot;
            p=t1[p][k];
        }
        end[p]++;
    }
    void build(int rt){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(t1[rt][i]){
                fail[t1[rt][i]]=rt;
                q.push(t1[rt][i]);
                val[t1[rt][i]]=end[t1[rt][i]];
                t2[rt][i]=t1[rt][i];
            } else {
                t2[rt][i]=rt;
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                if(t1[u][i]){
                    t2[u][i]=t1[u][i];
                    fail[t1[u][i]]=t2[fail[u]][i];
                    val[t1[u][i]]=val[fail[t1[u][i]]]+end[t1[u][i]];
                    q.push(t1[u][i]);
                } else {
                    t2[u][i]=t2[fail[u]][i];
                }
            }
        }
    }

    int merge(int x,int y){
        if(!x||!y) return x+y;
        end[x]+=end[y];
        for(int i=0;i<26;i++){
            t1[x][i]=merge(t1[x][i],t1[y][i]);
        }
        return x;
    }

    int query(string s,int rt){
        int p=rt,ret=0;
        for(auto c:s){
            int k=c-'a';
            p=t2[p][k];
            ret+=val[p];
        }
        return ret;
    }

    void insert(string s){
        siz[++cnt]=1;
        rt[cnt]=++tot;
        insert(s,rt[cnt]);
        while(siz[cnt]==siz[cnt-1]){
            rt[cnt-1]=merge(rt[cnt-1],rt[cnt]);
            siz[cnt-1]<<=1;
            siz[cnt]=0;
            cnt--;
        }
        build(rt[cnt]);
    }

    int query(string s){
        int ret=0;
        for(int i=1;i<=cnt;i++){
            ret+=query(s,rt[i]);
        }
        return ret;
    }

}t1,t2;

int main(){
    int T;
    cin>>T;
    while(T--){
        int op;
        string s;
        cin>>op>>s;
        if(op==1){
            t1.insert(s);
        }else if(op==2){
            t2.insert(s);
        }else{
            cout<<t1.query(s)-t2.query(s)<<'\n';
            fflush(stdout);
        }
    }

    return 0;
}
