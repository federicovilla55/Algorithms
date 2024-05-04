#include <stdio.h>
#include <string.h>

int hammingDistance(char *str1, char *str2) {
    if(strlen(str1) != strlen(str2)){
        printf("Error: given strings have different length.\n");
        return -1;
    }

    int distance = 0;

    for (int i = 0; i < strlen(str1); i++) {
        if (str1[i] != str2[i]) {
            distance++;
        }
    }

    return distance;
}

int main(){
    char* word1 = "karolin";
    char* word2 = "kathrin";

    int hd = hammingDistance(word1, word2);

    if(hd != -1){
        printf("Hamming distance of the strings is: %d\n", hd);   
    }
}