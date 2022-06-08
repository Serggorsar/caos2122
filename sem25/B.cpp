#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <cstdio>

bool is_prime(int n) {
    if (n % 2 == 0) {
        return false;
    }
    for(int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int find_ith_prime(int n) {
    int prime_no = 1;
    int prime = 2;
    for (int i = 3; prime_no < n; ++i) {
        if (is_prime(i)) {
            ++prime_no;
            prime = i;
        }
    }
    return prime;
}

void work() {
    int n;
    while (scanf("%d", &n) == 1) {
        int prime = find_ith_prime(n);
        printf("%d\n", prime);
    }   
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong args\n";
        return 1;
    }
    int N = std::stoi(argv[1]);
    std::vector<std::thread> threads(N);
    for (auto &thread: threads) {
        thread = std::thread(work);
    }

    for (auto &thread: threads) {
        thread.join();
    }
    return 0;
}