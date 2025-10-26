#include <bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;

constexpr int MN = 5e5 + 15, MD = 15, INF = 0x3f3f3f3f3f3f3f3f;

int fail[MN], cnt[MN], ans;
pir nxtp[MD][MN];
string s, t;
vector<pir> pos[MD];
vector<string> vct;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> t;

    bool isstar = true;
    for (auto c : s) {
        if (c != '*') {
            isstar = false;
            break;
        }
    }
    if (isstar) {
        cout << (signed)(t.size() + 1) * (signed)t.size() / 2 << '\n';
        return 0;
    }

    if (s[0] == '*') vct.push_back(""); 

    for (int i = 0, it = 0; i <= s.size(); i++) {
        if (i == s.size() || s[i] == '*') {
            string tmp = s.substr(it, i - it);
            if (!tmp.empty()) vct.push_back(tmp);
            it = i + 1;
        }
    }
    if (s.back() == '*') vct.push_back("");  

    memset(nxtp, 0x3f, sizeof(nxtp));

    for (int i = 0; i < (int)vct.size(); i++) {
        auto &pat = vct[i];
        memset(fail, 0, sizeof(fail));
        for (int j = 1, k = 0; j < (int)pat.size(); j++) {
            while (k && pat[j] != pat[k]) k = fail[k];
            if (pat[j] == pat[k]) k++;
            fail[j + 1] = k;
        }

        if (pat.empty()) pos[i].push_back({0, 0});

        for (int j = 0, k = 0; j < (int)t.size(); j++) {
            while (k && t[j] != pat[k]) k = fail[k];
            if (t[j] == pat[k]) k++;
            if (k == (int)pat.size()) {
                pos[i].push_back({j - k + 1, j + 1});
                k = fail[k];
            }
        }

        for (auto p : pos[i]) nxtp[i][p.first] = p;
        for (int j = (int)t.size() - 1; j >= 0; j--)
            nxtp[i][j] = min(nxtp[i][j], nxtp[i][j + 1]);
    }

    for (auto p : pos[vct.size() - 1]) cnt[p.first]++;
    if (vct.size() > 1) {  
        for (int i = (int)t.size() - 1; i >= 0; i--) cnt[i] += cnt[i + 1];
    }

    for (auto p : pos[0]) {
        for (int k = 1; k < (int)vct.size(); k++) {
            tie(p.first, p.second) = nxtp[k][p.second];  
            if (p.first == INF) break;
        }
        if (p.first != INF) ans += cnt[p.first];
    }

    cout << ans << '\n';
    return 0;
}
