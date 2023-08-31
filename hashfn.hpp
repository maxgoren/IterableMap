#ifndef hashfn_hpp
#define hashfn_hpp
#include <string>
#include <cstring>
using std::string;
using std::strlen;
using std::size_t;
using std::pair;
using std::make_pair;
//combined bernsteins hash with knuths cyclic shift
size_t __string_hash(const string& s) {
    unsigned long h = s.length();
    for (char c : s) {
        h = (h << 27) | (h >> 5);
        h = (33*h+int(c));
    }
    return h;
}

size_t __string_hash(char* str) {
    unsigned long h = strlen(str);
    for (int i = 0; str[i] != '\0'; i++) {
        h = (h << 27) | (h >> 5);
        h = (33 * h + int(str[i]));
    }
    return h;
}

template <typename K>
struct hashfn { };

template<> struct hashfn<string> {
    size_t operator()(string& s) {
        return __string_hash(s);
    }
};

template<> struct hashfn<const string> {
    size_t operator()(const string& s) {
        return __string_hash(s);
    }
};

template<> struct hashfn<char> {
    size_t operator()(char c) {
        return size_t(c);
    }
};

template<> struct hashfn<short> {
    size_t operator()(short c) {
        return size_t(c);
    }
};

template<> struct hashfn<int> {
    size_t operator()(int c) {
        return size_t(c);
    }
};

template<> struct hashfn<long> {
    size_t operator()(long c) {
        return size_t(c);
    }
};

template<> struct hashfn<unsigned char> {
    size_t operator()(unsigned char c) {
        return size_t(c);
    }
};

template<> struct hashfn<unsigned int> {
    size_t operator()(unsigned int c) {
        return size_t(c);
    }
};

template<> struct hashfn<unsigned short> {
    size_t operator()(unsigned short c) {
        return size_t(c);
    }
};

template<> struct hashfn<unsigned long> {
    size_t operator()(unsigned int c) {
        return size_t(c);
    }
};

template<> struct hashfn<unsigned long long> {
    size_t operator()(unsigned int c) {
        return size_t(c);
    }
};

#endif