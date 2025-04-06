#include<iostream>
#include<cstring>
#define ull unsigned long long
using namespace std;
const int MN=1e6+15;
const ull base=131;
string s;
int m,n,yl,pos[MN];
ull h[MN],pw[MN];
void update(int x){
    for(int i=x;i<=n;i++){
        h[i]=h[i-1]*base+s[i];
    }
}
ull geth(int l,int r){
    return h[r]-h[l-1]*pw[r-l+1];
}
int query(int x,int y){
    if(x>y) swap(x,y);
    int l=0,r=n-y+1,ans=0;
    while (l<=r)
    {
        int mid=(l+r)>>1;
        if(geth(x,x+mid-1)==geth(y,y+mid-1)){
            l=mid+1;
        }else r=mid-1;
    }
    return r;
}
int main(){
    cin>>s>>m;
    yl=n=s.length();
    for(int i=1;i<=n;i++){
        pos[i]=i;
    }
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*base;
    }
    s=" "+s;
    update(1);
    while (m--)
    {
        char op,in;
        int x,y;
        cin>>op;
        if(op=='Q'){
            cin>>x>>y;
            cout<<query(pos[x],pos[y])<<endl;
        }else{
            cin>>in>>x;
            string t;
            t.push_back(in);
            s.insert(x,t);
            n++;
            // cout<<"AFT S:"<<s<<'\n';
            for(int i=yl;i>=1;i--){
                if(pos[i]>=x) pos[i]++;
                else break;
            }
            update(x);
            // for(int i=1;i<=n;i++){
            //     cout<<pos[i]<<" ";
            // }
            // cout<<'\n';
        }
    }
    
    return 0;
}