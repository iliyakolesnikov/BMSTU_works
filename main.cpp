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
    std::vector<int> numbers = {5, 2, 9, 1, 7};
    std::cout << "Max: " << findMax(numbers) << std::endl;
    return 0;
}
