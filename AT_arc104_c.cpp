// LUOGU_RID: 154777407
#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN=2e2+10;
int a[MAXN], b[MAXN], tot, n;

int rp[MAXN], lp[MAXN];
int dd[MAXN];

int len[MAXN];
void dfs(int step) {
    if (step>2*n) {
        cout<<"Yes\n";
        exit(0);
    }
    if (lp[step] || rp[step]) return dfs(step+1);
    if (dd[step]!=1) {
        // [step, ?]
        auto check=[](int l, int r) {
            for (int i=l; i<=r; ++i) if (len[i]&&len[i]!=r-l+1) return 0;
            return 1;
        };
        for (int i=step+1; i<=2*n; ++i) {
            if (lp[i] || rp[i]) continue;
            if (!check(step,i)) continue;
            if (dd[i]==-1 || (dd[i]==1&&dd[step])) continue;

            vector<int> pos;
            for (int k=step; k<=i; ++k) if (!len[k]) pos.push_back(k), len[k]=i-step+1;

            rp[step]=i; lp[i]=step;
            dfs(step+1);
            for (auto k: pos) len[k]=0;

            rp[step]=lp[i]=0;
        }
    }
}

#define No() cout<<"No", exit(0)

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n;
    set<int> exists;
    for (int i=1,l,r; i<=n; ++i) {
        cin>>l>>r;
        if (l==-1 || r==-1) {
            if (l!=-1) {
                if (exists.count(l)) No();
                dd[l]=-1; exists.insert(l);
            }
            if (r!=-1) {
                if (exists.count(r)) No();
                dd[r]=1; exists.insert(r);
            }
            continue;
        }
        dd[l]=-1; dd[r]=1;
        rp[l]=r; lp[r]=l;
        if (exists.count(l) || exists.count(r) || r<=l) No();
        exists.insert(l); exists.insert(r);
        a[++tot]=l; b[tot]=r;
    }
    for (int i=1; i<=tot; ++i) {
        for (int j=i+1; j<=tot; ++j) {
            int l=max(a[i],a[j]), r=min(b[i],b[j]);
            if (l<=r && b[j]-a[j]!=b[i]-a[i]) return cout<<"No\n", 0;
        }
    }
    for (int i=1; i<=tot; ++i) 
        for (int j=a[i]; j<=b[i]; ++j)
            len[j]=b[i]-a[i]+1;
    dfs(1);
    cout<<"No\n";
}