#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e5+15;
int n;
long long ans;

struct SAM{
    map<int,int> nxt[MN];
    int fa[MN],len[MN],cnt_init[MN],cnt[MN],tot,lst;

    void init(){
        tot=0;
        lst=0;
        nxt[0].clear();
        fa[0]=-1;
        len[0]=0;
        cnt_init[0]=0;
    }
    
    void extend(int c){
        int cur=++tot;
        len[cur]=len[lst]+1;
        cnt_init[cur]=1;
        nxt[cur].clear();
        int p=lst;
        while(p!=-1&&!nxt[p][c]){
            nxt[p][c]=cur;
            p=fa[p];
        }
        if(p==-1) fa[cur]=0;
        else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }
            else{
                int nq=++tot;
                len[nq]=len[p]+1;
                nxt[nq]=nxt[q];
                fa[nq]=fa[q];
                cnt_init[nq]=0;
                while(p!=-1&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
                fa[q]=fa[cur]=nq;
            }
        }
        lst=cur;
        ans+=len[cur]-len[fa[cur]];
    }

}sam;


int main(){
    cin>>n;
    sam.init();
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        sam.extend(x);
        cout<<ans<<'\n';
    }
    return 0;
}
