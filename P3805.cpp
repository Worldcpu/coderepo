#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e7+15;
int n;
string st;

namespace Manacher{
    int p[MN];

    void prework(){
        string qwq;
        qwq.push_back('~');
        qwq.push_back('#');
        for(auto p:st){
            qwq.push_back(p);
            qwq.push_back('#');
        }
        qwq.push_back('^');
        st=qwq;
    }

    void manacher(){
        int r=0,c;
        for(int i=1;i<st.size();i++){
            if(i<r){
                p[i]=min(p[2*c-i],r-i);
            }
            while(st[i-p[i]-1]==st[i+p[i]+1]) p[i]++;
            if(p[i]+i>r){
                r=i+p[i];
                c=i;
            }
        }
    }

}using namespace Manacher;

int main(){
    cin>>st;
    prework();
    manacher();
    cout<<*max_element(p,p+st.size());
    return 0;
}