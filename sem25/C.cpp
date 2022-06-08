#include <iostream>
#include <thread>
#include <vector>

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
bool all_founded;

void work(int n, int start, int end) {
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
}

int main() {
    int start, end, n;
    std::cin >> start >> end >> n;

    primes.resize(n);
    all_founded = false;
    std::thread newthread(work, n, start, end);

    newthread.join();

    if (!all_founded) {
        std::cout << "end\n";
        return 0;
    }

    for (int i : primes) {
        std::cout << i << '\n';
    }

}
