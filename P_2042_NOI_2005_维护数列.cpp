#include <iostream>
#include <cstring>
#include <algorithm>
#define ls t[p].l  // 定义左子节点
#define rs t[p].r  // 定义右子节点
using namespace std;
constexpr int MN = 1e6 + 15;  // 定义最大节点数
template <typename type>
inline void read(type &x)  // 快速读入函数
{
    x = 0;
    bool flag(0);
    char ch = getchar();
    while (!isdigit(ch))  // 跳过非数字字符
        flag = ch == '-', ch = getchar();
    while (isdigit(ch))  // 读取数字
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    flag ? x = -x : 0;  // 处理负数
}
struct fhqtree  // FHQ Treap节点结构
{
    int l, r, dat, val, size;  // 左子节点、右子节点、随机值、节点值、子树大小
    int sum, ml, covnum, mr, msum;  // 区间和、最大前缀和、覆盖值、最大后缀和、最大子段和
    bool rev, iscov;  // 反转标记、覆盖标记
} t[MN];
int n, m, tot, root;  // 序列长度、操作数、节点总数、根节点
int gcstack[MN], top;  // 垃圾回收栈
int newnode(int k)  // 创建新节点
{
    int i = top ? gcstack[top--] : ++tot;  // 从垃圾回收栈中取节点或新建节点
    memset(&t[i], 0, sizeof(t[i]));  // 初始化节点
    t[i].dat = rand();  // 设置随机值
    t[i].sum = t[i].msum = t[i].val = k;  // 初始化节点值、区间和、最大子段和
    t[i].ml = t[i].mr = max(0, k);  // 初始化最大前缀和、最大后缀和
    t[i].size = 1;  // 初始化子树大小
    return i;
}
void gc(int p)  // 垃圾回收函数
{
    if (!p)
        return;
    gcstack[++top] = p;  // 将节点加入垃圾回收栈
    gc(ls);  // 递归回收左子树
    gc(rs);  // 递归回收右子树
}

void doreverse(int p)  // 处理反转操作
{
    if (!t[p].rev)
        return;

    swap(t[p].ml, t[p].mr);  // 交换最大前缀和与最大后缀和
    swap(t[p].l, t[p].r);  // 交换左右子节点

    t[ls].rev ^= 1;  // 传递反转标记到左子节点
    t[rs].rev ^= 1;  // 传递反转标记到右子节点
    t[p].rev = 0;  // 清除当前节点的反转标记
}

void docover(int p)  // 处理覆盖操作
{
    if (!t[p].iscov)
        return;

    int c = t[p].covnum, cs = t[p].size * c;  // 覆盖值和覆盖后的区间和

    t[p].val = c;  // 更新节点值
    t[p].sum = cs;  // 更新区间和
    t[p].msum = max(c, cs);  // 更新最大子段和
    t[p].ml = t[p].mr = max(cs, 0);  // 更新最大前缀和、最大后缀和

    t[ls].iscov = t[rs].iscov = 1;  // 传递覆盖标记到左右子节点
    t[ls].covnum = t[rs].covnum = c;  // 传递覆盖值到左右子节点

    t[p].covnum = t[p].iscov = 0;  // 清除当前节点的覆盖标记
}

void pushup(int p)  // 更新节点信息
{
    t[p].size = t[ls].size + t[rs].size + 1;  // 更新子树大小
    t[p].sum = t[ls].sum + t[p].val + t[rs].sum;  // 更新区间和
    t[p].ml = max({t[ls].ml, t[ls].sum + t[p].val + t[rs].ml, 0});  // 更新最大前缀和
    t[p].mr = max({t[rs].mr, t[rs].sum + t[p].val + t[ls].mr, 0});  // 更新最大后缀和
    t[p].msum = max(t[p].val, t[ls].mr + t[p].val + t[rs].ml);  // 更新最大子段和

    //注意这里必须判断ls，因为0节点所有值为0，在更新最大前缀和最大后缀的时候可以
    if (ls)
    {
        t[p].msum = max(t[p].msum, t[ls].msum);  // 与左子树的最大子段和比较
    }
    if (rs)
    {
        t[p].msum = max(t[p].msum, t[rs].msum);  // 与右子树的最大子段和比较
    }
}

void pushdown(int p)  // 下传懒标记
{
    if (!p)
        return;
    docover(p);  // 处理覆盖标记
    doreverse(p);  // 处理反转标记

    if (ls)
    {
        docover(ls);  // 处理左子节点的覆盖标记
        doreverse(ls);  // 处理左子节点的反转标记
    }
    if (rs)
    {
        docover(rs);  // 处理右子节点的覆盖标记
        doreverse(rs);  // 处理右子节点的反转标记
    }
}

void split(int p, int k, int &x, int &y)  // 分裂操作
{
    if (!p)
    {
        x = y = 0;
        return;
    }
    pushdown(p);  // 下传懒标记
    if (k > t[ls].size)
    {
        x = p;
        k -= t[ls].size + 1;
        split(rs, k, rs, y);  // 递归分裂右子树
    }
    else
    {
        y = p;
        split(ls, k, x, ls);  // 递归分裂左子树
    }
    pushup(p);  // 更新节点信息
}

int merge(int x, int y)  // 合并操作
{
    if (!x || !y)
    {
        return x + y;
    }
    if (t[x].dat < t[y].dat)
    {
        pushdown(x);  // 下传懒标记
        t[x].r = merge(t[x].r, y);  // 递归合并右子树
        pushup(x);  // 更新节点信息
        return x;
    }
    else
    {
        pushdown(y);  // 下传懒标记
        t[y].l = merge(x, t[y].l);  // 递归合并左子树
        pushup(y);  // 更新节点信息
        return y;
    }
}

void getqj(int k, int tott, int &x, int &y, int &z)  // 获取区间
{
    int l = k, r = k + tott - 1;
    split(root, r, x, z);  // 分裂出右区间
    split(x, l - 1, x, y);  // 分裂出目标区间
}

int toinsert[MN];
int build(int l, int r)  // 构建子树
{
    if (l == r)
    {
        return newnode(toinsert[l]);  // 创建叶子节点
    }
    int mid = l + r >> 1;
    return merge(build(l, mid), build(mid + 1, r));  // 递归构建左右子树并合并
}

void plinsert(int k, int tott)  // 插入区间
{
    int x, y, z;
    split(root, k, x, z);  // 分裂出插入位置
    y = build(1, tott);  // 构建新子树
    root = merge(merge(x, y), z);  // 合并子树
}

void del(int k, int tott)  // 删除区间
{
    int x, y, z;
    getqj(k, tott, x, y, z);  // 获取目标区间
    gc(y);  // 垃圾回收
    root = merge(x, z);  // 合并剩余区间
}

void pushback(int k)  // 在末尾插入节点
{
    root = merge(root, newnode(k));
}

int getmsum()  // 获取最大子段和
{
    return t[root].msum;
}

void reverse(int k, int tott)  // 反转区间
{
    int x, y, z;
    getqj(k, tott, x, y, z);  // 获取目标区间
    t[y].rev ^= 1;  // 设置反转标记
    doreverse(y);  // 处理反转
    root = merge(merge(x, y), z);  // 合并区间
}

void cover(int k, int tott, int cv)  // 覆盖区间
{
    int x, y, z;
    getqj(k, tott, x, y, z);  // 获取目标区间
    t[y].iscov = 1;  // 设置覆盖标记
    t[y].covnum = cv;  // 设置覆盖值
    docover(y);  // 处理覆盖
    root = merge(merge(x, y), z);  // 合并区间
}

int getsum(int k, int tott)  // 获取区间和
{
    int x, y, z;
    getqj(k, tott, x, y, z);  // 获取目标区间
    int ans = t[y].sum;  // 获取区间和
    root = merge(merge(x, y), z);  // 合并区间
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m;  // 读入序列长度和操作数
    for (int i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        pushback(tmp);  // 初始化序列
    }
    string op;
    int x, y, z;
    while (m--)  // 处理操作
    {
        cin >> op;
        if (op[0] == 'I')  // 插入操作
        {
            cin >> x >> y;
            for (int i = 1; i <= y; i++)
            {
                cin >> toinsert[i];
            }
            plinsert(x, y);
        }
        if (op[0] == 'D')  // 删除操作
        {
            cin >> x >> y;
            del(x, y);
        }
        if (op[0] == 'R')  // 反转操作
        {
            cin >> x >> y;
            reverse(x, y);
        }
        if (op[0] == 'G')  // 查询区间和
        {
            cin >> x >> y;
            cout << getsum(x, y) << '\n';
        }
        if (op[0] == 'M')  // 覆盖或查询最大子段和
        {
            if (op[2] == 'K')
            {
                cin >> x >> y >> z;
                cover(x, y, z);
            }
            else
            {
                cout << getmsum() << '\n';
            }
        }
    }
    return 0;
}