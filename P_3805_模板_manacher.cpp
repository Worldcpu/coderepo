// TODO：学麻辣烫车
#include<iostream>
#include<cstring>
using namespace std;
const int MN=1.1*1e7+15;
string s1,s;
int p[MN*2];
void change(){
    s.push_back('$');
    s.push_back('#');
    for(int i=0;i<s1.length();i++){
        s.push_back(s1[i]);
        s.push_back('#');
    }
    s.push_back('&');
}
void manacher(){
    int r=0,c;
    for(int i=1;i<s.length();i++){
        if(i<r){
            p[i]=min(p[c*2-i],r-i);
        }
        while (s[i+p[i]+1]==s[i-p[i]-1])
        {
            p[i]++;
        }
        if(p[i]+i>r){
            r=p[i]+i;
            c=i;
        }
    }
}
int main(){
    cin>>s1;
    change();
    // cout<<s<<endl;
    manacher();
    int ans=0;
    for(int i=0;i<s.length();i++){
        ans=max(ans,p[i]);
    }
    // for(int i=0;i<s.length();i++){
    //     cout<<p[i]<<" ";
    // }
    // cout<<endl;
    cout<<ans;
    return 0;
}