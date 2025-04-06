#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
#define inf 0x3f3f3f3f
#define maxn 50000005
using namespace std;

int les,nxt[maxn],ans=inf;
string s;

inline void exkmp() {
	les=s.size()-1;
	int j=0;
	nxt[0]=les+1;
	while(s[j]==s[1+j]&&j+1<=les) j++;
	nxt[1]=j;
	int maxp=1;
	rep(i,2,les) {
		if(i+nxt[i-maxp]<nxt[maxp]+maxp) nxt[i]=nxt[i-maxp];
		else {
			j=nxt[maxp]+maxp-i;
			j=max(j,0);
			while(s[j]==s[i+j]&&i+j<=les) j++;
			nxt[i]=j;
			maxp=i;
		}
	}
}//exkmp算法模板

void check() {
    rep(i, 0, les) { 
        if (i + nxt[i] == les + 1) {
            int L = nxt[i]; // 候选印章长度
            int pre = -1, max_gap = 0;
            for (int j = 0; j <= les;) {
                if (nxt[j] >= L) { // 当前位置可覆盖
                    if (pre != -1) {
                        max_gap = max(max_gap, j - pre);
                    }
                    pre = j; // 更新上一个覆盖点
                    j += L;  // 跳跃到下一个可能覆盖点
                } else { 
                    j++; // 无法覆盖，逐个检查
                }
            }
            // 检查末尾到最后一个pre的间隔
            if (pre != -1) {
                max_gap = max(max_gap, les + 1 - pre);
            }
            if (max_gap <= L) { 
                ans = min(ans, L); 
            }
        }
    }
}




int main() {
	ios::sync_with_stdio(false);
	cin>>s;
	exkmp();
	check();
	cout<<ans;
	return 0;
}