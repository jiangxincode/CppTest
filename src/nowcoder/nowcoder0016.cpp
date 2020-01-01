/**
 * 识别有效的IP地址和掩码并进行分类统计
 * https://www.nowcoder.com/practice/de538edd6f7e4bc3a5689723a7435682
 * 描述:
 * 请解析IP地址和对应的掩码，进行分类识别。
 * 要求按照A/B/C/D/E类地址归类，不合法的地址和掩码单独归类。
 * 所有的IP地址划分为 A,B,C,D,E五类
 * A类地址1.0.0.0~126.255.255.255;
 * B类地址128.0.0.0~191.255.255.255;
 * C类地址192.0.0.0~223.255.255.255;
 * D类地址224.0.0.0~239.255.255.255;
 * E类地址240.0.0.0~255.255.255.255
 * 私网IP范围是：
 * 10.0.0.0~10.255.255.255
 * 172.16.0.0~172.31.255.255
 * 192.168.0.0~192.168.255.255
 * 子网掩码为前面是连续的1，然后全是0
 * 输入:
 * 多行字符串。每行一个IP地址和掩码，以~隔开。如：
 * 10.70.44.68~255.255.255.0
 * 1.0.0.1~255.0.0.0
 * 192.168.0.2~255.255.255.0
 * 19..0.~255.255.255.0
 * 输出:
 * 统计A、B、C、D、E、错误IP地址或错误掩码、私有IP的个数，之间以空格隔开，根据上面的IP，可以得到：
 * 1.0.0.1~255.0.0.0 ----A类
 * 192.168.0.2~255.255.255.0  ----C类，私有
 * 10.70.44.68~255.254.255.0----错误的掩码
 * 19..0.~255.255.255.0-----错误的IP
 * 可以得到统计数据如下：
 * 1 0 1 0 0 2 1
 * 样例输入:
 * 10.70.44.68~255.254.255.0
 * 1.0.0.1~255.0.0.0
 * 192.168.0.2~255.255.255.0
 * 19..0.~255.255.255.0
 * 样例输出:
 * 1 0 1 0 0 2 1
 * 注意
 * 1. Mask 255.255.255.255 , 0.0.0.0 为非法
 * 2. IP和Mask必须同时正确，才能被分类到A, B, C, D, E以及私有
 * 3. IP和Mask同时错误时，只算一次错误
 * 4. 注意0.*.*.*以及127.*.*.*不属于任何类别
 */

#include <iostream>
#include <cstdio>
#include <regex>

using namespace std;

int main() {
    int A = 0, B = 0, C = 0, D = 0, E = 0, errorip = 0, privateip = 0;
    string input;
    int ip[4];
    int mask[4];

    while (cin >> input) {

        // R"..." is the new literal string syntax. Without it "\" would need to become "\\"
        std::regex re(
                R"(([0-9]{1,3}\.){3}[0-9]{1,3}~([0-9]{1,3}\.){3}[0-9]{1,3})");
        if (!std::regex_match(input, re)) {
            errorip++;
            continue;
        }

        // remove like 01, 001...
        bool invalid = false;
        for (std::size_t i = 0; i < input.size(); i++) {
            if (i != input.size() - 1 && input[i] == 0 && input[i + 1] != 0) {
                invalid = true;
                break;
            }
        }
        if (invalid) {
            errorip++;
            continue;
        }

        sscanf(input.c_str(), "%d.%d.%d.%d~%d.%d.%d.%d", ip, ip + 1, ip + 2, ip + 3, mask, mask + 1, mask + 2,
               mask + 3);
        if (ip[0] > 255 || ip[1] > 255 || ip[2] > 255 || ip[3] > 255 || mask[0] > 255 || mask[1] > 255 ||
            mask[2] > 255 || mask[3] > 255) {
            errorip++;
            continue;
        }
        if (mask[0] == 0 && mask[1] == 0 && mask[2] == 0 && mask[3] == 0) {
            errorip++;
            continue;
        }
        if (mask[0] == 255 && mask[1] == 255 && mask[2] == 255 && mask[3] == 255) {
            errorip++;
            continue;
        }
        char mask_str[32];
        int tmp = mask[3];
        for (int i = 0; i < 8; i++) {
            mask_str[i] = tmp % 2;
            tmp /= 2;
        }
        tmp = mask[2];
        for (int i = 9; i < 16; i++) {
            mask_str[i] = tmp % 2;
            tmp /= 2;
        }
        tmp = mask[1];
        for (int i = 16; i < 24; i++) {
            mask_str[i] = tmp % 2;
            tmp /= 2;
        }
        tmp = mask[0];
        for (int i = 24; i < 32; i++) {
            mask_str[i] = tmp % 2;
            tmp /= 2;
        }
        bool isRightMask = true;
        for (int i = 31; i >= 0; i--) {
            if (mask_str[i] != 1) {
                for (int j = i - 1; j >= 0; j--) {
                    if (mask_str[j] == 1) {
                        isRightMask = false;
                        break;
                    }
                }
                if (!isRightMask) {
                    break;
                }
            }
        }
        if (!isRightMask) {
            errorip++;
            continue;
        }
        if (ip[0] <= 126 && ip[0] != 0) {
            A++;
            if (ip[0] == 10) {
                privateip++;
            }
            continue;
        }

        if (ip[0] <= 191 && ip[0] >= 128) {
            B++;
            if (ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31) {
                privateip++;
            }
            continue;
        }

        if (ip[0] <= 223 && ip[0] > 191) {
            C++;
            if (ip[0] == 192 && ip[1] == 168) {
                privateip++;
            }
            continue;
        }

        if (ip[0] <= 239 && ip[0] >= 224) {
            D++;
            continue;
        }

        if (ip[0] >= 240) {
            E++;
            continue;
        }
    }
    cout << A << " " << B << " " << C << " " << D << " " << E << " " << errorip << " " << privateip << endl;
    return 0;
}
