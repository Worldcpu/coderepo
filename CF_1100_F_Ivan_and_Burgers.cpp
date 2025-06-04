#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,MP=32;
int n,q,a[MN];

struct prexxj{
    int num,pos[MN][MP],p[MN][MP];

    void insert(int x){
        num++;
        for(int i=0;i<MP;i++){
            p[num][i]=p[num-1][i];
            pos[num][i]=pos[num-1][i];
        }
        int P=num;
        for(int i=MP-1;i>=0;i--){
            if((x>>i)&1){
                if(!p[num][i]){
                    p[num][i]=x;
                    pos[num][i]=P;
                    break;
                }else{
                    if(pos[num][i]<P){
                        swap(pos[num][i],P);
                        swap(p[num][i],x);
                    }
                    x^=p[num][i];
                }
            }
        }
    }

    int getmx(int l,int r){
        int ans=0;
        for(int i=31;i>=0;i--){
            if(pos[r][i]<l) continue;
            if((ans^p[r][i])>ans) ans^=p[r][i];
        }
        return ans;
    }

}pxj;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        pxj.insert(x);
    }
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<pxj.getmx(x,y)<<'\n';
    }
    return 0;
}
