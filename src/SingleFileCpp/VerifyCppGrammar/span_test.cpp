#include <iostream>
#include <ostream>
#include <span>

void init_data(int buffer[], size_t size) {
    std::cout << "size=" << size << std::endl;
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = i;
    }
    buffer[4] = 40;
    //buffer[20] = 20; //越界访问
}

void init_data(std::span<int> buffer) {
    std::cout << "size=" << buffer.size() << std::endl;
    int value = 0;
    for (auto it = buffer.begin(); it != buffer.end(); it++) {
        *it = value++;
    }
    buffer[4] = 10;
    //buffer[20] = 20; //会触发断言(实测也没有触发断言)
}

int main() {
    int data[10];
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        data[i] = 0;
    }
    //使用数组传递参数
    init_data(data, 5);
    //使用span传递参数
    init_data(data);
    return 0;
}
