#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string lst;

struct Node{
    string ls,rs;
    int ans;

    Node(){
        ans=0,ls="",rs="";
    }

    Node(const string &st){
        ans=(st.find("haha"))!=string::npos;
        ls=st.substr(0,min(4ll,(int)st.length())),rs=st.substr(max(0ll,(int)st.length()-4));
    }

    friend Node operator +(const Node &x,const Node &y){
        Node ret=x;
        ret.ls+=y.ls;
        ret.rs+=y.rs;
        ret.ls=ret.ls.substr(0,min(4ll,(int)ret.ls.length()));
        ret.rs=ret.rs.substr(max(0ll,(int)ret.rs.length()-4));
        ret.ans+=y.ans;
        int rss=(x.rs.find("haha")!=string::npos),lss=((y.ls.find("haha"))!=string::npos),res=0;
        string st=x.rs+y.ls;
        for(int i=0;i<=(int)st.length()-4;i++){
            if(st.substr(i,4)=="haha") res++;
        }
        ret.ans+=res-rss-lss;
        return ret;
    }

};
map<string,Node> mp;

void solve(){
    cin>>n;
    string lst;
    for(int i=1;i<=n;i++){
        string x,y,z;
        string op,tmp;
        cin>>x>>op;
        if(op==":="){
            cin>>y;
            mp[x]=Node(y);
            lst=x;
        }else{
            cin>>y>>tmp>>z;
            mp[x]=mp[y]+mp[z];
            lst=x;
        }
    }
    cout<<mp[lst].ans<<'\n';
    mp.clear();
}

signed main(){
    freopen("haha.in","r",stdin);
    freopen("haha.out","w",stdout);
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}