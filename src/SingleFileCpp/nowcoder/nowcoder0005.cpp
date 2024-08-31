/**
 * 配置文件恢复
 * https://www.nowcoder.com/practice/ca6ac6ef9538419abf6f883f7d6f6ee5
 * 描述:  有6条配置命令，它们执行的结果分别是：
 * 命令    执行
 * reset    reset what
 * reset board    board fault
 * board add    where to add
 * board delet    no board at all
 * reboot backplane    impossible
 * backplane abort    install first
 * he he    unkown command
 * 注意：he he不是命令。
 * 为了简化输入，方便用户，以“最短唯一匹配原则”匹配：
 * 1、若只输入一字串，则只匹配一个关键字的命令行。例如
 * 输入：r，根据该规则，匹配命令reset，执行结果为：reset what；
 * 输入：res，根据该规则，匹配命令reset，执行结果为：reset what；
 * 2、若只输入一字串，但本条命令有两个关键字，则匹配失败。例如
 * 输入：reb，可以找到命令reboot backpalne，但是该命令有两个关键词，所有匹配失败，执行结果为：unkown command
 * 3、若输入两字串，则先匹配第一关键字，如果有匹配但不唯一，
 * 继续匹配第二关键字，如果仍不唯一，匹配失败。
 * 例如输入：r b，找到匹配命令reset board，执行结果为：board fault。
 * 4、若输入两字串，则先匹配第一关键字，如果有匹配但不唯一，
 * 继续匹配第二关键字，如果唯一，匹配成功。
 * 例如输入：b a，无法确定是命令board add还是backplane abort，匹配失败。
 * 5、若输入两字串，第一关键字匹配成功，则匹配第二关键字，若无匹配，失败。
 * 例如输入：bo a，确定是命令board add，匹配成功。
 * 6、若匹配失败，打印“unkown command”
 * 输入:
 * 多行字符串，每行字符串一条命令
 * 输出:
 * 执行结果，每条命令输出一行
 * 样例输入:1
 * reset
 * reset board
 * board add
 * board delet
 * reboot backplane
 * backplane abort
 * 样例输出:
 * reset what
 * board fault
 * where to add
 * no board at all
 * impossible
 * install first
 */
#include <iostream>
#include <string>

using namespace std;

bool static isMatch(string pattern, string input) {
    string::size_type min_size = (pattern.size() < input.size()) ? pattern.size() : input.size();
    string::size_type i = 0;

    for (i = 0; i < min_size; i++) {
        if (pattern[i] != input[i]) {
            break;
        }
    }

    if ((i <= pattern.size()) && (i == input.size())) //匹配成功
    {
        return true;
    } else //匹配失败
    {
        return false;
    }
}

int main() {
    string str_input;

    while (getline(cin, str_input)) {
        if (str_input.length() == 0) {
            break;
        }

        string str_key1 = "", str_key2 = "";

        string::size_type pos = str_input.find(" ");

        if (pos != string::npos) {
            str_key1 = str_input.substr(0, pos);
            str_key2 = str_input.substr(pos + 1, str_input.size());
        } else {
            str_key1 = str_input;
        }

        if (str_key2 == "") {
            if (isMatch("reset", str_key1)) {
                cout << "reset what" << endl;
            } else {
                cout << "unkown command" << endl;
            }
        } else if (isMatch("board", str_key2) && (!isMatch("backplane", str_key2))) {
            if (isMatch("reset", str_key1)) {
                cout << "board fault" << endl;
            } else {
                cout << "unkown command" << endl;
            }
        } else if ((isMatch("board", str_key2)) && (isMatch("backplane", str_key2))) {
            if ((isMatch("reset", str_key1)) && (!isMatch("reboot", str_key1))) {
                cout << "board fault" << endl;
            } else if ((!isMatch("reset", str_key1)) && (isMatch("reboot", str_key1))) {
                cout << "impossible" << endl;
            } else {
                cout << "unkown command" << endl;
            }
        } else if ((isMatch("add", str_key2)) && (!isMatch("abort", str_key2))) {
            if (isMatch("board", str_key1)) {
                cout << "where to add" << endl;
            } else {
                cout << "unkown command" << endl;
            }
        } else if ((isMatch("add", str_key2)) && (isMatch("abort", str_key2))) {
            if ((isMatch("board", str_key1)) && (!isMatch("backplane", str_key1))) {
                cout << "where to add" << endl;
            } else if ((!isMatch("board", str_key1)) && (isMatch("backplane", str_key1))) {
                cout << "install first" << endl;
            } else {
                cout << "unkown command" << endl;
            }
        } else if (isMatch("delet", str_key2)) {
            if (isMatch("board", str_key1)) {
                cout << "no board at all" << endl;
            } else {
                cout << "unkown command" << endl;
            }
        } else if (isMatch("backplane", str_key2)) {
            if (isMatch("reboot", str_key1)) {
                cout << "impossible" << endl;
            } else {
                cout << "unkown command" << endl;
            }
        } else if (isMatch("abort", str_key2)) {
            if (isMatch("backplane", str_key1)) {
                cout << "install first" << endl;
            } else {
                cout << "unkown command" << endl;
            }
        } else {
            cout << "unkown command" << endl;
        }
    }

    return 0;
}
