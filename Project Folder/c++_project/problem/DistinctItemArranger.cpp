#include <iostream>
#include <cmath>

// Function to calculate factorial
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

int main() {
    // Take the total number of items and the number of distinct items as input
    int n, k;
    std::cout << "Enter the total number of items: ";
    std::cin >> n;
    std::cout << "Enter the number of distinct items: ";
    std::cin >> k;

    // Calculate the number of ways to arrange the items
    long long ways = factorial(n) / (factorial(k) * factorial(n - k));

    // Output the number of ways
    std::cout << "The number of ways to arrange the items is: " << ways << std::endl;

    return 0;
}

