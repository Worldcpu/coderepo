#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=66,MQ=5e4+15;
int n,q;

struct XXJ{
    int p[MN],tim[MN];

    void insert(int x,int time){
        for(int i=62;i>=0;i--){
            if((x>>i)&1){
                if(tim[i]){
                   if(tim[i]<time){
                        swap(p[i],x);
                        swap(time,tim[i]);
                   } 
                    x^=p[i];
                }else{
                    p[i]=x;
                    tim[i]=time;
                    break;
                }
            }
        }
    }

    int getmx(int l){
        int ans=0;
        for(int i=62;i>=0;i--){
            if(p[i]&&tim[i]>=l) ans=max(ans,ans^p[i]);
        }
        return ans;
    }

}xj[MQ];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        xj[i]=xj[i-1];
        xj[i].insert(x, i);
    }
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<xj[r].getmx(l)<<'\n';
    }
    

    return 0;
}