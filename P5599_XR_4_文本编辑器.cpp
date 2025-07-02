#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,L=55;
int n,m,q,id,f[MN],len[MN],sum[MN];
string a,qry[MN];
vector<int> pre[MN];
unordered_map<char,int> mp;

struct ACAuto{
    int t[MN][62],fail[MN],end[MN],tot;

    void insert(string s){
        int p=0;
        for(auto c:s){
            int k=mp[c];
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[p]++;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<62;i++){
            if(t[0][i]) q.push(t[0][i]);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            end[u]+=end[fail[u]];
            for(int i=0;i<62;i++){
                int v=t[u][i];
                if(v){
                    fail[v]=t[fail[u]][i];
                    q.push(v);
                }else t[u][i]=t[fail[u]][i];
            }
        }
    }

    void getf(){
        int p=0;
        for(int i=1;i<=n;i++){
            p=t[p][mp[a[i-1]]];
            f[i]=end[p];
        }
    }
    
}ac;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1

    struct Lazytag{
        int id,hd;
    };
    struct Node{
        int l,r,val;
        Lazytag tag;
    }t[MN<<2];
    int lpos;
    string tmp;

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void dotag(int p,int id,int hd){
        t[p].tag={id,hd};
        int bef=t[p].l-hd,lid=(t[p].r-bef)%len[id],rid=(t[p].r-bef)/len[id];
        if(rid==0){
            t[p].val=pre[id][lid]-(hd?pre[id][hd-1]:0);
        }else t[p].val=pre[id][lid]+rid*sum[id]-(hd?pre[id][hd-1]:0);
    }

    void pushdown(int p){
        if(t[p].tag.id){
            int id=t[p].tag.id,hd=t[p].tag.hd,val=(hd+(t[ls].r-t[ls].l+1))%len[id];
            dotag(ls,id,hd);
            dotag(rs,id,val);
            t[p].tag.id=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=f[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modifyt(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            dotag(p,id,(t[p].l-lpos)%len[id]);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifyt(ls,fl,fr);
        if(mid<fr) modifyt(rs,fl,fr);
        pushup(p);
    }

    void modifyc(int p,int fl,int fr,bool tg){
        if(fl>fr) return;
        if(t[p].l==t[p].r){
            t[p].val=f[t[p].l];
            if(tg){
                t[p].tag={id,(t[p].l-lpos)%len[id]};
            }
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifyc(ls,fl,fr,tg);
        if(mid<fr) modifyc(rs,fl,fr,tg);
        pushup(p);
    }

    void modify(int p,int fl,int fr){
        if(fl>fr) return;
        if(t[p].l==t[p].r){
            if(t[p].tag.id){
                tmp+=qry[t[p].tag.id][t[p].tag.hd];
            }else tmp+=a[t[p].l-1];
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr);
        if(mid<fr) modify(rs,fl,fr);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        int ret=0;
        if(mid>=fl) ret+=query(ls,fl,fr);
        if(mid<fr) ret+=query(rs,fl,fr);
        return ret;
    }

    #undef ls
    #undef rs
}sg;

void initmp(){
	for(int i='A';i<='Z';i++)mp[i]=i-'A';
	for(int i='a';i<='z';i++)mp[i]=26+(i-'a');
	for(int i='0';i<='9';i++)mp[i]=52+(i-'0');
}

signed main(){
    initmp();
    cin>>n>>m>>q>>a;
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        ac.insert(s);
    }
    ac.build();
    ac.getf();
    sg.build(1,1,n);
    while(q--){
        int op,l,r,ls;
        cin>>op>>l>>r;
        ls=r-l+1;
        sg.lpos=l;
        if(op==1){
            int rpos=min(r,l+L),ret=0,p=0;
            sg.tmp="";
            sg.modify(1,l,rpos);
            for(int i=l;i<=rpos;i++){
                p=ac.t[p][mp[sg.tmp[i-l]]];
                ret+=ac.end[p];
            }
            cout<<ret+sg.query(1,rpos+1,r)<<'\n';
        }else{
            string st;
            cin>>st;
            len[++id]=st.size();
            pre[id].resize(len[id]);
            int lpos=max(1ll,l-L+1),rpos=min(n,r+L-1);
            int p=0;
            if(ls<=L*2+len[id]*2){
                sg.tmp="";
                sg.modify(1,lpos,rpos);
                for(int i=lpos;i<=rpos;i++){
                    char ch=(i<l||i>r?sg.tmp[i-lpos]:st[(i-l)%len[id]]);
                    p=ac.t[p][mp[ch]];
                    if(i>=l) f[i]=ac.end[p];
                }
                sg.modifyc(1,l,r,1);
                sg.modifyc(1,r+1,rpos,0);
            }else{
                int led=l+L-1,red=r-L+1;
                while((led-l)%len[id]) led++;
                sg.tmp="";
                sg.modify(1,lpos,l-1);
                for(int i=lpos;i<led+len[id];i++){
                    char ch=(i<l?sg.tmp[i-lpos]:st[(i-l)%len[id]]);
                    p=ac.t[p][mp[ch]];
                    if(i>=l){
                        if(i<led) f[i]=ac.end[p];
                        else pre[id][i-led]=(i>led?pre[id][i-led-1]:0)+ac.end[p];
                    }
                }
                sum[id]=pre[id][len[id]-1];
                sg.modifyc(1,l,led-1,1);
                sg.modifyt(1,led,r);

                sg.tmp="";
                sg.modify(1,r+1,rpos);
                for(int i=red;i<=rpos;i++){
                    char ch=(i>r?sg.tmp[i-r-1]:st[(i-l)%len[id]]);
                    p=ac.t[p][mp[ch]];
                    if(i>r){
                        f[i]=ac.end[p];
                    }
                }
                sg.modifyc(1,r+1,rpos,0);
            }
            qry[id]=st;
        }
    }
    return 0;
}
