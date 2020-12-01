#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

vector<int> load(const filesystem::path& path)
{
    ifstream input(path);

    vector<int> res;
    if (input) {
        int num;

        while (input >> num) {
            res.push_back(num);
        }
    }

    return res;
}

pair<int, int> twosum(vector<int>& nums, int sum, int start = 0)
{
    unordered_map<int, int> m;
    for (auto i = start; i < nums.size(); i++) {
        if (m.count(sum - nums[i]) > 0) {
            return {i, m[sum - nums[i]]};
        }
        m[nums[i]] = i;
    }
    return {-1, -1};
}

int main(int argc, char *argv[]) 
{
    if (argc <= 1) {
        exit(-1);
    }

    auto nums = load(filesystem::path(argv[1]));

    auto p = twosum(nums, 2020);

    cout << p.first << " " << p.second << ": " << nums[p.first] * nums[p.second] << endl;

    for (auto i = 0; i < nums.size(); i++) {
        auto p = twosum(nums, 2020 - nums[i], i + 1);
        if (p.first >= 0) {
            cout << nums[i] * nums[p.first] * nums[p.second] << endl;
        }
    }

    return 0;
}
