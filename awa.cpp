#include<iostream>
using namespace std;

void dfs(int u){
    if(u>=200){
        cout<<"2";
        return;
    }
    cout<<"2^{";
    dfs(u+1);
    cout<<"}";
}

int main(){
    freopen("ans.out","w",stdout);
    dfs(1);
    return 0;
}
