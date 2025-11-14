#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,ha,hb,hc;
vector<int> op;

// ha>hc -> ha<=hb;
void sol1(){
    while(hb>ha){
        hb--;
        b>>=1;
        op.push_back(2);
    }
    for(int i=hb;i>=0;i--){
        // kb一定为 1
        int ka=(a>>i)&1,kc=(c>>i)&1;
        if(kc==1){
            if(ka==0){
                op.push_back(3);
            }
        }else{
            if(ka==1){
                op.push_back(3);
            }
        }
        op.push_back(2);
    }
    op.push_back(4);
}

// ha<=hc 
void sol2(){// 3k+1
    while(ha<hc){
        a<<=1;
        op.push_back(1);
        ha++;
    }
    if(hb!=hc){
        op.push_back(4);
    }
    for(int i=hc;i>=0;i--){
        // kb一定为1
        int ka=(a>>i)&1,kc=(c>>i)&1;
        if(kc==1){
            if(ka==0){
                op.push_back(3);
            }
        }else{
            if(ka==1){
                op.push_back(3);
            }
        }
        op.push_back(2);
    }
    op.push_back(4);
}

// hb>hc
void sol3(){ //2k+1 
    for(int i=hb;i>=0;i--){
        // kb一定为 1
        int ka=(a>>i)&1,kc=(c>>i)&1;
        if(kc==1){
            if(ka==0){
                op.push_back(3);
            }
        }else{
            if(ka==1){
                op.push_back(3);
            }
        }
        op.push_back(2);
    }
    op.push_back(4);
}

void init(){
    ha=__lg(a);
    hb=__lg(b);
    hc=__lg(c);
    op.clear();
}

int get(int x, int y) {
    return (x>>y)&1;
}

void solve(){
    cin>>a>>b>>c;
    init();
    if((a==0&&b==0&&c!=0)){
        cout<<-1<<'\n';
        return;
    }
    if(ha > hb){
        b ^= a;
        op.push_back(4);
        hb = __lg(b);
    }else if(ha < hb){
        a ^= b;
        op.push_back(3);
        ha = __lg(a);
    }
    if (ha < hc) {
        while(hb > 0) {
            if (get(a, hb) != get(c, hb + hc - ha)){
                a ^= b;
                ha = __lg(a);
                op.push_back(3);
            }
            b >>= 1;
            hb--;
            op.push_back(2);
        }
        if(get(a, hb) != get(c, hb + hc - ha)){
            a ^= b;
            ha = __lg(a);
            op.push_back(3);
        }
        while(ha < hc){
            a <<= 1;
            ha++;
            op.push_back(1);
            if (get(c, hc - ha) != 0) {
                a ^= b;
                ha = __lg(a);
                op.push_back(3);
            }
        }
        op.push_back(2);
        op.push_back(4);
    } else {
        while(hb >= 0){
            if (get(a, hb) != get(c, hb)) {
                a ^= b;
                ha = __lg(a);
                op.push_back(3);
            }
            b >>= 1;
            hb--;
            op.push_back(2);
        }
        op.push_back(4);
    }
    cout<<op.size()<<'\n';
    for(auto p:op) cout<<p<<' ';
    cout<<'\n';
}


signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}

