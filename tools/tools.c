#include <tools.h>

void read_input(char* buff, int size) {
    int n = 0;
    int c;

    // Read input until newline or end of file, but ensure we do not exceed buffer size
    while (n < size - 1 && (c = getchar()) != '\n' && c != EOF) {
        buff[n++] = (char)c;
    }

    // Null-terminate the string
    buff[n] = '\0';
}