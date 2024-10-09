#include <iostream>
#include <ostream>
#include <span>

void init_data(int buffer[], size_t size) {
    std::cout << "size=" << size << std::endl;
    int value = 0;
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = value++;
    }
    buffer[4] = 40;
    buffer[20] = 20; //越界访问
    std::cout << "buffer[4]: " << buffer[4] << "buffer[20]: " << buffer[20] << std::endl;
}

void init_data(std::span<int> buffer) {
    std::cout << "size=" << buffer.size() << std::endl;
    int value = 0;
    for (int & it : buffer) {
        it = value++;
    }
    buffer[4] = 10;
    buffer[20] = 20; //会触发断言(实测也没有触发断言)
    std::cout << "buffer[4]: " << buffer[4] << "buffer[20]: " << buffer[20] << std::endl;
}

int main() {
    int data[10];
    for (int & i : data) {
        i = 0;
    }
    //使用数组传递参数
    init_data(data, 10);
    //使用span传递参数
    init_data(data);
    return 0;
}
