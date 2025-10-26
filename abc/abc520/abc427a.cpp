
#include<bits/stdc++.h>
using namespace std;
int n;
string st;


int main(){
    cin>>st;
    n=st.length();
    st=" "+st;
    for(int i=1;i<=n;i++){
        if(i==(n+1)/2) continue;
        cout<<st[i];
    }

    return 0;
}