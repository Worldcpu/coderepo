#include<bits/stdc++.h>
using namespace std;
string s;

int main(){
    cin>>s;
    int x,y;
    x=s[0]-'0',y=s[2]-'0';
    cerr<<x<<' '<<y;
    if(y%8==0){
        if(x==8){
            cout<<"8-8";
            return 0;
        }
        y=1;
        x++;
    }else y++;
    cout<<x<<'-'<<y;
    return 0;
}