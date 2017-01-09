
#include <stdio.h>
#include <stdbool.h>

#define MAX_WORD_LEN 32
#define N_NOUNS 6
#define N_VERBS 5
#define N_ADJS 6
#define N_SUFFIXES (N_NOUNS + N_VERBS + N_ADJS)

bool IsSuffixInDict(char *str, char *dict[], int n);
int StringLength(char *str);
void ConvertToLowercase(char *string);
void RemoveNonLetters(char *string_ptr);
void CopyString(char *source, char *destination);
void DeleteChar(char *string);
int WordCompare(char *flipped_word, char *suffix);
void MergeSuffixLists(char *list_1[], int len_1, char *list_2[], int len_2, char *merged_list[]);
void FlipString(char *orig_str, char *flipped_str, int str_len);

int main()
{
    char *noun_suffixes[] = {"msi", "re", "sci", "ssen", "tnem", "tsi"};
    //char *verb_suffixes[] = {"de", "eta", "ezi", "gni", "yfi"};
    //char *adj_suffixes[] = {"elba", "evi", "hsi", "la", "luf", "suo"};

    char word[MAX_WORD_LEN + 1], flipped_word[MAX_WORD_LEN + 1];
    scanf("%s", word);

    //int word_len = StringLength(word);

    ConvertToLowercase(word);
    RemoveNonLetters(word);
    FlipString(word, flipped_word, StringLength(word));

    printf("%s\n", flipped_word);

    int ret = IsSuffixInDict(flipped_word, noun_suffixes, 1);

    printf("%d\n", ret);

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

void ConvertToLowercase(char *string) {
    while (*string != '\0') {
        if (*string >= 'A' && *string <= 'Z') {
            char temp = *string;
            temp += ('z' - 'Z');
            *string = temp;
        }

        string++;
    }
}

void RemoveNonLetters(char *string) {
    while (*string != '\0') {
        if ((*string > 'z' || *string < 'a') && (*string != '.' )) {
            DeleteChar(string);
        } else {
            string++;
        }
    }
}


void DeleteChar(char *string) {
    for (char *temp_ptr = string; *temp_ptr != '\0'; temp_ptr++) {
        *temp_ptr = *(temp_ptr + 1);
    }
}

void FlipString(char *orig_str, char *flipped_str, int str_len) {
    for (int i = str_len; i > 0; i--) {
        *(flipped_str + (str_len - i)) = *(orig_str + i - 1);
    }
    *(flipped_str + str_len) = '\0';
}

/*void CopyString(char *source, char *destination) {
    if (source != NULL && destination != NULL) {
        while (*source != '\0') {
            *(destination++) = *(source++);
        }
    }
}*/


void MergeSuffixLists(char *list_1[], int len_1, char *list_2[], int len_2, char *merged_list[]) {
    int ia, ib, ic, comp_return_val;
    ia = ib = ic = 0;
    for (ia = ib = ic = 0; ia < len_1 && ib < len_2; ic++) {
        comp_return_val = WordCompare(*(list_1 + ia), *(list_2 + ib));
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


int WordCompare(char *flipped_word, char *suffix) {
    RemoveNonLetters(flipped_word);
    RemoveNonLetters(suffix);


    while (*flipped_word != '\0') {
        if (*suffix == '\0') {
            return 2;
        }

        if (*flipped_word > *suffix) {
            return 1;
        }

        if (*suffix > *flipped_word) {
            return -1;
        }

        flipped_word++;
        suffix++;
    }
    /*If the while loop ends (i.e., string_1 ends) before suffix ends,
    suffix is greater.*/
    if (*suffix != '\0') {
        return -2;
    }

    return 0;
}

//N is dict length
bool IsSuffixInDict(char *str, char *dict[], int n) {
    n = N_NOUNS;
    //int str_len = StringLength(str);
    int low = 0, high = n, mid, ret;

    while (low <= high) {

        mid = low + (high - low)/2;
        ret = WordCompare(str, *(dict + mid));
        if (ret == 0 || ret == 2) {
            return true;
        }

        if (ret == 1) {
            low = mid + 1;
        }

        if (ret == -1 || ret == -2) {
            high = mid - 1;
        }
    }

    return false;
}

