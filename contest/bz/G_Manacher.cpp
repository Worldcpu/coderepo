#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e7+15;
int n;
string st;

namespace Manacher{
    int p[MN];
    string str;

    void prework(){
        str.push_back('%');
        for(auto p:st){
            str.push_back(p);
            str.push_back('#');
        }
        str.push_back('$');
    }

    void manacher(){
        int r=0,c;
        for(int i=1;i<str.size();i++){
            if(i<r){
                p[i]=min(p[2*c]-i,r-i);
            }
            while(str[i+p[i]]==str[i-p[i]]) p[i]++;
            if(i+p[i]>r){
                r=i+p[i];
                c=i;
            }
        }
    }

}


int main(){
    cin>>st;
    Manacher::prework();
    Manacher::manacher();
    cout<<*max_element(Manacher::p,Manacher::p+Manacher::str.size());
    return 0;
}