/* h - moves cursor to the left, l - moves cursor to the right
i - switches to insert mode, <ESC> - switches back to view mode
insert mode - all symbols are written into the document
view mode - all commands except for h, l, i are ignored */

#include <iostream>
#include <list>
#include <string>

class Vim {
private:
    std::list<char> output;
    bool Reading;
    std::list<char>::iterator ptr;

public:
    Vim()
    : output({})
    , Reading(true)
    , ptr(output.end()) {}

    void i() {
        if (!Reading) {
            output.insert(ptr, 'i');
            return;
        }
        Reading = false;
    }

    void esc() {
        Reading = true;
    }

    void h() {
        if (!Reading) {
            output.insert(ptr, 'h');
            return;
        }
        if (ptr != output.begin()) {
            --ptr;
        }
    }

    void l() {
        if (!Reading) {
            output.insert(ptr, 'l');
            return;
        }
        if (ptr != output.end()) {
            ++ptr;
        }
    }

    void other(char elem) {
        if (!Reading) {
            output.insert(ptr, elem);
        }
    }

    auto out() const {
        return output;
    }
};

using namespace std;


int main() {
    char elem;
    Vim text;
    while (cin >> elem) {
        switch (elem) {
            case 'i':
                text.Vim::i();
                break;
            case 'h':
                text.Vim::h();
                break;
            case 'l':
                text.Vim::l();
                break;
            case '<':
                text.Vim::esc();
                for (int i = 0; i < 4; ++i) {
                    cin >> elem;
                }
                break;
            default:
                text.Vim::other(elem);
        }
    }
    auto t = text.Vim::out();
    for (char x : t) {
        std::cout << x;
    }
    std::cout << '\n';
}

