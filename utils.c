#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* 
    split_str split s by delim and return a slice containing all subs-trings of s after the split 
    Notice: caller is responsible to free the memmory of the return value
*/
char** split_str(char *s, const char *delim) {

    // TODO - fix case of trailing delim


    // copy s (we will be using strtoken which modifies the original string)
    char *s_dup = _strdup(s);
    if (s_dup == NULL) {
        printf("ERROR: failed to allocate memmory");
        return NULL; // nothing to clean
    }

    // using tmp to count appearances of delim (we will be using s_dup again)
    char *tmp = s_dup;
    int count = 0;
    // count appearacnes of delim
    while (*tmp) {
        if (*tmp == *delim) {
            count += 1;
        }
        tmp++;
    }

    // increment by 1
    count++;
    // space for null
    count++;
   
   // allocate memmory to hold all sub strings of s
    char **result = (char**)malloc(sizeof(char*)*count);
    if (result == NULL) {
        printf("ERROR: failed to allocate memmory\n");
        goto cleanup;
    }

    int index = 0;
    char *token = strtok(s_dup, delim); 
    while (token) {
        *(result + index++) = _strdup(token); // save token in array
        token = strtok(NULL, delim); // find next token
    }
    *(result+index) = NULL;

    cleanup:
    free(s_dup);

    return result;
}

int len_of_string_arr(char **strings) {
    int n = 0;
    char **tmp = strings;

    while (*tmp) {
        n++;
        tmp++;
    }

    return n;
}

void free_string_arr(char **strings) {
    char **tmp = strings;

    while (*tmp) {
      free(*tmp);
        tmp++;
    }

    free(strings);
}

char* join(char **strings, char *delim) {
    int n = len_of_string_arr(strings);

    // count total length of all strings
    int count = 0, i = 0;
    for (i = 0; i < n; i++) {

        count += sizeof(*(strings+i));
    }

    // add space for delim
    int countDelim = n ? (n-1) * sizeof(delim) : 0;
    count += countDelim;
    count++; // spaace for null terminating character  

    // allocate result
    char *res = (char*)malloc(sizeof(char)*count);
    if (res == NULL) {
        return NULL;
    }

    int index = 0;
    for (i = 0; i < n; i++) {
        strcpy(res+index, *(strings+i));
        index += strlen(*(strings+i));
        *(res+index) = *delim;
        index += strlen(delim);
    }
    *(res+index) = '\0';

    return res;
}