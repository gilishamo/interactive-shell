#ifndef _UTILS_H
#define _UTILS_H

char** split_str(char *s, const char *delim);
char* join(char **strings, char *delim);
void free_string_arr(char **strings);
int copy_file(char* src, char* dst);

#endif