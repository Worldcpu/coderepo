#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <thread>
#include <random>
#include <functional>
// 汇编级高精度计时器
inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

inline uint64_t get_cycles() {
    return rdtsc();
}

class Timer {
private:
    static double cpu_freq_ghz;
    static bool freq_detected;
    
    static void detect_cpu_frequency() {
        if (freq_detected) return;
        
        auto start_time = std::chrono::high_resolution_clock::now();
        uint64_t start_cycles = rdtsc();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        auto end_time = std::chrono::high_resolution_clock::now();
        uint64_t end_cycles = rdtsc();
        
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        double elapsed_ns = duration.count();
        uint64_t elapsed_cycles = end_cycles - start_cycles;
        
        cpu_freq_ghz = (elapsed_cycles / elapsed_ns);
        freq_detected = true;
        
        std::cout << "检测到CPU频率: " << std::fixed << std::setprecision(2) 
                  << cpu_freq_ghz << " GHz" << std::endl;
    }
    
public:
    static double cycles_to_ms(uint64_t cycles) {
        if (!freq_detected) detect_cpu_frequency();
        return cycles / (cpu_freq_ghz * 1000000.0);
    }
};

double Timer::cpu_freq_ghz = 2.5;
bool Timer::freq_detected = false;

class DataGenerator {
public:
    static void generateTestData(const std::string& filename, int count) {
        std::ofstream file(filename, std::ios::binary);
        file << count << "\n";
        
        std::random_device rd;
        uint32_t seed = rd();
        
        for (int i = 0; i < count; i++) {
            seed = seed * 1103515245 + 12345;
            int val = (int)(seed % 2000000) - 1000000; // 范围: -1000000 到 999999
            file << val;
            if (i < count - 1) file << " ";
            
            if (i % 100 == 99) file << "\n";
        }
        if (count % 100 != 0) file << "\n";
        file.close();
    }
};

namespace MyFastIO1 {
    int in() {
        int k = 0, f = 1;
        char c = getchar_unlocked();
        while (c < '0' || c > '9') {
            if (c == '-') f = -1;
            c = getchar_unlocked();
        }
        while (c >= '0' && c <= '9') k = k * 10 + c - '0', c = getchar_unlocked();
        return k * f;
    }
}

class MMapReader {
public:
    MMapReader() : is_mapped_(false), addr_(nullptr), current_(nullptr), end_(nullptr), size_(0) {
        struct stat st;
        if (fstat(STDIN_FILENO, &st) == -1) {
            fallbackRead();
            return;
        }
        
        size_ = st.st_size;
        if (size_ == 0) {
            fallbackRead();
            return;
        }
        
        addr_ = static_cast<char*>(
            mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0)
        );
        
        if (addr_ == MAP_FAILED) {
            fallbackRead();
            return;
        }
        
        is_mapped_ = true;
        current_ = addr_;
        end_ = addr_ + size_;
    }

    ~MMapReader() {
        if (is_mapped_ && addr_) {
            munmap(addr_, size_);
        }
    }

    int get() {
        if (is_mapped_) {
            if (current_ < end_) {
                return static_cast<unsigned char>(*current_++);
            }
            return EOF;
        } else {
            if (buffer_pos_ < buffer_data_.size()) {
                return static_cast<unsigned char>(buffer_data_[buffer_pos_++]);
            }
            return EOF;
        }
    }

    int readInt() {
        int x = 0, f = 1;
        char ch = get();
        
        while (ch != EOF && (ch < '0' || ch > '9')) {
            if (ch == '-') f = -1;
            ch = get();
        }
        
        while (ch != EOF && ch >= '0' && ch <= '9') {
            x = x * 10 + ch - '0';
            ch = get();
        }
        
        return x * f;
    }

private:
    bool is_mapped_;
    char* addr_;
    char* current_;
    char* end_;
    size_t size_;
    
    std::vector<char> buffer_data_;
    size_t buffer_pos_ = 0;
    
    void fallbackRead() {
        char ch;
        while ((ch = getchar()) != EOF) {
            buffer_data_.push_back(ch);
        }
        buffer_pos_ = 0;
        is_mapped_ = false;
    }
};

namespace StandardFastIO {
    class FastReader {
    private:
        static const int BUFFER_SIZE = 1 << 21; 
        char buffer[BUFFER_SIZE];
        char* ptr;
        char* end_ptr;
        FILE* file;
        bool eof_reached;
        
        void loadBuffer() {
            if (eof_reached) return;
            
            size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
            if (bytes_read == 0) {
                eof_reached = true;
                ptr = end_ptr = buffer;
                return;
            }
            
            ptr = buffer;
            end_ptr = buffer + bytes_read;
        }
        
        inline char getChar() {
            if (ptr >= end_ptr) {
                if (eof_reached) return EOF;
                loadBuffer();
                if (ptr >= end_ptr) return EOF;
            }
            return *ptr++;
        }
        
    public:
        FastReader() : ptr(nullptr), end_ptr(nullptr), file(stdin), eof_reached(false) {
            loadBuffer();
        }
        
        FastReader(FILE* f) : ptr(nullptr), end_ptr(nullptr), file(f), eof_reached(false) {
            loadBuffer();
        }
        
        int readInt() {
            int x = 0, f = 1;
            char ch = getChar();
            
            // 跳过非数字字符
            while (ch != EOF && (ch < '0' || ch > '9')) {
                if (ch == '-') f = -1;
                ch = getChar();
            }
            
            // 读取数字
            while (ch != EOF && ch >= '0' && ch <= '9') {
                x = x * 10 + (ch - '0');
                ch = getChar();
            }
            
            return x * f;
        }
        
        void reset() {
            ptr = end_ptr = buffer;
            eof_reached = false;
            rewind(file);
            loadBuffer();
        }
    };
}

class Benchmark {
private:
    std::vector<int> expected_data;
    int dataSize;
    const int NUM_RUNS = 10;
    
public:
    void prepareData(int size) {
        dataSize = size;
        std::cout << "正在生成 " << size << " 个测试整数..." << std::flush;
        DataGenerator::generateTestData("test_data.txt", size);
        std::cout << " 完成。" << std::endl;
        
        std::ifstream file("test_data.txt");
        int n;
        file >> n;
        expected_data.resize(n);
        for (int i = 0; i < n; i++) {
            file >> expected_data[i];
        }
        file.close();
        std::cout << "已加载预期结果用于验证。" << std::endl;
    }
    
    bool verifyResults(const std::vector<int>& results, const std::string& method) {
        if (results.size() != expected_data.size()) {
            std::cerr << method << ": 大小不匹配，预期 " << expected_data.size() 
                      << "，实际 " << results.size() << std::endl;
            return false;
        }
        
        // 验证前1000个和后1000个元素
        for (int i = 0; i < std::min(1000, (int)expected_data.size()); i++) {
            if (results[i] != expected_data[i]) {
                std::cerr << method << ": 第 " << i << " 个值不匹配，预期 " 
                          << expected_data[i] << "，实际 " << results[i] << std::endl;
                return false;
            }
        }
        
        int start_check = std::max(1000, (int)expected_data.size() - 1000);
        for (int i = start_check; i < (int)expected_data.size(); i++) {
            if (results[i] != expected_data[i]) {
                std::cerr << method << ": 第 " << i << " 个值不匹配，预期 " 
                          << expected_data[i] << "，实际 " << results[i] << std::endl;
                return false;
            }
        }
        return true;
    }
    
    // 为避免缓存影响，添加测试顺序随机化
    std::vector<int> getRandomizedTestOrder() {
        std::vector<int> order = {0, 1, 2, 3, 4, 5}; // 6种测试方法
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(order.begin(), order.end(), g);
        return order;
    }
    
    // 测试优化cin (sync_with_stdio(0) + cin.tie(0))
    double benchmarkOptimizedCin() {
        std::vector<double> times;
        std::cout << "测试优化cin (sync关闭+tie关闭)..." << std::flush;
        
        for (int run = 0; run < NUM_RUNS; run++) {
            if (freopen("test_data.txt", "r", stdin) == nullptr) {
                std::cerr << "无法打开测试文件" << std::endl;
                return -1;
            }
            std::ios_base::sync_with_stdio(0);
            std::cin.tie(0);
            
            std::vector<int> results;
            uint64_t start = get_cycles();
            
            int n;
            std::cin >> n;
            results.resize(n);
            for (int i = 0; i < n; i++) {
                std::cin >> results[i];
            }
            
            uint64_t end = get_cycles();
            times.push_back(Timer::cycles_to_ms(end - start));
            
            if (run == 0 && !verifyResults(results, "优化cin")) {
                std::cerr << "优化cin: 验证失败！" << std::endl;
                return -1;
            }
            std::cout << "." << std::flush;
        }
        
        double avg = std::accumulate(times.begin(), times.end(), 0.0) / NUM_RUNS;
        std::cout << " 完成。" << std::endl;
        return avg;
    }
    
    // 测试普通cin
    double benchmarkNormalCin() {
        std::vector<double> times;
        std::cout << "测试普通cin..." << std::flush;
        
        for (int run = 0; run < NUM_RUNS; run++) {
            if (freopen("test_data.txt", "r", stdin) == nullptr) {
                std::cerr << "无法打开测试文件" << std::endl;
                return -1;
            }
            std::ios_base::sync_with_stdio(true);
            std::cin.tie(&std::cout);
            
            std::vector<int> results;
            uint64_t start = get_cycles();
            
            int n;
            std::cin >> n;
            results.resize(n);
            for (int i = 0; i < n; i++) {
                std::cin >> results[i];
            }
            
            uint64_t end = get_cycles();
            times.push_back(Timer::cycles_to_ms(end - start));
            
            if (run == 0 && !verifyResults(results, "普通cin")) {
                std::cerr << "普通cin: 验证失败！" << std::endl;
                return -1;
            }
            std::cout << "." << std::flush;
        }
        
        double avg = std::accumulate(times.begin(), times.end(), 0.0) / NUM_RUNS;
        std::cout << " 完成。" << std::endl;
        return avg;
    }
    
    // 测试scanf
    double benchmarkScanf() {
        std::vector<double> times;
        std::cout << "测试scanf..." << std::flush;
        
        for (int run = 0; run < NUM_RUNS; run++) {
            if (freopen("test_data.txt", "r", stdin) == nullptr) {
                std::cerr << "无法打开测试文件" << std::endl;
                return -1;
            }
            
            std::vector<int> results;
            uint64_t start = get_cycles();
            
            int n;
            scanf("%d", &n);
            results.resize(n);
            for (int i = 0; i < n; i++) {
                scanf("%d", &results[i]);
            }
            
            uint64_t end = get_cycles();
            times.push_back(Timer::cycles_to_ms(end - start));
            
            if (run == 0 && !verifyResults(results, "scanf")) {
                std::cerr << "scanf: 验证失败！" << std::endl;
                return -1;
            }
            std::cout << "." << std::flush;
        }
        
        double avg = std::accumulate(times.begin(), times.end(), 0.0) / NUM_RUNS;
        std::cout << " 完成。" << std::endl;
        return avg;
    }
    
    double benchmarkStandardFastIO() {
        std::vector<double> times;
        std::cout << "测试标准快读 (fread)..." << std::flush;
        
        for (int run = 0; run < NUM_RUNS; run++) {
            FILE* file = fopen("test_data.txt", "r");
            if (!file) {
                std::cerr << "无法打开测试文件" << std::endl;
                return -1;
            }
            
            std::vector<int> results;
            uint64_t start = get_cycles();
            
            StandardFastIO::FastReader reader(file);
            int n = reader.readInt();
            results.resize(n);
            for (int i = 0; i < n; i++) {
                results[i] = reader.readInt();
            }
            
            uint64_t end = get_cycles();
            times.push_back(Timer::cycles_to_ms(end - start));
            
            fclose(file);
            
            if (run == 0 && !verifyResults(results, "标准快读")) {
                std::cerr << "标准快读: 验证失败！" << std::endl;
                return -1;
            }
            std::cout << "." << std::flush;
        }
        
        double avg = std::accumulate(times.begin(), times.end(), 0.0) / NUM_RUNS;
        std::cout << " 完成。" << std::endl;
        return avg;
    }
    
    double benchmarkMyFastIO1() {
        std::vector<double> times;
        std::cout << "测试 (getchar_unlocked)..." << std::flush;
        
        for (int run = 0; run < NUM_RUNS; run++) {
            if (freopen("test_data.txt", "r", stdin) == nullptr) {
                std::cerr << "无法打开测试文件" << std::endl;
                return -1;
            }
            
            std::vector<int> results;
            uint64_t start = get_cycles();
            
            int n = MyFastIO1::in();
            results.resize(n);
            for (int i = 0; i < n; i++) {
                results[i] = MyFastIO1::in();
            }
            
            uint64_t end = get_cycles();
            times.push_back(Timer::cycles_to_ms(end - start));
            
            if (run == 0 && !verifyResults(results, "快读1")) {
                std::cerr << "快读1: 验证失败！" << std::endl;
                return -1;
            }
            std::cout << "." << std::flush;
        }
        
        double avg = std::accumulate(times.begin(), times.end(), 0.0) / NUM_RUNS;
        std::cout << " 完成。" << std::endl;
        return avg;
    }
    
    double benchmarkMyFastIO2() {
        std::vector<double> times;
        std::cout << "测试 (MMap)..." << std::flush;
        
        for (int run = 0; run < NUM_RUNS; run++) {
            if (freopen("test_data.txt", "r", stdin) == nullptr) {
                std::cerr << "无法打开测试文件" << std::endl;
                return -1;
            }
            
            std::vector<int> results;
            uint64_t start = get_cycles();
            
            MMapReader reader;
            int n = reader.readInt();
            results.resize(n);
            for (int i = 0; i < n; i++) {
                results[i] = reader.readInt();
            }
            
            uint64_t end = get_cycles();
            times.push_back(Timer::cycles_to_ms(end - start));
            
            if (run == 0 && !verifyResults(results, "快读2")) {
                std::cerr << "快读2: 验证失败！" << std::endl;
                return -1;
            }
            std::cout << "." << std::flush;
        }
        
        double avg = std::accumulate(times.begin(), times.end(), 0.0) / NUM_RUNS;
        std::cout << " 完成。" << std::endl;
        return avg;
    }
    
    std::vector<std::pair<std::string, double>> runAllBenchmarks() {
        std::vector<std::pair<std::string, double>> results;
        
        struct TestCase {
            std::string name;
            std::function<double()> func;
        };
        
        std::vector<TestCase> tests = {
            {"优化cin (sync关闭+tie关闭)", [this]() { return benchmarkOptimizedCin(); }},
            {"普通cin", [this]() { return benchmarkNormalCin(); }},
            {"scanf", [this]() { return benchmarkScanf(); }},
            {"标准快读 (修复版fread)", [this]() { return benchmarkStandardFastIO(); }},
            {"快读1 (getchar_unlocked)", [this]() { return benchmarkMyFastIO1(); }},
            {"快读2 (MMap)", [this]() { return benchmarkMyFastIO2(); }}
        };
        
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(tests.begin(), tests.end(), g);
        
        for (auto& test : tests) {
            double time = test.func();
            if (time > 0) {
                results.push_back({test.name, time});
            }
        }
        
        return results;
    }
};

int main() {
    std::cout << "编译参数: g++ -O2 -static -std=c++20" << std::endl;
    std::cout << "测试规模: 10^7 个整数 (10,000,000)" << std::endl;
    std::cout << "每种方法运行次数: 10 次 (取平均值)" << std::endl;
    std::cout << "计时器: 汇编RDTSC + 自动CPU频率检测" << std::endl;
    std::cout << "缓存优化: 随机测试顺序" << std::endl;
    std::cout << std::endl;
    
    const int TEST_SIZE = 10000000; // 1e7
    
    Benchmark bench;
    bench.prepareData(TEST_SIZE);
    
    std::cout << std::endl;
    std::cout << "开始基准测试 (每种方法运行10次，随机顺序):" << std::endl;
    std::cout << "======================================" << std::endl;
    
    auto results = bench.runAllBenchmarks();
    
    // 按性能排序（最快的在前）
    std::sort(results.begin(), results.end(), 
              [](const auto& a, const auto& b) { return a.second < b.second; });
    
    std::cout << std::endl;
    std::cout << "=== 最终结果 (10次运行的平均值) ===" << std::endl;
    std::cout << "排名 | 方法                          | 平均时间 (ms) | 相对最慢的加速比" << std::endl;
    std::cout << "-----|-------------------------------|---------------|------------------" << std::endl;
    
    double slowest_time = results.empty() ? 1.0 : results.back().second;
    
    for (size_t i = 0; i < results.size(); i++) {
        double speedup = slowest_time / results[i].second;
        printf("%4zu | %-29s | %13.3f | %16.2fx\n", 
               i + 1, results[i].first.c_str(), results[i].second, speedup);
    }
    
    std::cout << std::endl;
    std::cout << "=== 性能分析 ===" << std::endl;
    if (!results.empty()) {
        double fastest = results[0].second;
        double slowest = results.back().second;
        printf("最快方法: %s (%.3f ms)\n", results[0].first.c_str(), fastest);
        printf("最慢方法: %s (%.3f ms)\n", results.back().first.c_str(), slowest);
        printf("性能差距: %.2fx\n", slowest / fastest);
        printf("数据吞吐量 (最快方法): %.2f MB/s\n", 
               (TEST_SIZE * 4.0 / 1024.0 / 1024.0) / (fastest / 1000.0));
        
        std::cout << std::endl;
        std::cout << "=== 详细分析 ===" << std::endl;
        for (size_t i = 0; i < results.size(); i++) {
            double throughput = (TEST_SIZE * 4.0 / 1024.0 / 1024.0) / (results[i].second / 1000.0);
            printf("%s: %.3f ms, %.2f MB/s\n", 
                   results[i].first.c_str(), results[i].second, throughput);
        }
    }
    
    std::cout << std::endl;
    std::cout << "测试成功完成！" << std::endl;
    
    return 0;
}
