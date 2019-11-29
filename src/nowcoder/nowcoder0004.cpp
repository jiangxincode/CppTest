/**
 * 扑克牌大小
 * https://www.nowcoder.com/practice/0a92c75f5d6b4db28fcfa3e65e5c9b3f
 * https://www.nowcoder.com/practice/d290db02bacc4c40965ac31d16b1c3eb
 * 描述:  扑克牌游戏大家应该都比较熟悉了，一副牌由54张组成，含3~A、2各4张，小王1张，大王1张。
 * 牌面从小到大用如下字符和字符串表示（其中，小写joker表示小王，大写JOKER表示大王）：
 * 3 4 5 6 7 8 9 10 J Q K A 2 joker JOKER
 * 输入两手牌，两手牌之间用"-"连接，每手牌的每张牌以空格分隔，"-"两边没有空格，如：
 * 4 4 4 4-joker JOKER。
 * 请比较两手牌大小，输出较大的牌，如果不存在比较关系则输出ERROR。
 * 基本规则：
 * （1）输入每手牌可能是个子、对子、顺子（连续5张）、三个、炸弹（四个）和对王中的一种，
 * 不存在其他情况，由输入保证两手牌都是合法的，顺子已经从小到大排列；
 * （2）除了炸弹和对王可以和所有牌比较之外，其他类型的牌只能跟相同类型的存在比较关系
 * （如，对子跟对子比较，三个跟三个比较），不考虑拆牌情况（如：将对子拆分成个子）；
 * （3）大小规则跟大家平时了解的常见规则相同，个子、对子、三个比较牌面大小；
 * 顺子比较最小牌大小；炸弹大于前面所有的牌，炸弹之间比较牌面大小；对王是最大的牌；
 * （4）输入的两手牌不会出现相等的情况。
 * 输入:
 * 输入两手牌，两手牌之间用"-"连接，每手牌的每张牌以空格分隔，"-"两边没有空格，如：
 * 4 4 4 4-joker JOKER。
 * 输出:
 * 输出两手牌中较大的那手，不含连接符，扑克牌顺序不变，仍以空格隔开；
 * 如果不存在比较关系则输出ERROR。
 * 样例输入: 4 4 4 4-joker JOKER
 * 样例输出: joker JOKER
 * 答案提示:
 * （1）除了炸弹和对王之外，其他必须同类型比较。
 * （2）输入已经保证合法性，不用检查输入是否是合法的牌。
 * （3）输入的顺子已经经过从小到大排序，因此不用再排序了。
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void mappingCards(string &src, vector<int> &result);

int compareCards(vector<int> &first, vector<int> &second);

map<string, int> cardMap;

int main() {
    string str_input, str_first, str_second;
    vector<int> vec_first, vec_second;

    /*设置扑克牌的映射表 */
    cardMap["3"] = 3;
    cardMap["4"] = 4;
    cardMap["5"] = 5;
    cardMap["6"] = 6;
    cardMap["7"] = 7;
    cardMap["8"] = 8;
    cardMap["9"] = 9;
    cardMap["10"] = 10;
    cardMap["J"] = 11;
    cardMap["Q"] = 12;
    cardMap["K"] = 13;
    cardMap["A"] = 14;
    cardMap["2"] = 15;
    cardMap["joker"] = 16;
    cardMap["JOKER"] = 17;

    getline(cin, str_input);


    int pos = str_input.find('-');

    str_first = str_input.substr(0, pos);
    str_second = str_input.substr(pos + 1, str_input.size() - pos);


    mappingCards(str_first, vec_first);
    mappingCards(str_second, vec_second);

    int flag = compareCards(vec_first, vec_second);

    if (flag == 1) {
        cout << str_first;
    } else if (flag == 2) {
        cout << str_second;
    } else {
        cout << "ERROR" << endl;
    }
    return 0;
}

void mappingCards(string &src, vector<int> &result) {
    string::size_type beg = 0;
    string::size_type pos = src.find(' ', beg);

    while (pos != string::npos) {
        result.push_back(cardMap[src.substr(beg, pos - beg)]);
        beg = pos + 1;
        pos = src.find(' ', beg);
    }
    result.push_back(cardMap[src.substr(beg, src.size())]);
}

int compareCards(vector<int> &first, vector<int> &second) {
    //求取两副牌的张数
    vector<int>::size_type n1 = first.size();
    vector<int>::size_type n2 = second.size();

    /*注意由于都是直接返回所以不需要break语句 */
    /*由于不考虑异常输入所以判断可以简化 */
    switch (n1) {
        case 1:
            switch (n2) {
                case 1:
                    return (first[0] > second[0]) ? 1 : 2;
                case 2:
                    return (second[0] + second[1] == 16 + 17) ? 2 : 0;
                case 4:
                    return 2;
                default:
                    return 0;
            }
        case 2:
            switch (n2) {
                case 2:
                    return (first[0] > second[0]) ? 1 : 2;
                case 4:
                    return (first[0] + first[1] == 16 + 17) ? 1 : 2;
                default:
                    return 0;
            }
        case 3:
            switch (n2) {
                case 2:
                    return (second[0] + second[1] == 16 + 17) ? 2 : 0;
                case 3:
                    return (first[0] > second[0]) ? 1 : 2;
                case 4:
                    return 2;
                default:
                    return 0;
            }
        case 4:
            switch (n2) {
                case 2:
                    return (second[0] + second[1] == 16 + 17) ? 2 : 1;
                case 4:
                    return (first[0] > second[0]) ? 1 : 2;
                default:
                    return 1;
            }
        case 5:
            switch (n2) {
                case 2:
                    return (second[0] + second[1] == 16 + 17) ? 2 : 0;
                case 4:
                    return 2;
                case 5:
                    return (first[0] > second[0]) ? 1 : 2;
                default:
                    return 0;
            }
        default:
            return 0;
    }
}


