#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2520+15;
struct Node{
    int posa,posb,len;
};
int lena,lenb;
bool vis[MN][MN];
string A,B;

struct SAM{// 1-based
    int nxt[MN][26],len[MN],fa[MN],tot,lst;

    SAM(){
        initsam();
    }

    void initsam(){
        for(int i=0;i<=tot;i++){
            fa[i]=len[i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        tot=lst=1;
    }

    inline void extend(int c){
        int cur=++tot;
        len[cur]=len[lst]+1;
        int p=lst;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int nq=++tot;
                len[nq]=len[p]+1,fa[nq]=fa[q];
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[q]=fa[cur]=nq;
                while(nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        lst=cur;
    }
}sam[2];

struct Seq{
    vector<int> nxt[MN];

    void expand(int c,int pos){
        nxt[c].push_back(pos);
    }

    int gnxt(int i,int c){
        auto ret=lower_bound(nxt[c].begin(),nxt[c].end(),i+1);
        if(ret==nxt[c].end()) return 0;
        return *ret;
    }

}sq[2];

int bfs1(){
    memset(vis,0,sizeof(vis));
    queue<Node> q;
    q.push((Node){1,1,0});
    while(!q.empty()){
        auto f=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(sam[0].nxt[f.posa][i]){
                if(sam[1].nxt[f.posb][i]){
                    int u=sam[0].nxt[f.posa][i],v=sam[1].nxt[f.posb][i];
                    if(!vis[u][v]){
                        vis[u][v]=1;
                        q.push((Node){u,v,f.len+1});
                    }
                }else return f.len+1;
            }
        }
    }
    return -1;
}

int bfs2(){
    memset(vis,0,sizeof(vis));
    queue<Node> q;
    q.push((Node){1,0,0});
    while(!q.empty()){
        auto f=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(sam[0].nxt[f.posa][i]){
                if(sq[1].gnxt(f.posb,i)){
                    int u=sam[0].nxt[f.posa][i],v=sq[1].gnxt(f.posb,i);
                    if(!vis[u][v]){
                        vis[u][v]=1;
                        q.push((Node){u,v,f.len+1});
                    }
                }else return f.len+1;
            }
        }
    }
    return -1;
}


int bfs3(){
    memset(vis,0,sizeof(vis));
    queue<Node> q;
    q.push((Node){0,1,0});
    while(!q.empty()){
        auto f=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(sq[0].gnxt(f.posa,i)){
                if(sam[1].nxt[f.posb][i]){
                    int u=sq[0].gnxt(f.posa,i),v=sam[1].nxt[f.posb][i];
                    if(!vis[u][v]){
                        vis[u][v]=1;
                        q.push((Node){u,v,f.len+1});
                    }
                }else return f.len+1;
            }
        }
    }
    return -1;
}


int bfs4(){
    memset(vis,0,sizeof(vis));
    queue<Node> q;
    q.push((Node){0,0,0});
    while(!q.empty()){
        auto f=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(sq[0].gnxt(f.posa,i)){
                if(sq[1].gnxt(f.posb,i)){
                    int u=sq[0].gnxt(f.posa,i),v=sq[1].gnxt(f.posb,i);
                    if(!vis[u][v]){
                        vis[u][v]=1;
                        q.push((Node){u,v,f.len+1});
                    }
                }else return f.len+1;
            }
        }
    }
    return -1;
}

int main(){
    cin>>A>>B;
    lena=A.length(),lenb=B.length();
    A=" "+A;
    B=" "+B;
    for(int i=1;i<=lena;i++){
        int k=A[i]-'a';
        sam[0].extend(k);
        sq[0].expand(k,i);
    }
    for(int i=1;i<=lenb;i++){
        int k=B[i]-'a';
        sam[1].extend(k);
        sq[1].expand(k,i);
    }
    cout<<bfs1()<<'\n'<<bfs2()<<'\n'<<bfs3()<<'\n'<<bfs4();

    return 0;
}