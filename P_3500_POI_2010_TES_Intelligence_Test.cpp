#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,q;

struct Seq{
    vector<int> nxt[MN];

    int gnxt(int i,int c){
        auto ret=lower_bound(nxt[c].begin(),nxt[c].end(),i+1);\
        if(ret==nxt[c].end()) return 0;
        return *ret;
    }

}sq;


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        sq.nxt[x].push_back(i);
    }
    cin>>q;
    while(q--){
        int len,lst=0,flag=1;
        cin>>len;
        for(int i=1;i<=len;i++){
            int x;
            cin>>x;
            lst=sq.gnxt(lst,x);
            if(!lst) flag=0;
        }
        if(flag) cout<<"TAK\n";
        else cout<<"NIE\n";
    }

    return 0;
}