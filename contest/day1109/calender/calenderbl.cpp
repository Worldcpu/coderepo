#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=120;
int n,a[MN],mna,ans;
unordered_set<int> st;


signed main(){
    freopen("calender.in","r",stdin);
    freopen("calender.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    mna=*min_element(a+1,a+1+n);
    for(int i=1;i<=mna/4;i++){
        st.clear();
        for(int j=1;j<=n;j++){
            st.insert(a[j]%i);
        } 
        if(st.size()<=3){
            ans+=i;
        }
    }
    cout<<ans;

    return 0;
}