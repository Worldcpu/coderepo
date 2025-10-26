/*
    对拍数据生成器 V1.0 By wjyppm1403
    License：GPL-3
*/

#ifndef RANDOM_DATAGEN
#define RANDOM_DATAGEN

#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <utility>
#include <unordered_set>
#include <limits.h>

#if !defined(RANDGEN_ALLOW_OLD_RNG)

#undef random_shuffle
#define random_shuffle(...)                                                                            \
    do                                                                                                 \
    {                                                                                                  \
        static_assert(false,                                                                           \
                      "random_shuffle is DISABLED. Use std::shuffle with a RNG (e.g. randgen::rnd)."); \
    } while (0)

#if defined(__GNUC__) || defined(__clang__)
extern "C" int rand(void) __attribute__((error("rand() is DISABLED. Use randgen::rnd instead.")));
extern "C" void srand(unsigned int) __attribute__((error("srand() is DISABLED. Use randgen::rnd instead.")));
#else
#undef rand
#define rand(...) static_assert(false, "rand() is DISABLED. Use randgen::rnd instead.")
#undef srand
#define srand(...) static_assert(false, "srand() is DISABLED. Use randgen::rnd instead.")
#endif

#endif

namespace Rand
{

    // ===================== rnd 类 =====================
    class rnd
    {
    private:
        struct xorshift64s_state
        {
            uint64_t a;
        } state;

        bool external = false;
        rnd *external_rnd = nullptr;

        inline uint64_t xorshift64s()
        {
            uint64_t x = state.a;
            x ^= x >> 12;
            x ^= x << 25;
            x ^= x >> 27;
            state.a = x;
            return x * UINT64_C(0x2545F4914F6CDD1D);
        }

        inline uint64_t get_raw()
        {
            if (external && external_rnd)
                return external_rnd->get_raw();
            return xorshift64s();
        }

    public:
        // ===== 构造函数 =====

        rnd()
        {
            std::random_device rd;
            uint64_t seed = ((uint64_t)rd() << 32) ^ rd();
            if (seed == 0)
                seed = 0x5f3759dfE1eafULL;
            state.a = seed;
        }

        explicit rnd(uint64_t seed)
        {
            if (seed == 0)
                seed = 0x600D600D600dfaceULL;
            state.a = seed;
        }

        explicit rnd(rnd &other) : external(true), external_rnd(&other) {}

        // ======= 整数 / 浮点随机生成 =======
        int gen(int n)
        {
            return static_cast<int>(get_raw() % (n + 1));
        }

        long long gen(long long n)
        {
            return static_cast<long long>(get_raw() % (n + 1));
        }

        size_t gen(size_t n)
        {
            return static_cast<size_t>(get_raw() % (n + 1));
        }

        int gen(int l, int r)
        {
            if (l > r)
                return -1;
            return l + gen(r - l);
        }

        long long gen(long long l, long long r)
        {
            if (l > r)
                return -1;
            return l + gen(r - l);
        }

        size_t gen(size_t l, size_t r)
        {
            if (l > r)
                return 0;
            return l + gen(r - l);
        }

        double gen(double l, double r)
        {
            if (l > r)
                return -1.0;
            return l + (r - l) * (static_cast<double>(get_raw()) / static_cast<double>(ULLONG_MAX));
        }

        double gen(double n)
        {
            return gen(0.0, n);
        }

        // ======= 从容器随机选一个元素 =======
        template <typename Container>
        auto &any(Container &c)
        {
            static_assert(
                std::is_same<typename std::iterator_traits<typename Container::iterator>::iterator_category, std::random_access_iterator_tag>::value,
                "Container must support random access iterators!");
            size_t idx = gen((size_t)0, c.size() - 1);
            return c[idx];
        }

        // ======= 打乱 =======
        template <typename RandomIt>
        void shuffle(RandomIt first, RandomIt last)
        {
            for (auto i = last - 1; i > first; --i)
            {
                auto j = first + gen((size_t)0, (size_t)(i - first));
                std::swap(*i, *j);
            }
        }
    };

    // ===================== String 类 =====================
    class String
    {
    private:
        bool use_external = false;
        rnd *external_rnd = nullptr;
        rnd internal_rnd;

        rnd &get_rnd()
        {
            return use_external ? *external_rnd : internal_rnd;
        }

    public:
        String() = default;
        explicit String(uint64_t seed) : internal_rnd(seed) {}
        explicit String(rnd &other) : use_external(true), external_rnd(&other) {} // 引用已有 rnd

        // strgen(len) -> 生成固定长度字符串（默认字符集：小写字母）
        std::string strgen(size_t len, const std::string &charset = "abcdefghijklmnopqrstuvwxyz")
        {
            std::string res;
            res.reserve(len);
            auto &r = get_rnd();
            for (size_t i = 0; i < len; ++i)
                res.push_back(r.any(charset));
            return res;
        }

        // strgen(pair(l,r)) -> 生成区间长度字符串
        std::string strgen(std::pair<size_t, size_t> len_range, const std::string &charset = "abcdefghijklmnopqrstuvwxyz")
        {
            auto &r = get_rnd();
            size_t len = r.gen(len_range.first, len_range.second);
            return strgen(len, charset);
        }

        // randomly return one of the string from the args
        template <typename... Args>
        std::string strselect(const Args &...args)
        {
            std::vector<std::string> arr = {args...};
            auto &r = get_rnd();
            size_t idx = r.gen((size_t)0, arr.size() - 1);
            return arr[idx];
        }
    };

    class Graph
    {
    private:
        bool ext = false;
        rnd *er = nullptr;
        rnd ir; // internal rnd if not external

        rnd &r() { return ext ? *er : ir; }

        // helper: undirected key
        static uint64_t key_u(int a, int b)
        {
            if (a > b)
                std::swap(a, b);
            return ((uint64_t)a << 32) | (uint64_t)b;
        }
        // helper: directed key
        static uint64_t key_d(int a, int b)
        {
            return ((uint64_t)a << 32) | (uint64_t)b;
        }

    public:
        Graph() = default;
        explicit Graph(uint64_t seed) : ir(seed) {}
        explicit Graph(rnd &ex) : ext(true), er(&ex) {}

        using E3 = std::vector<std::tuple<int, int, int>>;
        using E2 = std::vector<std::pair<int, int>>;

        E3 ndgraph(int n, int m, bool self_loop = false, bool repeated_edge = false,
                   std::pair<int, int> wl = {1, 1})
        {
            E3 out;
            if (n <= 0)
                return out;
            uint64_t maxEdges = self_loop ? (uint64_t)n * n : (uint64_t)n * (n - 1) / 2;
            if (!repeated_edge)
                m = (int)std::min((uint64_t)m, maxEdges);
            std::unordered_set<uint64_t> S;
            out.reserve(std::min(m, n * n));
            int tries = 0;
            while ((int)out.size() < m && tries < m * 10 + 1000)
            {
                ++tries;
                int u = r().gen(1, n);
                int v = r().gen(1, n);
                if (!self_loop && u == v)
                    continue;
                uint64_t key = key_u(u, v);
                if (!repeated_edge)
                {
                    if (S.find(key) != S.end())
                        continue;
                    S.insert(key);
                }
                int w = r().gen(wl.first, wl.second);
                out.emplace_back(u, v, w);
            }
            return out;
        }

        // ---------- dgraph: directed graph (weights) ----------
        E3 dgraph(int n, int m, bool self_loop = false, bool repeated_edge = false,
                  std::pair<int, int> wl = {1, 1})
        {
            E3 out;
            if (n <= 0)
                return out;
            uint64_t maxEdges = self_loop ? (uint64_t)n * (uint64_t)n : (uint64_t)n * (uint64_t)(n - 1);
            if (!repeated_edge)
                m = (int)std::min((uint64_t)m, maxEdges);
            std::unordered_set<uint64_t> S;
            out.reserve(std::min(m, n * n));
            int tries = 0;
            while ((int)out.size() < m && tries < m * 10 + 1000)
            {
                ++tries;
                int u = r().gen(1, n);
                int v = r().gen(1, n);
                if (!self_loop && u == v)
                    continue;
                uint64_t key = key_d(u, v);
                if (!repeated_edge)
                {
                    if (S.find(key) != S.end())
                        continue;
                    S.insert(key);
                }
                int w = r().gen(wl.first, wl.second);
                out.emplace_back(u, v, w);
            }
            return out;
        }

        // ---------- dag: acyclic directed graph ----------
        E3 dag(int n, int m, bool repeated_edge = false, std::pair<int, int> wl = {1, 1})
        {
            E3 out;
            if (n <= 0)
                return out;
            uint64_t maxE = (uint64_t)n * (uint64_t)(n - 1) / 2;
            if (!repeated_edge)
                m = (int)std::min((uint64_t)m, maxE);
            std::vector<int> ord(n);
            for (int i = 0; i < n; ++i)
                ord[i] = i + 1;
            r().shuffle(ord.begin(), ord.end());
            std::unordered_set<uint64_t> S;
            out.reserve(std::min(m, (int)maxE));
            int tries = 0;
            while ((int)out.size() < m && tries < m * 10 + 1000)
            {
                ++tries;
                int i = r().gen(0, n - 1);
                int j = r().gen(0, n - 1);
                if (i == j)
                    continue;
                if (i > j)
                    std::swap(i, j);
                int u = ord[i];
                int v = ord[j];
                uint64_t key = key_d(u, v);
                if (!repeated_edge)
                {
                    if (S.find(key) != S.end())
                        continue;
                    S.insert(key);
                }
                int w = r().gen(wl.first, wl.second);
                out.emplace_back(u, v, w);
            }
            return out;
        }

        // ---------- tree: unweighted tree ----------
        // p_chain, p_flower are fractions in [0,1]; remaining is random
        E2 tree(int n, double p_chain = 0.4, double p_flower = 0.35)
        {
            E2 out;
            if (n <= 1)
                return out;
            out.reserve(n - 1);
            // center for flower = 1
            int last = 1;
            int center = 1;
            for (int v = 2; v <= n; ++v)
            {
                double x = (double)r().gen(0, 1000) / 1000.0;
                if (x < p_chain)
                {
                    // attach to last -> chain
                    out.emplace_back(last, v);
                    last = v;
                }
                else if (x < p_chain + p_flower)
                {
                    // attach to center -> flower
                    out.emplace_back(center, v);
                }
                else
                {
                    // attach to random existing
                    int u = r().gen(1, v - 1);
                    out.emplace_back(u, v);
                }
            }
            return out;
        }

        E2 chain(int n)
        {
            return tree(n, 1.0, 0.0);
        }

        E2 flower(int n)
        {
            return tree(n, 0.0, 1.0);
        }

        // ---------- bintree: binary tree, probabilistic left/right ----------
        E2 bintree(int n, double p_left = 0.4, double p_right = 0.35)
        {
            E2 out;
            if (n <= 1)
                return out;
            out.reserve(n - 1);
            // keep left/right occupancy
            std::vector<int> left(n + 1, 0), right(n + 1, 0);
            for (int v = 2; v <= n; ++v)
            {
                int tries = 0;
                while (true)
                {
                    ++tries;
                    int p = r().gen(1, v - 1); // parent candidate
                    double x = (double)r().gen(0, 1000) / 1000.0;
                    if (x < p_left)
                    {
                        if (!left[p])
                        {
                            left[p] = v;
                            out.emplace_back(p, v);
                            break;
                        }
                    }
                    else if (x < p_left + p_right)
                    {
                        if (!right[p])
                        {
                            right[p] = v;
                            out.emplace_back(p, v);
                            break;
                        }
                    }
                    else
                    {
                        if (!left[p])
                        {
                            left[p] = v;
                            out.emplace_back(p, v);
                            break;
                        }
                        if (!right[p])
                        {
                            right[p] = v;
                            out.emplace_back(p, v);
                            break;
                        }
                    }
                    if (tries > 50)
                    {
                        int p2 = r().gen(1, v - 1);
                        out.emplace_back(p2, v);
                        break;
                    }
                }
            }
            return out;
        }

        // ---------- wtree: weighted tree ----------
        E3 wtree(int n, std::pair<int, int> wl = {1, 1}, double p_chain = 0.4, double p_flower = 0.35)
        {
            E3 out;
            if (n <= 1)
                return out;
            out.reserve(n - 1);
            int last = 1, center = 1;
            for (int v = 2; v <= n; ++v)
            {
                double x = (double)r().gen(0, 1000) / 1000.0;
                int u;
                if (x < p_chain)
                {
                    u = last;
                    last = v;
                }
                else if (x < p_chain + p_flower)
                {
                    u = center;
                }
                else
                {
                    u = r().gen(1, v - 1);
                }
                int w = r().gen(wl.first, wl.second);
                out.emplace_back(u, v, w);
            }
            return out;
        }

        // ---------- udag: undirected connected (weighted) ----------
        E3 udag(int n, int m, bool self_loop = false, bool repeated_edge = false,
                std::pair<int, int> wl = {1, 1})
        {
            E3 out;
            if (n <= 0)
                return out;
            std::unordered_set<uint64_t> S;
            out.reserve(std::min(m, n * (n - 1) / 2));
            for (int v = 2; v <= n; ++v)
            {
                int u = r().gen(1, v - 1);
                int w = r().gen(wl.first, wl.second);
                out.emplace_back(u, v, w);
                S.insert(key_u(u, v));
            }
            int need = m - (int)out.size();
            uint64_t maxEdges = self_loop ? (uint64_t)n * n : (uint64_t)n * (uint64_t)(n - 1) / 2;
            if (!repeated_edge)
                need = (int)std::min((uint64_t)need, maxEdges - S.size());
            int tries = 0;
            while (need > 0 && tries < need * 20 + 1000)
            {
                ++tries;
                int u = r().gen(1, n);
                int v = r().gen(1, n);
                if (!self_loop && u == v)
                    continue;
                uint64_t key = key_u(u, v);
                if (!repeated_edge)
                {
                    if (S.find(key) != S.end())
                        continue;
                    S.insert(key);
                }
                int w = r().gen(wl.first, wl.second);
                out.emplace_back(u, v, w);
                --need;
            }
            return out;
        }
    };

}

#endif // RANDOM_DATAGEN
