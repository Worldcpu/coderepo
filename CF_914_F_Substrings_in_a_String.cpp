#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,q;
string st;
bitset<MN> bit[26],ret;


int main(){
    cin>>st;
    n=st.length();
    for(int i=0;i<n;i++){
        bit[st[i]-'a'].flip(i);
    }
    cin>>q;
    while(q--){
        int op,x,y;
        string c;
        cin>>op>>x;
        --x;
        if(op==1){
            cin>>c;
            bit[st[x]-'a'][x]=0;
            st[x]=c[0];
            bit[st[x]-'a'][x]=1;
        }else{
            cin>>y>>c;
            --y;
            if(c.size()>y-x+1){
                cout<<0<<'\n';
                continue;
            }
            ret.set();
            for(int i=0;i<c.size();i++){
                ret&=bit[c[i]-'a']>>(i);
            }
            cout<<(ret>>(x)).count()-(ret>>(y-c.size()+2)).count()<<'\n';
        }
    }

    return 0;
}