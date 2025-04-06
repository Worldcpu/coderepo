#include<bits/stdc++.h>
using namespace std;
const int MN=128;
struct previous{
    int i,j;
};
int T,n,m;
string a,b;
int f[MN][MN],ret;
set<string> st;
vector<previous> pre[MN][MN];

// set<string> st;
// void dfs(int i,int j,int len,string s){
//     if(len==ret){
//         st.insert(s);
//         return;
//     }
//     if(i>n||j>m||len>ret) return;
//     if(a[i]==b[j]){
//         s.push_back(a[i]);
//         dfs(i+1,j+1,len+1,s);
//         s.pop_back();
//     }
//     dfs(i+1,j,len,s);
//     dfs(i,j+1,len,s);
// }

void getans(int i,int j,string s){
    s.push_back(a[i]);
    for(auto v:pre[i][j]){
        getans(v.i,v.j,s);
    }
    if(s.length()==ret){
        reverse(s.begin(),s.end());
        st.insert(s);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin>>T;
    while (T--)
    {
        // memset(f,0,sizeof(f));
        st.clear();
        cin>>a>>b;
        n=a.length(),m=b.length();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                f[i][j]=1;
                pre[i][j].clear();
            }
        }
        a=' '+a;
        b=' '+b;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i]==b[j]){
                    for(int l=1;l<i;l++){
                        for(int r=1;r<j;r++){
                            if(a[l]!=b[r]) continue;
                            if(f[l][r]+1>f[i][j]){
                                f[i][j]=f[l][r]+1;
                                pre[i][j].clear();
                                pre[i][j].push_back({l,r});
                            }else if(f[l][r]+1==f[i][j]){
                                pre[i][j].push_back({l,r});
                            }
                        }
                    }
                }

            }
        }
        ret=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                ret=max(ret,f[i][j]);
            }
        }
        // cout<<"LEN:"<<ret<<'\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(f[i][j]==ret){
                    getans(i,j,"");
                }
            }
        }
        for(auto it=st.begin();it!=st.end();it++){
            cout<<*it<<'\n';
        }
        // dfs(1,1,0,"");
        // for(auto it=st.begin();it!=st.end();it++){
        //     cout<<*it<<'\n';
        // }
    }
    return 0;
}