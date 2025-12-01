#include <iostream>
#include <vector>

int findMax(const std::vector<int>& list) {
    int max = list[0];
    for (int i = 1; i < list.size(); i++) {
        if (list[i] > max) {
            max = list[i];
        }
    }
    return max;
}

int main() {
    int n;
    std::cout << "Enter number of elements: ";
    std::cin >> n;
    
    std::vector<int> numbers(n);
    std::cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }
    
    std::cout << "Maximum: " << findMax(numbers) << std::endl;
    return 0;
}

