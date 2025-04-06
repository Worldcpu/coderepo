#include<iostream>
using namespace std;
int main(){
    freopen("pre.out","w",stdout);
    cout<<"int num[57]={";
    for(int i=0;i<=56;i++){
        cout<<i*i<<",";
    }
    cout<<"};";
    return 0;
}