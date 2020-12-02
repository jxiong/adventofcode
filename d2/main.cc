#include <cstdio>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Entry {
public:
    explicit Entry(string s) {
        istringstream is(s);

        is >> low;
        is.ignore();
        is >> high;
        is.ignore();
        is >> character;
        is.ignore(2);
        is >> password;
    }

    void print() {
        printf("%d - %d, %c : %s\n", low, high, character, password.c_str());
    }

    bool isLegal() {
        int count = 0;

        for (auto c : password) {
            if (c == character) {
                ++count;
            }
        }

        return count >= low && count <= high;
    }

    bool isLegal2() {
        int count = 0;

        if (password.size() < low) {
            return false;
        }

        if (password[low - 1] == character) {
            ++count;
        }

        if (password.size() >= high && password[high - 1] == character) {
            ++count;
        }

        return count == 1;
    }

private:
    int low;
    int high;
    char character;
    string password;
};

vector<Entry> load(const filesystem::path& input)
{
    ifstream file(input);

    vector<Entry> res;
    if (file) {
        while (!file.eof()) {
            string s;

            getline(file, s);
            if (s.empty()) {
                continue;
            }

            res.push_back(Entry(s));
        }
    }

    return res;
}

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        cout << "Usage: " << argv[0] << " <filename>\n";
        exit(EXIT_FAILURE);
    }

    auto pws = load(filesystem::path(argv[1]));

    int count = 0;
    for (auto e : pws) {
        if (e.isLegal()) {
            ++count;
        }
    }
    cout << count << endl;

    int count2 = 0;
    for (auto e : pws) {
        if (e.isLegal2()) {
            ++count2;
        }
    }

    cout << count2 << endl;
    return 0;
}
