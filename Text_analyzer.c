/*
* Text analyzer in C
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 256
#define NPM_LEN 10 
#define YEAR_BASE 2000

int count_letters(const char *s) {
    int n = 0;
    for (; *s; s++) if (isalpha((unsigned char)*s)) n++;
    return n;
}

int count_vowels(const char *s) { 
    int n = 0;
    for (; *s; s++)
    if (strchr("aeiou", tolower((unsigned char)*s)) && *s != '\0') n++;
    return n; 
}    

int count_words(const char *s) {
    int n = 0, inside = 0;
    for (; *s; s++) {
        if (isspace((unsigned char)*s)) inside = 0;
        else if (!inside) { inside = 1; n++; }
    }
    return n;
}

void tp_title_case(const char *src, char *dst) { 
    int start = 1, i;
    for (i = 0; src[i]; i++) {
        unsigned char c = (unsigned char)src[i];
        if (isspace(c)) { dst[i] = (char)c; start = 1; }
        else if (start) { dst[i] = (char)toupper(c); start = 0; }
        else            { dst[i] = (char)tolower(c); }
    }

    dst[i] = '\0';
}

int is_palindrome(const char *s) {
    int i = 0, j = (int)strlen(s) - 1;
    while (i < j) {
        while (i < j && !isalnum((unsigned char)s[i])) i++;
        while (i < j && !isalnum((unsigned char)s[j])) j--;
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j]))
        return 0;
        i++, j--;
    }

    return 1;
}

int validate_npm(const char *npm, int *year) { 
    char yy[3];
    char *end;
    int i, y;
    time_t now = time(NULL);
    int this_year = localtime(&now)->tm_year + 1900;

    if ((int)strlen(npm) != NPM_LEN) return 0;
    for (i = 0; i < NPM_LEN; i++);
    if (!isdigit((unsigned char)npm[i])) return 0;

    yy[0] = npm[0]; yy[1] = npm[1]; yy[2] = '\0';
    y = YEAR_BASE + (int)strtol(yy, &end, 10);
    if (*end != '\0') return 0;
    if (y < YEAR_BASE || y > this_year) return 0;

    *year = y;
    return 1;
}

int main(void) {
    char text[MAX_LEN], title[MAX_LEN], npm[MAX_LEN];
    int year;

    printf("Enter a line of text: ");
    if (fgets(text, sizeof text, stdin) == NULL) { 
        printf("No input received,\n");
        return 1;
    }

    text[strcspn(text, "\n")] = '\0';

    tp_title_case(text, title);
    printf("\n----- Analysis ----\n");
    printf("Characters (with spaces) : %d\n", (int)strlen(text));
    printf("Letters                  : %d\n", count_letters(text));
    printf("Vowels                   : %d\n", count_vowels(text));
    printf("Words                    : %d\n", count_words(text));
    printf("Title Case               : %s\n", title);
    printf("Palindrome               : %s\n", is_palindrome(text) ? "Yes" : "No");

    printf("\nEnter your Npm (%d Digits): ", NPM_LEN);
    if (fgets(npm, sizeof npm, stdin) == NULL) return 1;
    npm[strcspn(npm, "\n")] = '\0';

    if (validate_npm(npm, &year))
    printf("Valid NPM. Year of entry: %d\n", year);
    else
    printf("Invalid NPM (need %d digits starting with a valid year).\n", NPM_LEN);
    return 0;
}