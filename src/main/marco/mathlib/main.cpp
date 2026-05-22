#include <iostream>
#include <chrono>
#include <cstdint>

int main() {

    
long long result = 0;

    auto t0 = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < 10000000000LL; i++) {
        result += i * i;
    }

    auto t1 = std::chrono::high_resolution_clock::now();

    auto ns = std::chrono::duration_cast<
        std::chrono::nanoseconds
    >(t1 - t0);

    std::cout << result << '\n';

    std::cout << ns.count() << "ns\n";
}