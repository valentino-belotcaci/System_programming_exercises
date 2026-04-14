#include <assert.h>

extern int contains_double(const char * s);

int main() {
    assert(!contains_double(""));
    assert(!contains_double(" "));
    assert(contains_double("  - "));
    assert(!contains_double("  1- "));
    assert(contains_double("  1-1"));
    assert(!contains_double("  1-"));
    assert(!contains_double("  xyz-yyx"));
    assert(!contains_double("  xyz-yyx  ciao-mamma"));
    assert(contains_double("  ..xyz-xyz  ciao-mamma"));
    assert(contains_double("  ..xyz-yyx  ciao-ciao"));
    assert(!contains_double("- ..-zyx  ciao-cia"));
    assert(contains_double("- -..-zyx  ciao-ciao-"));
}
