#include<stdio.h>

/*
contains double: In a source file called containsdouble.c write a function: 
int contains_double(const char * s) The contains_double function must return true (non zero) 
if and only if the string s contains two identical non-empty strings separated by a hyphen character (-). 
For example, contains_double("there are no hyphens in this string") should return false and also contains_double("a-b") 
should return false, while contains_double("012-012!") should return true. You may not use any external library function, 
not even from the C standard library.
*/
// containsdouble.c

int contains_double(const char *s) {
    const char *p = s;

    // Step 1: scan the string looking for a hyphen
    while (*p != '\0') {
        if (*p == '-') {
            const char *hyphen = p;

            // Step 2: Try all possible lengths (len >= 1)
            for (int len = 1;; len++) {
                const char *left_start = hyphen - len;
                const char *right_start = hyphen + 1;

                // Make sure left doesn't go before beginning
                if (left_start < s)
                    break;

                // Make sure right side is long enough
                const char *r = right_start;
                int ok = 1;
                for (int i = 0; i < len; i++) {
                    if (r[i] == '\0') {
                        ok = 0;
                        break;
                    }
                }
                if (!ok)
                    break;

                // Compare the two substrings character by character
                int match = 1;
                for (int i = 0; i < len; i++) {
                    if (left_start[i] != right_start[i]) {
                        match = 0;
                        break;
                    }
                }

                if (match)
                    return 1;
            }
        }
        p++;
    }

    return 0;
}


/*
int main(){

    int res = 0;
    const char * s = "012-012!";
    res = contains_double(s);
    printf("%d", res);

}*/