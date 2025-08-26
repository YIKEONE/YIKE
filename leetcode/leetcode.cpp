#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <string>
#include <functional>
#include <set>
#include <iterator>
#include <cstddef>
#include <unordered_set>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <random>
#include <sys/epoll.h>
/*
    已知的解体思路
    1. 快慢指针
    2. 双指针
    3. 
*/

/*  13. 罗马数字转整数
    罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

    字符          数值
    I             1
    V             5
    X             10
    L             50
    C             100
    D             500
    M             1000

    例如， 罗马数字 2 写做 II ，即为两个并列的 1 。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

    通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。
    数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

        I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
        X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
        C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。

    给定一个罗马数字，将其转换成整数。

    tips: 字符串str拆解为多个单字符, 若str[i] < str[i + 1], 则str[i]的值则取反为-str[i], 反之则为str[i]
*/
class Solution13 {
public:
    int RomanToInt(const std::string& str) {
        int ans = 0;
        for (int i = 0; i < str.size(); ++i) {
            auto value = symbolValues[str[i]];
            if ((i < str.size() - 1) && value < symbolValues[str[i + 1]]) {
                ans -= value;
                continue;
            }
            ans += value;
        }
        return ans;
    }
private:
    std::unordered_map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };
};

/*
27. 移除元素
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素。元素的顺序可能发生改变。然后返回 nums 中与 val 不同的元素的数量。

假设 nums 中不等于 val 的元素数量为 k，要通过此题，您需要执行以下操作：
    更改 nums 数组，使 nums 的前 k 个元素包含不等于 val 的元素。nums 的其余元素和 nums 的大小并不重要。
    返回 k。

    tips: 删除nums中为val的元素, 并且返回nums中不为val的个数
*/
class Solution27 {
public:
    int removeElement(std::vector<int>& nums, int val) {
        return -1;
    }
};

/*
88. 合并两个有序数组
给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。

请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。

示例 1：

输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
*/
class Solution88 {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        if (nums2.empty()) {
            return;
        }

        int p1 = m - 1, p2 = n - 1, p = m + n -1;
        while (p1 >= 0 && p2 >= 0) {
            auto val = (nums1[p1] >= nums2[p2]) ? nums1[p1--] : nums2[p2--];
            nums1[p--] = val;
        }
        while (p2 >= 0) {
            nums1[p--] = nums2[p2--];
        }
    }
};

/*
80. 删除有序数组中的重复项 II
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
*/
class Solution80 {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        int slow = 2, fast = 2;
        while (fast < nums.size()) {
            if (nums[slow - 2] != nums[fast]) {
                nums[slow++] = nums[fast];
            }
            fast++;
        }
        return slow;
    }
};

/*
169. 多数元素
给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。
*/
class Solution169 {
public:
    int majorityElement(std::vector<int>& nums) {
        // std::unordered_map<int, int> map;
        // int res = 0, cnt = 0;
        // for (auto &num: nums) {
        //     ++map[num];
        //     if (map[num] > cnt) {
        //         res = num;
        //         cnt = map[num];
        //     }
        // }
        // return res;

        // 摩尔计数
        int res = 0, votes = 0;
        for (auto &num : nums) {
            if (votes == 0) {
                res = num;
            }
            votes += num == res ? 1 : -1;
        }
        return res;
    }
};

/*
189. 轮转数组
给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
*/
class Solution189 {
public:
    void rotate(std::vector<int>& nums, int k) {
        auto len = nums.size();
        k %= len;
        auto cnt = len - k;
        if (len == 1 || (k == 0)) {
            return;
        }
        for (int i = 0; i < cnt; ++i) {
            nums.emplace_back(nums[i]);
        }
        nums.erase(nums.begin(), nums.begin() + cnt);
    }
};

/*
14. 最长公共前缀
编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""。
*/
class Solution14 {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        auto s0 = strs[0];
        std::string res = "";
        for (int i = 0; i < s0.size(); ++i) {
            for (int j = 1; j < strs.size(); ++j) {
                if (strs[j][i] != s0[i]) {
                    return res;
                }
            }
            res += s0[i];
        }
        return res;
    }
};

/*
151. 反转字符串中的单词
给你一个字符串 s ，请你反转字符串中 单词 的顺序。

单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。

返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。

注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

输入：s = "  hello world  "
输出："world hello"
解释：反转后的字符串中不能存在前导空格和尾随空格。
*/
class Solution151 {
public:
    std::string reverseWords(std::string s) {
        std::string res = "";
        std::string word = "";
        for (auto &chr : s) {
            if (chr != ' ') {
                word += chr;
                continue;
            }
            if (!word.empty()) {
                word += ' ';
                res.insert(0, word);
                word.clear();
            }
        }
        if (!word.empty()) {
            word += ' ';
            res.insert(0, word);
        }
        res.pop_back();
        return res;
    }
};

/*
121. 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
*/
class Solution121 {
public:
    int maxProfit(std::vector<int>& prices) {
        int min = prices[0];
        int max = 0;
        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] < min) {
                min = prices[i];
            } else if (prices[i] - min > max) {
                max = prices[i] - min;
            }
        }
        return max;
    }
};


/*
122. 买卖股票的最佳时机 II
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。
*/
class Solution122 {
public:
    int maxProfit(std::vector<int>& prices) {
        int ans = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] - prices[i - 1] > 0) {
                ans += prices[i] - prices[i - 1];
            }
        }
        return ans;
    }
};

// rookie
/*
125. 验证回文串
如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 回文串 。

字母和数字都属于字母数字字符。

给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。
tips: ctype头文件中有函数 isalnum()判断字符是否为字母或数字, tolower将大写字符转成对应小写的字符的ASCII码, 或者手搓这两个函数
*/
class Solution125 {
public:
    bool isAlpha(char chr) {
        auto ascii = static_cast<int>(chr);
        // 大写、 小写和数字的ASCII码
        return (ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122) || (ascii >= 48 && ascii <= 57);
    }

    char toLower(char chr) {
        if (chr >= 'A' && chr <= 'Z') {
            return chr + 32;
        }
        return chr;
    }

    bool isPalindrome(std::string s) {
        int head = 0, tail = s.size() - 1;
        while (head < tail) {
            if (!isAlpha(s[head])) {
                ++head;
                continue;
            }
            if (!isAlpha(s[tail])) {
                --tail;
                continue;
            }
            if (toLower(s[head]) != toLower(s[tail])) {
                return false;
            }
            ++head;
            --tail;
        }
        return true;
    }
};

/*
392. 判断子序列
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

进阶：

如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

示例 1：

输入：s = "abc", t = "ahbgdc"
输出：true

示例 2：

输入：s = "axc", t = "ahbgdc"
输出：false
*/
class Solution392 {
public:
    bool isSubsequence(std::string s, std::string t) {
        auto sLen = s.size();
        auto tLen = t.size();
        if (sLen == 0) {
            return true;
        } else if (sLen > tLen) {
            return false;
        }
        int p1 = 0, p2 = 0;
        while (p2 < tLen) {
            if (s[p1] == t[p2]) {
                ++p1;
                ++p2;
            } else {
                ++p2;
            }
            if (p1 == sLen) {
                return true;
            }
        }
        return p1 == sLen;
    }
};

/*
难!!!
15. 三数之和 
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
*/
class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        int len = nums.size();
        if (len < 3) {
            return {};
        } else if (len == 3) {
            auto sum = 0;
            for (auto &num : nums) {
                sum += num;
            }
            if (sum == 0) {
                return { { nums[0], nums[1], nums[2] } };
            }
            return {};
        }

        std::vector<std::vector<int>> ans = {};
        std::sort(nums.begin(), nums.end());
        for (int first = 0; first < len; ++first) {
            // 不能和上一个重复
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            int third = len - 1;
            int target = -nums[first];
            for (int second = first + 1; second < len; ++second) {
                // 不能和上一个重复
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // c 要在b的右侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({ nums[first], nums[second], nums[third] });
                }
            }
        }
        return ans;
    }
};

// rookie
/*
167. 两数之和 II - 输入有序数组
给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列  ，请你从数组中找出满足相加之和等于目标数 target 的两个数。如果设这两个数分别是 numbers[index1] 和 numbers[index2] ，则 1 <= index1 < index2 <= numbers.length 。

以长度为 2 的整数数组 [index1, index2] 的形式返回这两个整数的下标 index1 和 index2。

你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。

你所设计的解决方案必须只使用常量级的额外空间。

示例 1：

输入：numbers = [2,7,11,15], target = 9
输出：[1,2]
解释：2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。

示例 2：

输入：numbers = [2,3,4], target = 6
输出：[1,3]
解释：2 与 4 之和等于目标数 6 。因此 index1 = 1, index2 = 3 。返回 [1, 3] 。

示例 3：

输入：numbers = [-1,0], target = -1
输出：[1,2]
解释：-1 与 0 之和等于目标数 -1 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。
*/
class Solution167 {
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        int head = 0, tail = numbers.size() - 1;
        while (head < tail) {
            int sum = numbers[head] + numbers[tail];
            if (sum == target) {
                return { head + 1, tail + 1 };
            }
            sum > target ? --tail : ++ head;
        }
        return { -1, -1 };
    }
};

/*
11. 盛最多水的容器
给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

说明：你不能倾斜容器。
*/
class Solution11 {
public:
    int maxArea(std::vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxArea = 0;
        while (left < right) {
            int h = std::min(height[left], height[right]);
            maxArea = h * (right - left) > maxArea ? h * (right - left) : maxArea;
            height[left] > height[right] ? --right : ++left;
        }
        return maxArea;
    }
};

// rookie
/*
383. 赎金信
给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。

如果可以，返回 true ；否则返回 false 。

magazine 中的每个字符只能在 ransomNote 中使用一次。
*/
class Solution383 {
public:
    bool canConstruct(std::string ransomNote, std::string magazine) {
        std::unordered_map<int, int> hashMap;
        for (const auto &chr : magazine) {
            ++hashMap[chr];
        }
        for (const auto &chr : ransomNote) {
            --hashMap[chr];
            if (hashMap[chr] < 0) {
                return false;
            }
        }
        return true;
    }
};

/*
解法有点没有想到...
205. 同构字符串
给定两个字符串 s 和 t ，判断它们是否是同构的。

如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。

每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。
示例 1:

输入：s = "egg", t = "add"
输出：true
*/
class Solution205 {
public:
    bool isIsomorphic(std::string s, std::string t) {
        if (s.size() != t.size()) {
            return false;
        }
        std::unordered_map<char, char> s_to_t;
        std::unordered_map<char, char> t_to_s;
        for (int i = 0; i < s.size(); ++i) {
            if (s_to_t.count(s[i]) && s_to_t[s[i]] != t[i]) {
                return false;
            }
            if (t_to_s.count(t[i]) && t_to_s[t[i]] != s[i]) {
                return false;
            }
            s_to_t[s[i]] = t[i];
            t_to_s[t[i]] = s[i];
        }
        return true;
    }
};

/*
290. 单词规律
给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s 中的每个非空单词之间存在着双向连接的对应规律。
*/
class Solution290 {
public:
    void GetWords(std::vector<std::string> &words, const std::string &s) {
        std::istringstream iss(s);
        std::string word;
        while (iss >> word) {
            words.emplace_back(word);
        }
    }

    bool wordPattern(std::string pattern, std::string s) {
        std::vector<std::string> words;
        GetWords(words, s);
        if (words.size() != pattern.size()) {
            return false;
        }

        std::unordered_map<char, std::string> p2s;
        std::unordered_map<std::string, char> s2p;
        for (int i = 0; i < pattern.size(); ++i) {
            if (p2s.count(pattern[i]) && p2s[pattern[i]] != words[i]) {
                return false;
            }
            if (s2p.count(words[i]) && s2p[words[i]] != pattern[i]) {
                return false;
            }
            p2s[pattern[i]] = words[i];
            s2p[words[i]] = pattern[i];
        }
        return true;
    }
};

/*
1. 两数之和
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

你可以按任意顺序返回答案。
*/
class Solution1 {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            auto num = target - nums[i];
            if (map.count(num)) {
                return { i, map[num] };
            }
            map[nums[i]] = i;
        }
        return {};
    }
};

/*
    判断a与b中[a, b], 数 x 是回文(对称)且 x 中包含至少一个6, 求 [a, b]中 x 的个数
*/
class Solution12345 {
public:
    bool isPalindromeAndContainSix(long long num) {
        auto str = std::to_string(num);
        int left = 0, right = str.size() - 1;
        bool flag = false;
        while (left <= right) {
            if (str[left] != str[right]) {
                return false;
            } else {
                if (!flag) {
                    flag = str[left] == '6' ? true : false;
                }
            }
            ++left;
            --right;
        }
        if (flag) {
            std::cout << num << std::endl;
        }
        return flag;
    }

    int isPalindromicNumberCount(long long a, long long b) {
        int ans = 0;
        while (a <= b) {
            ans += isPalindromeAndContainSix(a) ? 1 : 0;
            ++a;
        }
        return ans;
    }
};

/*
242. 有效的字母异位词
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的

示例 1:
输入: s = "anagram", t = "nagaram"
输出: true

示例 2:
输入: s = "rat", t = "car"
输出: false
*/
class Solution242 {
public:
    bool isAnagram(std::string s, std::string t) {
        // std::sort(s.begin(), s.end());
        // std::sort(t.begin(), t.end());
        // return s == t;

        if (t.size() != s.size()) {
            return false;
        }
        std::unordered_map<char, int> map;
        for (const auto &element : s) {
            ++map[element];
        }
        for (const auto &element : t) {
            if (map[element]-- == 0) {
                return false;
            }
        }
        return true;
    }
};

/*
55. 跳跃游戏
给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。

示例 1：

输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。

可以用贪心来算, 算max step, 计算标准 max: i + nums[i], 
*/
class Solution55 {
public:
    // int maxStepIndex(int index, const std::vector<int>& nums) {
    //     int steps = nums[index];
    //     if (index + steps >= nums.size() - 1) {
    //         return nums.size() - 1;
    //     }

    //     int ans = index;
    //     int max = index + nums[index];
    //     for (int i = index + 1; i <= index + steps; ++i) {
    //         if (i + nums[i] > max) {
    //             max = i + nums[i];
    //             ans = i;
    //         }
    //     }
    //     return ans;
    // }

    // bool canJump(std::vector<int>& nums) {
    //     auto last_index = maxStepIndex(0, nums);
    //     while (true) {
    //         auto cur_index = maxStepIndex(last_index, nums);
    //         if (cur_index >= nums.size() - 1) {
    //             return true;
    //         } else if (cur_index == last_index) {
    //             return false;
    //         }
    //         last_index = cur_index;
    //     }
    // }

    // recursion
    bool maxStepIndex(int index, const std::vector<int>& nums) {
        int steps = nums[index];
        if (index + steps >= nums.size() - 1) {
            return true;
        }

        int ans = index;
        int max = index + nums[index];
        for (int i = index + 1; i <= index + steps; ++i) {
            if (i + nums[i] > max) {
                max = i + nums[i];
                ans = i;
            }
        }
        if (ans == index) {
            return false;
        }
        return maxStepIndex(ans, nums);
    }

    bool canJump(std::vector<int>& nums) {
        return maxStepIndex(0, nums);
    }
};

/*
45. 跳跃游戏 II
给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。

每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：

0 <= j <= nums[i] 且
i + j < n
返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1。
*/
class Solution45 {
public:
    bool maxStepIndex(int index, int& res, const std::vector<int>& nums) {
        int steps = nums[index];
        if (index + steps >= nums.size() - 1) {
            return true;
        }
        int ans = index;
        int max = index + nums[index];
        for (int i = index + 1; i <= index + steps; ++i) {
            if (i + nums[i] > max) {
                max = i + nums[i];
                ans = i;
            }
        }
        ++res;
        if (ans == index) {
            return false;
        }
        return maxStepIndex(ans, res, nums);
    }

    int jump(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        int ans = 1;
        maxStepIndex(0, ans, nums);
        return ans;
    }
};

/*
274. H 指数
给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。
根据维基百科上 h 指数的定义：h 代表“高引用次数” ，一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，并且 至少 有 h 篇论文被引用次数大于等于 h 。如果 h 有多种可能的值，h 指数 是其中最大的那个。

示例 1：
输入：citations = [3,0,6,1,5]
输出：3 
解释：给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
由于研究者有 3 篇论文每篇 至少 被引用了 3 次，其余两篇论文每篇被引用 不多于 3 次，所以她的 h 指数是 3。

标准: 排序(1 to n), len - i <= [i] len -i 为答案
    len - i 表示篇数
    当 len - i > [i] i后移， 表示[i]不符合len - i的指数, 因为是小到大排序, 当i符合标准, i之后的也肯定符合
*/
class Solution274 {
public:
    int hIndex(std::vector<int>& citations) {
        std::sort(citations.begin(), citations.end());
        int len = citations.size();
        for (int i = 0; i < len; ++i) {
            if (len - i <= citations[i]) {
                return len - i;
            }
        }
        return 0;
    }
};

/*
380. O(1) 时间插入、删除和获取随机元素

实现RandomizedSet 类：
RandomizedSet() 初始化 RandomizedSet 对象
bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。
*/
class RandomizedSet {
public:
    RandomizedSet() {}
    
    bool insert(int val) {
        if (iSet_.count(val)) {
            return false;
        }
        iSet_.emplace(val);
        return true;
    }
    
    bool remove(int val) {
        if (iSet_.count(val)) {
            iSet_.erase(val);
            return true;
        }
        return false;
    }
    
    int getRandom() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, iSet_.size() - 1);
        auto it = iSet_.begin();
        std::advance(it, dis(gen));
        return *it;
    }
private:
    std::unordered_set<int> iSet_;
};

/*
238. 除自身以外数组的乘积

给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。
题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

示例 1:
输入: nums = [1,2,3,4]
输出: [24,12,8,6]

有点难, 累乘的思想, suffix mul and perfix mul
*/
class Solution238 {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        std::vector<int> ans(nums.size(), 1);
        auto len = nums.size();
        for (int i = 1; i < len; ++i) {
            ans[i] = nums[i - 1] * ans[i - 1];
        }

        int tmp = 1;
        for (int i = len - 2; i >= 0; --i) {
            tmp *= nums[i + 1];
            ans[i] = ans[i] * tmp;
        }
        return ans;
    }
};

/*
垃圾题！！！
68. 文本左右对齐
给定一个单词数组 words 和一个长度 maxWidth ，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。
你应该使用 “贪心算法” 来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。
要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。
文本的最后一行应为左对齐，且单词之间不插入额外的空格。

注意:
单词是指由非空格字符组成的字符序列。
每个单词的长度大于 0，小于等于 maxWidth。
输入单词数组 words 至少包含一个单词。

示例 1:
输入: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
输出:
[
    "This    is    an",
    "example  of text",
    "justification.  "
]
*/
class Solution68 {
public:
    std::vector<std::string> fullJustify(std::vector<std::string>& words, int maxWidth) {
        return { };
    }
};

/*
28. 找出字符串中第一个匹配项的下标
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。

示例 1：
输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。
*/
class Solution28 {
public:
    int strStr(std::string haystack, std::string needle) {
        int m = haystack.size(), n = needle.size();
        for (int i = 0; i <= m -n; ++i) {
            if (haystack.substr(i, needle.size()) == needle) {
                return i;
            }
        }
        return -1;
    }
};

/*
58. 最后一个单词的长度
给你一个字符串 s，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中 最后一个 单词的长度。

单词 是指仅由字母组成、不包含任何空格字符的最大子字符串。
*/
class Solution58 {
public:
    int lengthOfLastWord(std::string s) {
        int ans = 0;
        int i;
        std::cout << s.size() << std::endl;
        for (i = s.size() - 1; i >= 0; --i) {
            if (s[i] != ' ') {
                break;
            }
        }
        std::cout << i << std::endl;
        for (int j = i; j >= 0; --j) {
            if (s[j] == ' ') {
                break;
            }
            ++ans;
        }
        return ans;
    }
};

/*
12. 整数转罗马数字
七个不同的符号代表罗马数字，其值如下：
符号	值
I	1
V	5
X	10
L	50
C	100
D	500
M	1000
罗马数字是通过添加从最高到最低的小数位值的转换而形成的。将小数位值转换为罗马数字有以下规则：

如果该值不是以 4 或 9 开头，请选择可以从输入中减去的最大值的符号，将该符号附加到结果，减去其值，然后将其余部分转换为罗马数字。
如果该值以 4 或 9 开头，使用 减法形式，表示从以下符号中减去一个符号，例如 4 是 5 (V) 减 1 (I): IV ，9 是 10 (X) 减 1 (I)：IX。仅使用以下减法形式：4 (IV)，9 (IX)，40 (XL)，90 (XC)，400 (CD) 和 900 (CM)。
只有 10 的次方（I, X, C, M）最多可以连续附加 3 次以代表 10 的倍数。你不能多次附加 5 (V)，50 (L) 或 500 (D)。如果需要将符号附加4次，请使用 减法形式。
给定一个整数，将其转换为罗马数字。

示例 1：
输入：num = 3749
输出： "MMMDCCXLIX"

解释：
3000 = MMM 由于 1000 (M) + 1000 (M) + 1000 (M)
 700 = DCC 由于 500 (D) + 100 (C) + 100 (C)
  40 = XL 由于 50 (L) 减 10 (X)
   9 = IX 由于 10 (X) 减 1 (I)
注意：49 不是 50 (L) 减 1 (I) 因为转换是基于小数位
*/
class Solution12 {
public:
    std::string intToRoman(int num) {
        std::string ans;
        for (const auto &[digit, roman] : valueSymbols) {
            while (num >= digit) {
                num -= digit;
                ans += roman;
            }
            if (num == 0) {
                break;
            }
        }
        return ans;
    }
private:
    std::vector<std::pair<int, std::string>> valueSymbols = {
        {1000, "M"},
        {900,  "CM"},
        {500,  "D"},
        {400,  "CD"},
        {100,  "C"},
        {90,   "XC"},
        {50,   "L"},
        {40,   "XL"},
        {10,   "X"},
        {9,    "IX"},
        {5,    "V"},
        {4,    "IV"},
        {1,    "I"},
    };
};

/*
202. 快乐数
编写一个算法来判断一个数 n 是不是快乐数。
「快乐数」 定义为：

对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
如果这个过程 结果为 1，那么这个数就是快乐数。
如果 n 是 快乐数 就返回 true ；不是，则返回 false 。

示例 1：

输入：n = 19
输出：true
解释：
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
示例 2：

输入：n = 2
输出：false

快慢指针，当循环的时候，slow和fast会重合
*/
class Solution202 {
public:
    int cal(int n) {
        int ans = 0;
        while (n > 0) {
            int digit = n % 10;
            ans += std::pow(digit, 2);
            n /= 10;
        }
        return ans;
    }

    bool isHappy(int n) {
        int slow = n, fast = n;
        do {
            slow = cal(slow);
            fast = cal(fast);
            fast = cal(fast);
        } while (slow != fast);
        return slow == 1;
    }
};

/*
219. 存在重复元素 II
给你一个整数数组 nums 和一个整数 k ，判断数组中是否存在两个 不同的索引 i 和 j ，满足 nums[i] == nums[j] 且 abs(i - j) <= k 。如果存在，返回 true ；否则，返回 false 。

示例 1：

输入：nums = [1,2,3,1], k = 3
输出：true
示例 2：

输入：nums = [1,0,1,1], k = 1
输出：true
示例 3：

输入：nums = [1,2,3,1,2,3], k = 2
输出：false
*/
class Solution219 {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
        // k is num, v is min last index
        std::unordered_map<int, int> map;
        auto len = nums.size();
        for (int i = 0; i < len; ++i) {
            if (map.count(nums[i])) {
                if (i - map[nums[i]] <= k) {
                    return true;
                }
            }
            map[nums[i]] = i;
        }
        return false;
    }
};

/*
128. 最长连续序列
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
*/
class Solution128 {
public:
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_set<int> iSet(nums.begin(), nums.end());
        int ans = 0;
        for (const auto &element : iSet) {
            if (iSet.count(element - 1)) {
                continue;
            }
            auto tmp = element + 1;
            while (iSet.count(tmp)) {
                ++tmp;
            }
            ans = std::max(tmp - element, ans);
            if (ans * 2 >= nums.size()) {
                break;
            }
        }
        return ans;
    }
};

/*
136. 只出现一次的数字
给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。

示例 1 ：
输入：nums = [2,2,1]
输出：1

示例 2 ：
输入：nums = [4,1,2,1,2]
输出：4
*/
class Solution136 {
public:
    int singleNumber(std::vector<int>& nums) {
        int ans = 0;
        for (auto &element : nums) {
            ans ^= element;
        }
        return ans;
    }
};

/*
9. 回文数
给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。

回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

例如，121 是回文，而 123 不是。
*/
class Solution9 {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        auto str = std::to_string(x);
        int head = 0, tail = str.size() - 1;
        if (head == tail) {
            return true;
        }
        while (head < tail) {
            if (str[head] != str[tail]) {
                return false;
            }
            ++head;
            --tail;
        }
        return true;
    }
};

/*
66. 加一
给定一个表示 大整数 的整数数组 digits，其中 digits[i] 是整数的第 i 位数字。这些数字按从左到右，从最高位到最低位排列。这个大整数不包含任何前导 0。

将大整数加 1，并返回结果的数字数组。
这是简单题？？？
*/
class Solution66 {
public:
    std::vector<int> plusOne(std::vector<int>& digits) {
        for (int i = digits.size() - 1; i >= 0; --i) {
            digits[i] = (digits[i] + 1) % 10;
            if (digits[i] != 0) {
                return digits;
            }
        }
        digits = std::vector<int>(digits.size() + 1, 0);
        digits[0] = 1;
        return digits;
    }
};

/*
172. 阶乘后的零
给定一个整数 n ，返回 n! 结果中尾随零的数量。
示例 1：

输入：n = 3
输出：0
解释：3! = 6 ，不含尾随 0
*/
class Solution172 {
public:
    int trailingZeroes(int n) {
        int ans = 0;
        int num = 5;
        while (n >= num) {
            ans += n / num;
            num *= 5;
        }
        return ans;
    }
};

/*
69. x 的平方根 
给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。
*/
class Solution69 {
public:
    int mySqrt(int x) {
        int l = 0, r = x;
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if ((long long) mid * mid <= x) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};

/*
50. Pow(x, n)
实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。

示例 1：

输入：x = 2.00000, n = 10
输出：1024.00000

示例 2：

输入：x = 2.00000, n = -2
输出：0.25000
解释：2-2 = 1/22 = 1/4 = 0.25

快速幂
x^35 = (x^17)^2 = x^16 * x = x^8 = x^4 = x^2 = x^1 = x^0
*/
class Solution50 {
public:
    double quickMul(double x, long long n) {
        if (n == 0) {
            return 1.0;
        }
        double y = quickMul(x, n / 2);
        return n % 2 == 0 ? y * y : y * y * x;
    }

    double myPow(double x, int n) {
        long long N = n;
        return n >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};

/*
35. 搜索插入位置
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。
*/
class Solution35 {
public:
    int searchInsert(std::vector<int>& nums, int target) {
        auto len = nums.size();
        int l = 0, r = len - 1, ans = len;
        while (l <= r) {
            int mid = l + ((r - l) >> 2);
            if (nums[mid] >= target) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};

/*
6. Z 字形变换
将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

P   A   H   N
A P L S I I G
Y   I   R
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
math conclusion: head and tail: xi += 2n. midRow: xi += 2(n - row) -> xi += 2row (cycle)
步长交互使用标志位取反
*/
class Solution6 {
public:
    std::string convert(std::string s, int numRows) {
        if (s.size() <= numRows || numRows == 1) {
            return s;
        }
        int index = 0;
        int cycle = 2 * (numRows - 1);
        std::string ans;
        for (int i = 0; i < numRows; ++i) {
            index = i;
            bool isMidRow = i > 0 && i < numRows - 1;
            int step1 = 2 * (numRows - 1 - i);
            int step2 = 2 * i;
            bool useStep1 = true;
            while (index < s.size()) {
                ans += s[index];
                if (isMidRow) {
                    index += useStep1 ? step1 : step2;
                    useStep1 = !useStep1;
                } else {
                    index += cycle;
                }
            }
        }
        return ans;
    }
};

/*
134. 加油站
在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。

贪心的思想有点绕：currentGas在站点 i处变为负数，说明从当前 start出发无法到达 i+1。此时，start到 i之间的任何站点都不能作为有效起点。
*/
class Solution134 {
public:
    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        int totalGas = 0, currentGas = 0, start = 0;
        for (int i = 0; i < gas.size(); ++i) {
            int netGas = gas[i] - cost[i];
            totalGas += netGas;
            currentGas += netGas;
            if (currentGas < 0) {
                start = i + 1;
                currentGas = 0;
            }
        }
        return totalGas >= 0 ? start : -1;
    }
};

/*
209. 长度最小的子数组
给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。
如果不存在符合条件的子数组，返回 0 。

示例 1：
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。

滑动窗口: 一直右滑，当满足条件时，左滑缩短条件
*/
class Solution209 {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        int len = nums.size(), ans = len + 1, sum = 0, left = 0;
        for (int right = 0; right < len; ++right) {
            sum += nums[right];
            while (sum >= target) {
                ans = std::min(ans, right - left + 1);
                sum -= nums[left];
                ++left;
            }
        }
        return ans > len ? 0 : ans;
    }
};

/*
3. 无重复字符的最长子串
给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。

示例 1:

输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
*/
class Solution3 {
public:
    int lengthOfLongestSubstring(std::string s) {
        // int len = s.size(), ans = 0, left = 0;
        // std::unordered_map<char, int> map;
        // for (int right = 0; right < len; ++right) {
        //     char c = s[right];
        //     if (map.count(c) && map[c] >= left) {
        //         left = map[c] + 1;
        //     }
        //     map[c] = right;
        //     ans = std::max(ans, right - left + 1);
        // }
        // return ans;
        int len = s.size(), ans = 0, left = 0;
        std::unordered_set<char> set;
        for (int right = 0; right < len; ++right) {
            char ch = s[right];
            while (set.count(ch)) {
                set.erase(s[left++]);
            }
            ans = std::max(ans, right - left + 1);
            set.emplace(ch);
        }
        return ans;
    }
};

/*
36. 有效的数独
请你判断一个 9 x 9 的数独是否有效。只需要 根据以下规则 ，验证已经填入的数字是否有效即可。

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）

每一行、列、box每一个数都没有出现过， 当出现了row[i][curNum] == 1就代表curNum在之前已经出现过了
*/
class Solution36 {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        int row[9][10] = { 0 };
        int col[9][10] = { 0 };
        int box[9][10] = { 0 };
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    continue;
                }
                int curNum = board[i][j] - '0';
                if (row[i][curNum]) {
                    return false;
                }
                if (col[j][curNum]) {
                    return false;
                }
                if (box[(i / 3) * 3 + (j / 3)][curNum]) {
                    return false;
                }
                row[i][curNum] = 1;
                col[j][curNum] = 1;
                box[(i / 3) * 3 + j / 3][curNum] = 1;
            }
        }
        return true;
    }
};

/*
54. 螺旋矩阵
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
*/
class Solution54 {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = n - 1, top = 0, bottom = m - 1;
        std::vector<int> ans;
        while (left <= right && top <= bottom) {
            // left -> right
            for (int i = left; i <= right; ++i) {
                ans.emplace_back(matrix[top][i]);
            }
            ++top;
            // top -> bottom
            for (int j = top; j <= bottom; ++j) {
                ans.emplace_back(matrix[j][right]);
            }
            --right;
            // right -> left
            if (top <= bottom) {
                for (int k = right; k >= left; --k) {
                    ans.emplace_back(matrix[bottom][k]);
                }
            }
            --bottom;
            // bottom -> top
            if (left <= right) {
                for (int l = bottom; l >= top ; --l) {
                    ans.emplace_back(matrix[l][left]);
                }
            }
            ++left;
        }
        return ans;
    }
};

/*
73. 矩阵置零
给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。
*/
class Solution73 {
public:
    void setZeroes(std::vector<std::vector<int>>& matrix) {
        bool colZero = false;
        int row = matrix.size(), col = matrix[0].size();
        for (int i = 0; i < row; ++i) {
            if (matrix[i][0] == 0) {
                colZero = true;
            }
            for (int j = 1; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        // 如果顺序遍历的话, 第一列的标志位会影响到后序, 所以要逆序遍历
        for (int i = row - 1; i >= 0; --i) {
            for (int j = col - 1; j > 0; --j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
            if (colZero) {
                matrix[i][0] = 0;
            }
        }
    }
};

/*
48. 旋转图像
给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
对于奇偶矩阵, 都是x = len / 2, y = (len + 1) / 2, 之间进行旋转, 之后算好坐标即可
*/
class Solution48 {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        int len = matrix.size();
        for (int i = 0; i < len / 2; ++i) {
            for (int j = 0; j < (len + 1) / 2; ++j) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[len - j - 1][i];
                matrix[len - j - 1][i] = matrix[len - i - 1][len - j - 1];
                matrix[len - i - 1][len - j - 1] = matrix[j][len - i - 1];
                matrix[j][len - i - 1] = temp;
            }
        }
    }
};

/*
283. 移动零
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。
*/
class Solution283 {
public:
    void moveZeroes(std::vector<int>& nums) {
        for (int fast = 0, slow = 0; fast < nums.size(); ++fast) {
            if (nums[fast] != 0) {
                std::swap(nums[slow++], nums[fast]);
            }
        }
    }
};

/*
289. 生命游戏
生命游戏 ，简称为 生命 ，是英国数学家约翰·何顿·康威在 1970 年发明的细胞自动机。

给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态： 1 即为 活细胞 （live），或 0 即为 死细胞 （dead）。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是 同时 发生的。给你 m x n 网格面板 board 的当前状态，返回下一个状态。

给定当前 board 的状态，更新 board 到下一个状态。

注意 你不需要返回任何东西。
难: 0表示死，1表示生，10 表示原来死变生了，11 表示原来是生的现在还是生的，00 01同理
*/
class Solution289 {
public:
    void gameOfLife(std::vector<std::vector<int>>& board) {
        int rows = board.size(), cols = board[0].size();
        int dx[] = { -1, 1, 0, 0, -1, -1, 1, 1};
        int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1};
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int sum = 0;
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        sum += (board[ni][nj] & 1);
                    }
                }
                if (board[i][j] == 1) {
                    if (sum == 2 || sum == 3) {
                        board[i][j] |= 2;
                    }
                } else {
                    if (sum == 3) {
                        board[i][j] |= 2;
                    }
                }
            }
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                board[i][j] >>= 1;
            }
        }
    }
};

/*
228. 汇总区间
给定一个  无重复元素 的 有序 整数数组 nums 。

区间 [a,b] 是从 a 到 b（包含）的所有整数的集合。

返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个区间但不属于 nums 的数字 x 。

列表中的每个区间范围 [a,b] 应该按如下格式输出：

"a->b" ，如果 a != b
"a" ，如果 a == b

示例 1：

输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"

题都看不明白, 才看明白...
*/
class Solution228 {
public:
    std::vector<std::string> summaryRanges(std::vector<int>& nums) {
        std::vector<std::string> ans;
        int len = nums.size(), low = 0, i = 0;
        while (i < len) {
            low = i;
            ++i;
            while (i < len && (nums[i - 1] + 1 == nums[i])) {
                ++i;
            }
            int high = i - 1;
            std::string temp = std::to_string(nums[low]);
            if (low < high) {
                temp.append("->");
                temp.append(std::to_string(nums[high]));
            }
            ans.emplace_back(std::move(temp));
        }
        return ans;
    }
};

/*
56. 合并区间
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
*/
class Solution56 {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        std::vector<std::vector<int>> ans;
        std::sort(intervals.begin(), intervals.end());
        int i = 0, len = intervals.size();
        while (i < len) {
            auto currentStart = intervals[i][0];
            auto currentEnd = intervals[i][1];
            while (i + 1 < len && intervals[i + 1][0] <= currentEnd) {
                ++i;
                currentEnd = std::max(currentEnd, intervals[i][1]);
            }
            ans.push_back({currentStart, currentEnd});
            ++i;
        }
        return ans;
    }
};

/*
57. 插入区间
给你一个 无重叠的 ，按照区间起始端点排序的区间列表 intervals，其中 intervals[i] = [starti, endi] 表示第 i 个区间的开始和结束，
并且 intervals 按照 starti 升序排列。同样给定一个区间 newInterval = [start, end] 表示另一个区间的开始和结束。

在 intervals 中插入区间 newInterval，使得 intervals 依然按照 starti 升序排列，且区间之间不重叠（如果有必要的话，可以合并区间）。

返回插入之后的 intervals。

注意 你不需要原地修改 intervals。你可以创建一个新数组然后返回它。

示例 1：

输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]
*/
class Solution57 {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        std::vector<std::vector<int>> ans;

        return ans;
    }
};

/*
844. 比较含退格的字符串

给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回 true 。# 代表退格字符。

注意：如果对空文本输入退格字符，文本继续为空。
*/
class Solution844 {
public:
    void backspace(std::string &str) {
        for (auto it = str.begin(); it != str.end();) {
            if (*it != '#') {
                ++it;
                continue;
            }
            if (it == str.begin()) {
                it = str.erase(it);
            } else {
                --it;
                it = str.erase(it);
                it = str.erase(it);
            }
        }
    }

    bool backspaceCompare(std::string s, std::string t) {
        backspace(s);
        backspace(t);
        return s == t;
    }
};



int main() {
    Solution172 s;
    std::cout << s.trailingZeroes(15) << std::endl;
}

// /*
// 49. 字母异位词分组
// 给你一个字符串数组，请你将字母异位词组合在一起。可以按任意顺序返回结果列表。
// 示例 1:

// 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

// 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

// 解释：
// 在 strs 中没有字符串可以通过重新排列来形成 "bat"。
// 字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
// 字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。
// */
// class Solution {
// public:
//     std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
//     }
// };

// /*
// 67. 二进制求和
// 给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。
// */
// class Solution67 {
// public:
//     char addBinaryChar(char a, char b, bool &carry) {

//         if (carry) {
//         //    auto num = (std::fabs(a - b) + carry) % 2;
//         }
//         return ' ';
//     }

//     std::string addBinary(std::string a, std::string b) {
//         std::string ans = a.size() > b.size() ? a : b;

//         int pa = a.size() - 1, pb = b.size() - 1;
//         bool carry = false;
//         while (pa >= 0 && pb >= 0) {
//             ans.push_back(addBinaryChar(a[pa], b[pb], carry));
//         }
//         std::reverse(ans.begin(), ans.end());
//         return ans;
//     }
// };