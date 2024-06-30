#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    char filename[100];
    FILE *file;
    char c;
    int word_count = 0, line_count = 0, char_count = 0;
    bool in_word = false;

    printf("Enter the filename: ");
    scanf("%99s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((c = fgetc(file)) != EOF) {
        char_count++;

        if (c == '\n') {
            line_count++;
        }

        if (isspace(c) || c == '\n') {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            word_count++;
        }
    }

    // Account for last line if file doesn't end with a newline
    if (char_count > 0 && c != '\n') {
        line_count++;
    }

    fclose(file);

    printf("\nFile Analysis Results:\n");
    printf("----------------------\n");
    printf("Word count:  %d\n", word_count);
    printf("Line count:  %d\n", line_count);
    printf("Char count:  %d\n", char_count);

    return 0;
}
