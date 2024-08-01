#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_PARAGRAPH_SIZE 1000
#define MAX_WORD_SIZE 100
#define MAX_WORD_COUNT 1000


void toLowerCase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}


int findWordIndex(char words[MAX_WORD_COUNT][MAX_WORD_SIZE], int count, const char *word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return i;
        }
    }
    return -1;
}


void getNextWord(const char **source, char *word) {
    const char *ptr = *source;
    while (*ptr && isspace(*ptr)) {
        ptr++;
    }

    const char *start = ptr;
    while (*ptr && !isspace(*ptr) && !strchr(".,!?;:", *ptr)) {
        ptr++;
    }

    size_t length = ptr - start;
    strncpy(word, start, length);
    word[length] = '\0';
    
    *source = ptr;
}

int main() {
    char paragraph[MAX_PARAGRAPH_SIZE];
    char words[MAX_WORD_COUNT][MAX_WORD_SIZE];
    int frequencies[MAX_WORD_COUNT];
    int wordCount = 0;

    printf("Enter a paragraph:\n");
    fgets(paragraph, sizeof(paragraph), stdin);

    
    size_t len = strlen(paragraph);
    if (len > 0 && paragraph[len - 1] == '\n') {
        paragraph[len - 1] = '\0';
    }

    
    toLowerCase(paragraph);

    
    const char *ptr = paragraph;
    char word[MAX_WORD_SIZE];

    while (*ptr) {
        getNextWord(&ptr, word);
        if (strlen(word) > 0) {
            int index = findWordIndex(words, wordCount, word);
            if (index != -1) {
                
                frequencies[index]++;
            } else {
                
                strncpy(words[wordCount], word, MAX_WORD_SIZE - 1);
                words[wordCount][MAX_WORD_SIZE - 1] = '\0'; 
                frequencies[wordCount] = 1;
                wordCount++;
            }
        }
    }

    
    printf("\nWord frequencies:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s: %d\n", words[i], frequencies[i]);
    }

    return 0;
}
