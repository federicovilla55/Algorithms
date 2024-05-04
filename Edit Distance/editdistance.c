#include <stdio.h>
#include <string.h>
#include<math.h>

int min(int a, int b, int c) {
    int min = (a < b) ? a : b;
    return (min < c) ? min : c;
}

int editDistance(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = min(dp[i - 1][j - 1], 1 + dp[i - 1][j], 1 + dp[i][j - 1]);
            else
                dp[i][j] = min(1+dp[i - 1][j], 1+dp[i][j - 1], 1+dp[i - 1][j - 1]);
        }
    }
    return dp[m][n];
}

int weightedEditDistance(char *str1, char *str2, int matchScore, int mismatchScore, int gapScore) {
    int m = strlen(str1);
    int n = strlen(str2);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = min(matchScore+dp[i - 1][j - 1], gapScore+dp[i - 1][j], gapScore+dp[i][j - 1]);
            else
                dp[i][j] = min(gapScore+dp[i - 1][j], gapScore+dp[i][j - 1], mismatchScore+dp[i - 1][j - 1]);
        }
    }
    return dp[m][n];
}


int main(){
    printf("Edit distance is: %d\n", editDistance("kitten", "sitting"));

    printf("Edit distance is: %d\n", weightedEditDistance("peterpan", "noeternit", -1, 1, 2));

    printf("Edit distance is: %d\n", editDistance("sunday", "saturday"));
}