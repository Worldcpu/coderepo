#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
int n,ans;
string a,b,c;
unordered_map<char,int> cnt;
set<char> st;

void init(){
    ans=(a[0]==b[n-2])+(a[0]==c[n-1])+(b[n-2]==c[n-1]);
    cnt.clear();
    st.clear();
}

void insert(char x){
    ++cnt[x];
    if(cnt[x]==1){
        st.insert(x);
    }
}

void del(char x){
    --cnt[x];
    if(cnt[x]==0) st.erase(st.find(x));
}

int lcp(const string &s,const string &t,int i,int j,int k){
    int ret=0;
    for(;i+ret<j&&j+ret<k&&ret<3;ret++){
        if(s[i+ret]!=t[j+ret]) break;
    }
    return ret;
}

int calc(int i,int j){
    return lcp(a,b,0,i,j)+lcp(b,c,i,j,n)+lcp(a,c,0,j,n);
}

bool checkst(char x,char y){
    for(auto p:st){
        if(p!=x&&p!=y){
            return 1;
        }
    }
    return 0;
}

void solve(){
    cin>>n>>a>>b>>c;
    init();
    for(int i=5;i<n;i++) insert(c[i]);
    for(int i=1;i+1<n;i++){
        for(int len=1;i+len<n&&len<=3;len++){
            ans=min(ans,calc(i,i+len));
        }
        int mat1=lcp(a,b,0,i,n);
        if(checkst(a[0],b[i])) ans=min(ans,mat1);
        else ans=min(ans,mat1+(c.back()==b[i])+(c.back()==a[0]));
        del(c[i+4]);
    }
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}