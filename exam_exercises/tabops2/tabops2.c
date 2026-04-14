// tabops2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 1024
#define MAX_TOKENS 26
#define STACK_MAX 100

/* ---------- delimiters ---------- */
int is_delim(char c, const char *delim) {
    for (const char *d = delim; *d != 0; ++d)
        if (*d == c) return 1;
    return 0;
}

/* ---------- tokenizer: up to 26 items per line ---------- */
unsigned tokenize_line(char *line, const char *S[], const char *delim) {
    unsigned n = 0;
    int in_tok = 0;
    for (char *p = line; *p != 0; ++p) {
        if (*p == '\n' || is_delim(*p, delim)) {
            if (in_tok) {
                *p = 0;
                in_tok = 0;
                if (n == MAX_TOKENS) break;
            }
        } else {
            if (!in_tok) {
                if (n < MAX_TOKENS) S[n++] = p;
                in_tok = 1;
            }
        }
    }
    return n;
}

/* ---------- parse item as integer: full-string check, +/- allowed ---------- */
long parse_item_as_int(const char *s) {
    if (s == NULL || *s == 0) return 0;
    int i = 0;
    int sign = 1;
    long val = 0;

    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-') sign = -1;
        i++;
    }
    if (s[i] == 0) return 0;

    for (; s[i] != 0; ++i) {
        if (s[i] < '0' || s[i] > '9') return 0;
        val = val * 10 + (s[i] - '0');
    }
    return sign * val;
}

/* ---------- simple global stack (no typedef, no & in calls) ---------- */
long stack_v[STACK_MAX];
int  stack_top = 0;

void stack_init(void) {
    stack_top = 0;
}

int stack_push(long x) {
    if (stack_top >= STACK_MAX) return 0;
    stack_v[stack_top] = x;
    stack_top++;
    return 1;
}

int stack_size(void) {
    return stack_top;
}

long stack_pop_val(void) {
    if (stack_top < 1) return 0;
    stack_top--;
    return stack_v[stack_top];
}

long stack_peek_val(void) {
    return stack_v[stack_top - 1];
}

/* ---------- expression evaluator state (avoid &) ---------- */
long eval_last_value = 0;
int  eval_has_value = 0;

/* evaluate expression inside {start..end-1} */
int eval_expr(const char *start, const char *end, const char *S[], unsigned n) {
    stack_init();
    eval_has_value = 0;

    const char *p = start;

    while (p < end) {
        unsigned char ch = (unsigned char)(*p);

        if (isspace(ch)) {
            p++;
            continue;
        }

        /* literal non-negativo */
        if (ch >= '0' && ch <= '9') {
            long val = 0;
            while (p < end && *p >= '0' && *p <= '9') {
                val = val * 10 + (*p - '0');
                p++;
            }
            stack_push(val);
            continue;
        }

        /* variabile a..z → push valore dell'item (o 0 se assente/non intero) */
        if (ch >= 'a' && ch <= 'z') {
            unsigned idx = (unsigned)(ch - 'a');
            long val2 = 0;
            if (idx < n) val2 = parse_item_as_int(S[idx]);
            stack_push(val2);
            p++;
            continue;
        }

        /* operatori binari */
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (stack_size() >= 2) {
                long b = stack_pop_val();
                long a = stack_pop_val();
                long r = 0;

                if (ch == '+') r = a + b;
                else if (ch == '-') r = a - b;
                else if (ch == '*') r = a * b;
                else {
                    if (b == 0) { p++; continue; }  /* ignora divisione per zero */
                    r = a / b;                      /* divisione intera */
                }
                stack_push(r);
            }
            p++;
            continue;
        }

        /* altro carattere: ignora */
        p++;
    }

    if (stack_size() == 0) return 0;

    eval_last_value = stack_peek_val();
    eval_has_value = 1;
    return 1;
}

/* ---------- process a single file with given format/delim ---------- */
void process_file(FILE *f, const char *format, const char *delim) {
    char line[LINE_LENGTH + 1];
    const char *S[MAX_TOKENS];

    while (fgets(line, sizeof(line), f)) {
        unsigned n = tokenize_line(line, S, delim);

        for (const char *p = format; *p != 0; ++p) {
            if (*p == '@') {
                p++;
                if (*p >= 'a' && *p <= 'z') {
                    unsigned idx = (unsigned)(*p - 'a');
                    if (idx < n) fputs(S[idx], stdout);
                }
            }
            else if (*p == '{') {
                const char *start = p + 1;
                const char *q = start;
                while (*q != 0 && *q != '}') q++;
                if (*q == '}') {
                    if (eval_expr(start, q, S, n)) {
                        printf("%ld", eval_last_value);
                    }
                    p = q;
                } else {
                    /* nessuna '}' trovata: ignora il resto */
                    break;
                }
            }
            else {
                putchar(*p);
            }
        }
        putchar('\n');
    }
}

/* ---------- main: same CLI semantics as exercise 1 ---------- */
int main(int argc, char *argv[]) {
    const char *format = "@a";
    const char *delim  = " \t";
    int read_stdin = 1;

    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "format=", 7) == 0) {
            format = argv[i] + 7;
        } else if (strncmp(argv[i], "delim=", 6) == 0) {
            delim = argv[i] + 6;
        } else {
            read_stdin = 0;
            FILE *in = fopen(argv[i], "r");
            if (!in) {
                fprintf(stderr, "could not open file %s.\n", argv[i]);
                return EXIT_FAILURE;
            }
            process_file(in, format, delim);
            fclose(in);
        }
    }

    if (read_stdin) process_file(stdin, format, delim);
    return 0;
}
