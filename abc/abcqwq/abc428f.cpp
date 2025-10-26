#include <bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,q,w[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1

    struct Node {
        int a, b, tag;
    } t[MN << 2];

    inline int ceil_div_ll(int a, int b) {
        if (a >= 0) return (a + b - 1) / b;
        else return a / b; 
    }

    void dotag(int p, int a, int b) {
        t[p].tag = 1;
        t[p].a = a;
        t[p].b = b;
    }

    void pushdown(int p) {
        if(t[p].tag) {
            dotag(ls, t[p].a, t[p].b);
            dotag(rs, t[p].a, t[p].b);
            t[p].tag = 0;
        }
    }

    void modify(int p, int l, int r, int ql, int qr, int A, int B) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            dotag(p, A, B);
            return;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(ls, l, mid, ql, qr, A, B);
        if (qr > mid) modify(rs, mid+1, r, ql, qr, A, B);
    }

    pir querypos(int p, int l, int r, int pos) {
        if (t[p].tag) {
            return {t[p].a, t[p].b};
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) return querypos(ls, l, mid, pos);
        else return querypos(rs, mid+1, r, pos);
    }

    int query(int p, int l, int r, int S) {
        if (t[p].tag) {
            int A = t[p].a;
            int B = t[p].b;
            if (A == 0) {
                int A_num = S - 2*B;
                int th = ceil_div_ll(A_num, 2);
                auto it=lower_bound(w+l,w+r+1,th);
                int pos = it - w;
                if (pos > r) return 0;
                return r - pos + 1;
            } else { 
                if (S > 2*B) return 0;
                int A_num = 2*B - S;
                int th = ceil_div_ll(A_num, 2);
                auto it=lower_bound(w+l,w+r+1,th);
                int pos = it - w;
                if (pos > r) return 0;
                return r - pos + 1;
            }
        }
        int mid=(l+r) >> 1;
        return query(ls, l, mid, S)+query(rs, mid+1, r, S);
    }
}sg;







signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    sg.dotag(1,0,0);
    cin>>q;
    while(q--){
        int op,v;
        cin>>op;
        if(op==1){
            cin>>v;
            auto p=sg.querypos(1,1,n,v);
            int nxtl=(p.first*w[v]+p.second);
            sg.modify(1,1,n,1,v,0,nxtl);
        }
        if(op==2){
            cin>>v;
            auto p=sg.querypos(1,1,n,v);
            int nxtr=(p.first*w[v]+p.second)+w[v];
            sg.modify(1,1,n,1,v,-1,nxtr);
        }
        if(op==3){
            int x;
            cin>>x;
            cout<<sg.query(1,1,n,2*x+1)<<'\n';
        }
    }
    return 0;
}

