#include<iostream>
#include<cstring>
using namespace std;
const int MN=1.1*1e7+15;
string s1,s;
int p[MN*2];//这里一定要开2倍！
void change(){//直接用pushback怎么说，stl的魅力
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
        if(i<r){//将两种情况合并
            p[i]=min(p[c*2-i],p[c]+c-i);
        }
        while (s[i+p[i]+1]==s[i-p[i]-1])
        {//暴力扩展，注意加一和减一是向外拓展
            p[i]++;
        }
        if(p[i]+i>r){//如果超范围啦，直接就更新r和c变为当前节点的回文串
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
        ans+=(p[i]+1)/2;
    }
    cout<<ans;
    return 0;
}