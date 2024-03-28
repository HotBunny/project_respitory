#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "Enter number many steps: ";
    int n;
    cin >> n;

    vector<int> ways(n + 1, 0);
    ways[0] = 1;

    for (int i = 1; i <= n; i++) {
        ways[i] = ways[i - 1] + ways[i - 2];
    }

    cout << "The number of ways to climb the staircase is: " << ways[n] << endl;
    
    return 0;
}
