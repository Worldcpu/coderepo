#include<bits/stdc++.h>
using namespace std;
constexpr int T=50;

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}

string randstr(int len){
    string st;
    for(int i=0;i<len;i++){
        st.push_back((char)(getrd(0,5)+'a'));
    }
    return st;
}

int main(){
    srand(time(0));
    ios::sync_with_stdio(0);
    cout.tie(0);
    cout<<T<<'\n';
    int qwq=T;
    while(qwq--){
        int n=getrd(10,20);
        cout<<n<<'\n';
        for(int i=1;i<=n;i++){
            cout<<randstr(getrd(50,100))<<' '<<getrd(5,10)<<'\n';
        }
    }

    return 0;
}