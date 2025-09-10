#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MV=2e5+15;
struct Node{
    int pos,tim,hp;
}st[MN];
int n,q,c[MN],R[MN],rt[MN],top,ans;
vector<int> vct[MN];

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson,k,b;
    }t[MN<<5];
    int tot;

    void pushup(int p){
        t[p].k=t[ls].k+t[rs].k;
        t[p].b=t[ls].b+t[rs].b;
    }

    void build(int &p,int l,int r){
        p=++tot;
        if(l==r){
            t[p].k=R[l];
            t[p].b=0;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    int modify(int lst,int l,int r,int pos){
        int p=++tot;
        t[p]=t[lst];
        if(l==r){
            t[p].k=0;
            t[p].b=c[l];
            return p;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) t[p].lson=modify(t[lst].lson,l,mid,pos);
        else t[p].rson=modify(t[lst].rson,mid+1,r,pos);
        pushup(p);
        return p;
    }

    int query(int p,int l,int r,int fl,int fr,int x){
        if(!p) return 0;
        if(l>=fl&&r<=fr){
            return x*t[p].k+t[p].b;
        }
        int mid=(l+r)>>1;
        int ret=0;
        if(mid>=fl) ret+=query(ls,l,mid,fl,fr,x);
        if(mid<fr) ret+=query(rs,mid+1,r,fl,fr,x);
        return ret;
    }

    void find(int p,int l,int r,int fl,int x,int &hp,int &pos){
        if(!p) return;
        int mid=(l+r)>>1;
        if(l>=fl){
            int v=x*t[p].k+t[p].b;
            if(hp>=v){
                pos=r;
                hp-=v;
                return;
            }
            if(l==r) return;
            find(ls,l,mid,fl,x,hp,pos);
            if(pos==mid){
                find(rs,mid+1,r,fl,x,hp,pos);
            }
            return;
        }else if(mid<fl){
            find(rs,mid+1,r,fl,x,hp,pos);
            return;
        }
        find(ls,l,mid,fl,x,hp,pos);
        if(pos==mid){
            find(rs,mid+1,r,fl,x,hp,pos);
        }
    }

}sg;



signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>R[i];
        int t=c[i]/R[i]+1;
        if(t<MV) vct[t].push_back(i);
    }
    sg.build(rt[0],1,n);
    for(int i=1;i<=MV;i++){
        rt[i]=rt[i-1];
        for(auto p:vct[i]){
            rt[i]=sg.modify(rt[i],1,n,p);
        }
    }
    cin>>q;
    st[0].pos=n+1;
    for(int i=n;i>=1;i--){
        st[++top].pos=i;
        st[top].hp=c[i];
    }
    while(q--){
        int t,h;
        cin>>t>>h;
        while(top){
            if(!h) break;
            auto &tp=st[top];
            int tim=t-tp.tim;
            if(st[top-1].pos-tp.pos==1){
                int hp=min(c[tp.pos],R[tp.pos]*tim+tp.hp);
                if(hp>h){
                    tp.hp=hp-h;
                    tp.tim=t;
                    break;  
                }
                top--;
                h-=hp;
                continue;
            }
            int hp=sg.query(rt[tim],1,n,tp.pos,st[top-1].pos-1,tim);
            if(hp>h){
                int pos=tp.pos-1;
                sg.find(rt[tim],1,n,tp.pos,tim,h,pos);
                pos++;
                if(pos==st[top-1].pos-1){
                    top--;
                }else tp.pos=pos+1;
                st[++top].pos=pos;
                st[top].tim=t;
                st[top].hp=min(c[pos],R[pos]*tim)-h;
                break;
            }else{
                h-=hp;
                top--;
            }
        }
        if(!top){
            ans+=h;
        }
        if(st[top].pos!=1){
            st[++top].pos=1;
            st[top].tim=t;
            st[top].hp=0;
        }
    }   
    cout<<ans;
    return 0;
}