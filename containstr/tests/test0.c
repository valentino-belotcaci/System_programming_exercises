#include <assert.h>

extern int contains_str(const char * s, const char * x);

int main() {
    assert(contains_str("", ""));
    assert(contains_str("a", ""));
    assert(contains_str("abc", ""));
    assert(!contains_str("", "a"));
    assert(!contains_str("", "abc"));
    assert(!contains_str("abc", "d"));
    assert(!contains_str("abc", "ad"));
    assert(!contains_str("abc", "ba"));

    assert(contains_str("abc", "a"));
    assert(contains_str("ciao mamma", "ciao mamma"));
    assert(contains_str("abc defg xyz", "z"));
    assert(contains_str("abc defg xyz", "xyz"));
    assert(contains_str("abc defg xyz", "c d"));
    assert(contains_str("abc defg xyz", "x"));

    assert(contains_str("ababab cdcdcd", "ab cd"));
    assert(!contains_str("ababab cdcdcd", "abac"));
    assert(!contains_str("ababab cdcdcd", "abcd"));
    assert(contains_str("ababab cdcdcd", "dcdc"));
}

