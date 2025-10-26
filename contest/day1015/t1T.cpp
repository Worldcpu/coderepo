#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int n,t,ans,cnt0;
string st;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int mn,mncnt,se,secnt;

        Node(int mnn=0,int mnccnt=0,int see=INF,int secntt=0){
            mn=mnn,mncnt=mnccnt,se=see,secnt=secntt;
        }

        friend Node operator+(const Node &x,const int y){
            return Node(x.mn+y,x.mncnt,x.se+y,x.secnt);
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.mn=min(x.mn,y.mn);
            if(ret.mn==x.mn){
                ret.mncnt+=x.mncnt;
            }
            if(ret.mn==y.mn){
                ret.mncnt+=y.mncnt;
            }
            ret.se=min({x.se,y.se,(ret.mn==x.mn?INF:x.mn),(ret.mn==y.mn?INF:y.mn)});
            if(ret.se==x.se) ret.secnt=x.secnt;
            else if(ret.se==x.mn) ret.secnt=x.mncnt;
            if(ret.se==y.se) ret.secnt=y.secnt;
            else if(ret.se==y.mn) ret.secnt=y.mncnt;
            return ret;
        }
    };

    struct SNode{
        int l,r,add;
        Node val;
    }t[MN<<2];

    void doadd(int p,int k){
        t[p].val=t[p].val+k;
        t[p].add+=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].add=0;
        if(l==r){
            t[p].val=Node((st[l]=='1'?INF:0),1,INF,0);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void add(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) add(ls,fl,fr,k);
        if(mid<fr) add(rs,fl,fr,k);
        pushup(p);
    }

    Node query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return query(rs,fl,fr);
        if(mid>=fr) return query(ls,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
    }
}sg;

void modify(int l,int r){
    assert(l<=r);
    if(l>n){
        l-=n;
        r-=n;
        if(r>n) r=n;
        sg.add(1,l,r,1);
    }else if(r<1){
        r+=n;
        l+=n;
        if(l<1) l=1;
        sg.add(1,l,r,1);
    }else if(r>=1&&l<1){
        sg.add(1,1,r,1);
        l+=n;
        if(l<1) l=n;
        sg.add(1,l,n,1);
    }else if(l<=n&&r>n){
        sg.add(1,l,n,1);
        r-=n;
        if(r>n) r=n;
        sg.add(1,1,r,1);
    }else if(l>=1&&r<=n){
        sg.add(1,l,r,1);
    }
    else{
        cerr<<l<<' '<<r<<'\n';
        exit(1);
    }
}

auto query(int l,int r){
    if(l>r) return Segment::Node(INF,-INF,INF,-INF);
    if(l>n){
        l-=n;
        r-=n;
        if(r>n) r=n;
        return sg.query(1,l,r);
    }else if(r<1){
        r+=n;
        l+=n;
        if(l<1) l=1;
        return sg.query(1,l,r);
    }else if(r>=1&&l<1){
        auto tmp=sg.query(1,1,r);
        l+=n;
        if(l<1) l=n;
        return tmp+sg.query(1,l,n);
    }else if(l<=n&&r>n){
        auto tmp=sg.query(1,l,n);
        r-=n;
        if(r>n) r=n;
        return tmp+sg.query(1,1,r);
    }else if(l>=1&&r<=n){
        return sg.query(1,l,r);
    }
    else{
        cerr<<l<<' '<<r<<'\n';
        exit(2);
    }
}

void init(){
    ans=cnt0=0;
}

void solve(){
    cin>>n>>t>>st;
    cerr<<n<<' '<<t<<'\n'<<st<<'\n';
    init();
    st=" "+st;
    sg.build(1,1,n);
    for(int i=1,flag=0;i<=n;i++){
        // if(i==50){
        //     cerr<<"QWQ\n";
        // }
        if(st[i]=='1'){
            if(!flag){
                modify((i-1)-t+1,i-1);
                flag=1;
            }
            if(i==n&&st[1]!='1'){
                modify(i+1,(i+1)+t-1);
            }
        }else{
            if(flag){
                flag=0;
                modify(i,i+t-1);
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     cerr<<sg.query(1,i,i).mn<<' ';
    // }
    auto tot=sg.query(1,1,n);
    if(tot.mn==0){
        cnt0=tot.mncnt;
        ans=tot.mncnt;
    }
    // cerr<<ans;
    for(int i=1,flag=0;i<=n;i++){
        if(st[i]=='1'){
            if(!flag){
                // modify((i-1)-t+1,i-1);
                auto qry=query((i-1-t+1),i-2);
                if(qry.mn==0){
                    if(qry.se==1){
                        ans=max(ans,cnt0+qry.secnt);
                    }
                }else if(qry.mn==1){
                    ans=max(ans,cnt0+qry.mncnt);
                }
                flag=1;
            }
        }else{
            if(flag){
                flag=0;
                // modify(i,i+t-1);
                auto qry=query((i+1),(i+t-1));
                if(qry.mn==0){
                    if(qry.se==1){
                        ans=max(ans,cnt0+qry.secnt);
                    }
                }else if(qry.mn==1){
                    ans=max(ans,cnt0+qry.mncnt);
                }
            }
        }
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    for(int i=1;i<=T;i++){
        cerr<<"TEST: "<<i<<'\n';
        solve();
    }

    return 0;
}

// 50 1
// 00000101000101011100100000010111100001000110100011
// 10001111101111111111110000111111110011101111110111

// 5 1
// 00001
