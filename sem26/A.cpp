#include <iostream>
#include <thread>
#include <string.h>
#include <vector>
#include <future>

bool is_prime(int n) {
    if (n == 1) {
        return false;
    }
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

std::vector<int> primes;

void work(int n, int start, int end, std::promise<bool>& p) {
    bool all_founded = false;
    int counter = 0;
    for (int i = start; i != end; ++i) {
        if (is_prime(i)) {
            primes[counter] = i;
            ++counter;
            if (counter == n) {
                break;
            }
        }
    }
    if (counter == n) {
        all_founded = true;
    }
     p.set_value_at_thread_exit(all_founded);   
}

int main() {
    int start, end, n;
    std::cin >> start >> end >> n;

    primes.resize(n);


    std::promise<bool> p;
    std::future<bool> f = p.get_future();

    std::thread t(work, n, start, end, std::ref(p));

    //auto f = std::async(work, n, start, end);
    bool all_founded = f.get();
    t.join();

   

    //bool all_founded = work(n, start, end);

    if (!all_founded) {
         std::cout << "end\n";
         return 0;
    }

    for (int i : primes) {
        std::cout << i << '\n';
    }

}
