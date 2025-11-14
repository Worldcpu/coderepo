#include<bits/stdc++.h>
#include "../../random.h"
using namespace std;
using namespace Rand;
constexpr int N=5;
unordered_set<int> st;
rnd rd;


int main(){
    cout<<N<<'\n';
    for(int i=1,dtot=0;i<=N;i++){
        int op=rd.gen(1,2);
        if(op==1){
            dtot++;
            cout<<op<<' '<<rd.gen(-10,10)<<' '<<rd.gen(-10,10)<<' '<<rd.gen(-10,10)<<'\n';
            st.insert(dtot);
        }else{
            if(st.empty()){
                i--;
                continue;
            }
            int siz=rd.gen(1,(int)st.size());
            int qwq=-1;
            for(auto p:st){
                siz--;
                if(siz==0){
                    qwq=p;
                    break;
                }
            }
            assert(qwq!=-1);
            st.erase(qwq);
            cout<<op<<' '<<qwq<<'\n';
        }
    }
    return 0;
}