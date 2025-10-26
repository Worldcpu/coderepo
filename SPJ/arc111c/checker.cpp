#include "../testlib.h"
#include<bits/stdc++.h>
#define tpir tuple<int,int,string>
using namespace std;
int n;
vector<int> a,b,p,ta,tb,tp;

// 答案所需步数（包含无解），答案是否符合要求，报错信息（拼接）
tpir checkans(InStream &it){
    int st = it.readInt(-1, 1000000000, "steps");
    if (st == -1) {

        // 这里应该有一个无解的检查，但是会暴漏做法所以没加。
        return tpir(st,1,"ok");
    }
    ta = a; tb = b; tp = p;

    for (int step = 1; step <= st; ++step) {
        int x = it.readInt(1, n);
        int y = it.readInt(1, n);
        // 不能和自己交换
        if (x == y) {
            string msg = "step " + to_string(step) + ": invalid swap with same index (" + to_string(x) + ").";
            return tpir(st, 0, msg);
        }
        // 检查 x 是否已经疲劳（即当前拿的行李重量 >= 其体重）
        int luggage_x = tp[x];
        if (ta[x] <= tb[luggage_x]) {
            // 在此步尝试把疲劳的人选入交换——报错并指出详情
            stringstream ss;
            ss << "step " << step << ": person " << x
               << " is invaild and cannot participate. "
               << "person weight a[" << x << "]=" << ta[x] << " <= "
               << "current luggage weight b[" << luggage_x << "]=" << tb[luggage_x]
               << " (luggage id " << luggage_x << ").";
            return tpir(st, 0, ss.str());
        }
        int luggage_y = tp[y];
        if (ta[y] <= tb[luggage_y]) {
            stringstream ss;
            ss << "step " << step << ": person " << y
               << " is invaild and cannot participate. "
               << "person weight a[" << y << "]=" << ta[y] << " <= "
               << "current luggage weight b[" << luggage_y << "]=" << tb[luggage_y]
               << " (luggage id " << luggage_y << ").";
            return tpir(st, 0, ss.str());
        }
        swap(tp[x], tp[y]);
    }

    // 最终检查：每个人是否拿到了自己编号相同的行李
    for (int i = 1; i <= n; ++i) {
        if (tp[i] != i) {
            stringstream ss;
            ss <<"person " << i
               << " holds luggage " << tp[i] << " but expected " << i << ".";
            return tpir(st, 0, ss.str());
        }
    }

    // 是否多输出了
    if (!it.seekEof()) {
        return tpir(st, 0, "extra tokens after declared steps.");
    }

    return tpir(st, 1, "ok");
}

int main(int argc,char *argv[]){
    registerTestlibCmd(argc,argv);

    n=inf.readInt(1,200000,"n");
    a.resize(n+1),b.resize(n+1),p.resize(n+1);
    for(int i=1;i<=n;i++){
        a[i]=inf.readInt(1,1000000000,"a[i]");
    }
    for(int i=1;i<=n;i++){
        b[i]=inf.readInt(1,1000000000,"b[i]");
    }
    for(int i=1;i<=n;i++){
        p[i]=inf.readInt(1,n,"p[i]");
    }
    auto [ra1,ra2,ra3]=checkans(ans);
    auto [ro1,ro2,ro3]=checkans(ouf);

    // 对于有解答案的合法性判断

    if(ra1!=-1&&ra2==0){
        quitf(_fail,"Jury's %s",ra3.c_str());
    }
    if(ro1!=-1&&ro2==0){
        quitf(_wa,"Participant's %s",ro3.c_str());
    }   

    // 无解判断
    
    if(ra1!=-1&&ro1==-1){
        quitf(_wa,"Jury found the answer but the participant didn't.");
    }else if(ra1==-1&&ro1!=-1){
        quitf(_fail,"Parcipant found the answer but the Jury didn't.");
    }

    if(ra1==-1&&ro1==-1){
        quitf(_ok,"No solution.");
    }

    // 有解判断

    if(ra1>ro1){
        quitf(_fail,"Jury's answer's steps is worse than participant's answer's steps.");
    }
    if(ro1>ra1){
        quitf(_wa,"Participant's answer's steps is worse than Jury's answer's steps.");
    }
    quitf(_ok,"%d steps,both answer is vaild",ra1);

    return 0;
}
