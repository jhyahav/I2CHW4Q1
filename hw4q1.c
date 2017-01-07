
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
int StringCompare(char *string_1, char *string_2);
void MergeSuffixLists(char *list_1[], int len_1, char *list_2[], int len_2, char *merged_list[]);

int main()
{
    char *noun_suffixes[] = {"msi", "re", "sci", "ssen", "tnem", "tsi"};
    char *verb_suffixes[] = {"de", "eta", "ezi", "gni", "yfi"};
    char *adj_suffixes[] = {"elba", "evi", "hsi", "la", "luf", "suo"};

    char *nouns_and_verbs[N_NOUNS + N_VERBS];
    char *dict[N_SUFFIXES];
    char word[MAX_WORD_LEN + 1];
    scanf("%s", word);

    //int word_len = StringLength(word);

    MergeSuffixLists(noun_suffixes, N_NOUNS, verb_suffixes, N_VERBS, nouns_and_verbs);
    MergeSuffixLists(nouns_and_verbs, N_NOUNS + N_VERBS, adj_suffixes, N_ADJS, dict);

    for (int i = 0; i < N_SUFFIXES; i++) {
        printf("%s\n", *(dict + i));
    }

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


/*bool IsSuffixInDict(char *str, char *dict[], int n) {


    int low = 0, high = N_SUFFIXES, mid, ret;
    while low <= high {

        mid = low + (high - low)/2;
        ret = StringCompare(str, *(dict + mid));
        if (*(dict + mid) == *str) {
            return true;
        }

        if (*(dict + mid) < *str) {
            low = mid + 1;
        }

        if (*(dict + mid) > *str) {
            high = mid - 1;
        }
    }

    return false;
}
*/
