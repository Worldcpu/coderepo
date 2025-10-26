#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
string st;


int main(){
    cin>>st;
    if(*st.begin()==*--st.end()){
        cout<<((st.length()%2)?"Second":"First");
    }else{
        cout<<((st.length()%2)?"First":"Second");
    }


    return 0;
}