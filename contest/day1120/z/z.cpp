#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
#define ppir pair<pir,pir>
using namespace std;
constexpr int MN=5200;
int n,m,q;
map<ppir,int> mp;
mt19937 mt(random_device{}());

struct BIT{
    int t[MN][MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int y,int k){
        while(x<MN){
            int tmpy=y;
            while(tmpy<MN){
                t[x][tmpy]^=k;
                tmpy+=lowbit(tmpy);
            }
            x+=lowbit(x);
        }
    }

    int query(int x,int y){
        int ret=0;
        while(x){
            int tmpy=y;
            while(tmpy){
                ret^=t[x][tmpy];
                tmpy-=lowbit(tmpy);
            }
            x-=lowbit(x);
        }
        return ret;
    }
}bit;

signed main(){
    cin>>n>>m>>q;
    while(q--){
        int op,x1,y1,x2,y2;
        cin>>op>>x1>>y1>>x2>>y2;
        if(op==1){
            auto id=mt();
            mp[ppir(pir(x1,y1),pir(x2,y2))]=id;
            bit.modify(x1,y1,id);
            bit.modify(x2+1,y1,id);
            bit.modify(x1,y2+1,id);
            bit.modify(x2+1,y2+1,id);
        }else if(op==2){
            auto id=mp[ppir(pir(x1,y1),pir(x2,y2))];
            bit.modify(x1,y1,id);
            bit.modify(x2+1,y1,id);
            bit.modify(x1,y2+1,id);
            bit.modify(x2+1,y2+1,id);
        }else{
            int x=bit.query(x1,y1),y=bit.query(x2,y2);
            if(x==y){
                cout<<"Yes\n";
            }else cout<<"No\n";
        }
    }


    return 0;
}