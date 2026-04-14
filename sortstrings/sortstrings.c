#include<stdio.h>
#include<string.h>
/*
sortstrings: In a source file called sortstrings.c write a function 
void sort_strings(const char * input, char * output, unsigned int n) t
hat takes a sequence of n≤1000 contiguous C strings from a given input memory buffer, 
and copies in a given output buffer the same strings, also as a sequence of contiguous C strings, 
but sorted in non-decreasing lexicographical order. The order is defined by the numerical order of the character codes. 
Do not worry too much about the complexity of your sorting algorithm. 
You may not use any external library function, not even from the C standard library.
*/
void sort_strings(const char *input, char *output, unsigned int n)
{
    /* -----------------------------------------------------------
     * STEP 1: Collect the addresses of the n contiguous strings
     * -------------------------------------------------------- */
    const char *strings[n];          /* temporary array of pointers  */

    strings[0] = input;              /* first string starts at input */

    for (unsigned int i = 1; i < n; ++i) {
        /* Move \`input\` forward until we reach the NUL byte that
         * ends the current string.                                */
        while (*input != '\0') {
            ++input;
        }
        /* Advance one more position so that \`input\` now points
         * to the first character of the next string, then store
         * that address.                                           */
        strings[i] = ++input;
    }

    /* -----------------------------------------------------------
     * STEP 2: Sort the pointer array 
     * -------------------------------------------------------- */
    for (unsigned int i = 0; i < n - 1; ++i) {
        for (unsigned int j = i + 1; j < n; ++j) {
            /* \`strcmp\` returns >0 if strings[i] is after strings[j]
             * lexicographically.  In that case swap the two pointers. */
            if (strcmp(strings[i], strings[j]) > 0) {
                const char *tmp = strings[i];
                strings[i]      = strings[j];
                strings[j]      = tmp;
            }
        }
    }

    /* -----------------------------------------------------------
     * STEP 3: Copy the sorted strings into the output buffer
     * -------------------------------------------------------- */
    for (unsigned int i = 0; i < n; ++i) {
        const char *p = strings[i];   /* current source string */

        /* Copy every character, including the final NUL. */
        while (*p != '\0') {
            *output++ = *p++;
        }
        *output++ = '\0';            /* write the terminator */
    }
}
