
#include <stdio.h>
#include <stdbool.h>

#define MAX_WORD_LEN 32
#define N_NOUNS 6
#define N_VERBS 5
#define N_ADJS 6
#define N_SUFFIXES (N_NOUNS + N_VERBS + N_ADJS)

bool IsSuffixInDict(char *str, char *dict[], int n);
int StringLength(char *str);
char* ConvertToLowercase(char *string, char *lowercase_str);
char* RemoveNonLetters(char *string, char *clean_str);
void CopyString(char *source, char *destination);
void DeleteChar(char *string, char *clean_str);
int StringCompare(char *string_1, char *string_2);
void MergeSuffixLists(char *list_1[], int len_1, char *list_2[], int len_2, char *merged_list[]);
void FlipString(char *orig_str, char *flipped_str, int str_len);
void ProcessWord(char *orig_str, char *lowercase_str, char *clean_word, char *flipped_word);
void ProcessDict(char *dict[], int dict_len);

int main()
{
    char *noun_suffixes[] = {"msi", "re", "sci", "ssen", "tnem", "tsi"};
    char *verb_suffixes[] = {"de", "eta", "ezi", "gni", "yfi"};
    char *adj_suffixes[] = {"elba", "evi", "hsi", "la", "luf", "suo"};

    char word[MAX_WORD_LEN + 1], lowercase_word[MAX_WORD_LEN + 1],
    clean_word[MAX_WORD_LEN + 1], flipped_word[MAX_WORD_LEN + 1];

    ProcessWord(word, lowercase_word, clean_word, flipped_word);

    printf("%s\n", flipped_word);

    return 0;
}

int StringLength(char *string_ptr) {
    int length = 0;
    while (*string_ptr != '\0') {
        length++;
        string_ptr++;
    }

    return length;
}

char* ConvertToLowercase(char *string, char *lowercase_str) {
    while (*string != '\0') {
        if (*string >= 'A' && *string <= 'Z') {
            char temp = *string;
            ///DEFINE THIS
            temp += ('z' - 'Z');
            *lowercase_str = temp;
        } else {
            *lowercase_str = *string;
        }

        string++;
        lowercase_str++;
    }

    *lowercase_str = '\0';

    return lowercase_str;
}

char* RemoveNonLetters(char *string, char *clean_str) {
    for (; *string != '\0'; string++, clean_str++) {
        while ((*string > 'z' || *string < 'a') && (*string != '.' ) && (*string != '\0')) {
            DeleteChar(string, clean_str);
            string++;
        }
            *clean_str = *string;
    }

    clean_str = '\0';

    return clean_str;
}


void DeleteChar(char *string, char *clean_str) {
    for (; *string != '\0'; string++, clean_str++) {
        *clean_str = *(string + 1);
    }

    *clean_str = '\0';
}

void MergeSuffixLists(char *list_1[], int len_1, char *list_2[], int len_2, char *merged_list[]) {
    int ia, ib, ic, comp_return_val;
    ia = ib = ic = 0;
    for (ia = ib = ic = 0; ia < len_1 && ib < len_2; ic++) {
        comp_return_val = StringCompare(*(list_1 + ia), *(list_2 + ib));
        if (comp_return_val == -1 || comp_return_val == -2) {
            *(merged_list + ic) = *(list_1 + ia);
            ia++;
        } else {
            *(merged_list + ic) = *(list_2 + ib);
            ib++;
        }
    }

    for(; ia < len_1; ia++, ic++) {
        *(merged_list + ic) = *(list_1 + ia);
    }

    for (; ib < len_2; ib++, ic++) {
        *(merged_list + ic) = *(list_2 + ib);
    }
}

void FlipString(char *orig_str, char *flipped_str, int str_len) {
    for (int i = str_len; i > 0; i--) {
        *(flipped_str + (str_len - i)) = *(orig_str + i - 1);
    }
    *(flipped_str + str_len) = '\0';
}

void ProcessWord(char *orig_str, char *lowercase_str, char *clean_word, char *flipped_word) {
    ConvertToLowercase(orig_str, lowercase_str);
    RemoveNonLetters(lowercase_str, clean_word);
    int word_len = StringLength(clean_word);
}

int StringCompare(char *string_1, char *string_2) {
    while (*string_1 != '\0') {
        if (*string_2 == '\0') {
            return 2;
        }

        if (*string_1 > *string_2) {
            return 1;
        }

        if (*string_2 > *string_1) {
            return -1;
        }

        string_1++;
        string_2++;
    }
    /*If the while loop ends (i.e., string_1 ends) before string_2 ends,
    string_2 is greater.*/
    if (*string_2 != '\0') {
        return -2;
    }

    return 0;
}


bool IsSuffixInDict(char *str, char *dict[], int n) {
    char flipped_str[MAX_WORD_LEN + 1];
    FlipString(str, flipped_str, n);

    int low = 0, high = n, mid, ret;
    while (low <= high) {
        mid = low + (high - low)/2;
        ret = StringCompare(str, *(dict + mid));
        printf("RET: %d\n", ret);
        if (ret == 2 || ret == 0) {
            return true;
        }

        if (ret <= -1) {
            low = mid + 1;
        }

        if (ret == 1) {
            high = mid - 1;
        }
    }

    return false;
}
