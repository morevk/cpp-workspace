#include <iostream>

template <typename T, int size, typename Callback>
void ForEach(T (&arr)[size], Callback func) {
    for(auto &item : arr) {
        func(item);
    }
}

int test_template_for_each_main() {
    int arr[]{1, 2, 3, 4, 5};

    ForEach(arr, [](int &num) {
        std::cout << num << " ";
    });

    return 0;
}