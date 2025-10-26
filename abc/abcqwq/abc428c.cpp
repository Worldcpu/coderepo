#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
int q,sum,len;
set<pir> st;
string s;

int main(){
    cin>>q;
    while(q--){
        int op;
        char c;
        cin>>op;
        if(op==1){
            cin>>c;
            s.push_back(c);
            if(c=='('){
                sum++;
            }else{
                sum--;
            }
            st.insert(pir(sum,s.length()));
        }else{
            st.erase(pir(sum,s.length()));           
            sum+=(s[s.length()-1]=='('?-1:1);
            s.pop_back();
        }
        if(sum==0&&st.begin()->first==0){
            cout<<"Yes\n";
        }else cout<<"No\n";
    }

    return 0;
}