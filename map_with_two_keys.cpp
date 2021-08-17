/* map where each value can have two types of keys */
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>


template <typename Key1, typename Key2, typename Value>
class BiMap {
private:
    std::map<Key1, std::shared_ptr<Value>> First;
    std::map<Key2, std::shared_ptr<Value>> Second;

public:
    // insert value by specifying one or both keys
    // generates exception std::invalid_argument("some text") if
    // both keys are empty or if one of the keys is already stored
    void Insert(const std::optional<Key1>& key1,
                const std::optional<Key2>& key2, const Value& value) {
        if (!key1 && !key2) {
            throw std::invalid_argument("some text");
        }
        if (key1 && (First.find(*key1) != First.end())) {
            throw std::invalid_argument("some text");
        }
        if (key2 && (Second.find(*key2) != Second.end())) {
            throw std::invalid_argument("some text");
        }
        auto shared = std::make_shared<Value>(value);
        if (key1) {
            First[*key1] = shared;
        }
        if (key2) {
            Second[*key2] = shared;
        }
    }

    // Get value by first of the keys
    // generates exception std::out_of_range("some text")
    // if there is no such key
    Value& GetByPrimaryKey(const Key1& key) {
        auto it = First.find(key);
        if (it != First.end()) {
            return *it->second;
        }
        throw std::out_of_range("some text");
    }
    const Value& GetByPrimaryKey(const Key1& key) const {
        auto it = First.find(key);
        if (it != First.end()) {
            return *it->second;
        }
        throw std::out_of_range("some text");
    }



    Value& GetBySecondaryKey(const Key2& key) {
        auto it = Second.find(key);
        if (it != Second.end()) {
            return *it->second;
        }
        throw std::out_of_range("some text");
    }
    const Value& GetBySecondaryKey(const Key2& key) const {
        auto it = Second.find(key);
        if (it != Second.end()) {
            return *it->second;
        }
        throw std::out_of_range("some text");
    }
};

/* Usage example

using namespace std;

struct Student {
    string FirstName, LastName;
};

ostream& operator << (ostream& out, const Student& s) {
    return out << s.FirstName << " " << s.LastName;
}

int main() {
    BiMap<int, string, Student> bimap;  // each student can be identified by number or by login
    bimap.Insert(42, {}, {"A", "Aa"});
    bimap.Insert({}, "login2", {"B", "Bb"});
    bimap.Insert(13, "login3", {"C", "Cc"});

    cout << bimap.GetByPrimaryKey(42) << "\n";  // A Aa

    cout << bimap.GetBySecondaryKey("login2") << "\n";  // B Bb

    cout << bimap.GetByPrimaryKey(13) << "\n";  // C Cc
    cout << bimap.GetBySecondaryKey("login3") << "\n";  // C Cc

    bimap.GetByPrimaryKey(13).LastName = "Dd";  // if the value is changed by the first key, it should also be changed by the second
    cout << bimap.GetByPrimaryKey(13) << "\n";  // C Dd
    cout << bimap.GetBySecondaryKey("login3") << "\n";  // C Dd
    return 0;
}