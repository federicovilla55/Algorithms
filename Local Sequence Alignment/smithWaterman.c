#include <stdio.h>
#include <string.h>

int maxZero(int a, int b, int c) {
    int max = (a > b) ? a : b;
    max = (max > c) ? max : c;
    return (max < 0) ? 0 : max;
}

int SmithWatermanAlgorithm(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    int dp[m + 1][n + 1];
    int result = 0;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = maxZero(dp[i - 1][j - 1], 1 + dp[i - 1][j], 1 + dp[i][j - 1]);
            else
                dp[i][j] = maxZero(1+dp[i - 1][j], 1+dp[i][j - 1], 1+dp[i - 1][j - 1]);
            
            result = (result > dp[i][j]) ? result : dp[i][j];
        }
    }
    return result;
}

int weightedSmithWatermanAlgorithm(char *str1, char *str2, int matchScore, int mismatchPenalty, int gapPenalty) {
    int m = strlen(str1);
    int n = strlen(str2);
    int dp[m + 1][n + 1];
    int result = 0;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = 0;
            else if (j == 0)
                dp[i][j] = 0;
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = maxZero(matchScore+dp[i - 1][j - 1], gapPenalty+dp[i - 1][j], gapPenalty+dp[i][j - 1]);
            else
                dp[i][j] = maxZero(gapPenalty+dp[i - 1][j], gapPenalty+dp[i][j - 1], mismatchPenalty+dp[i - 1][j - 1]);

            result = (result > dp[i][j]) ? result : dp[i][j];
        }
    }
    return result;
}


int main(){
    printf("Local sequence alignment: %d\n", weightedSmithWatermanAlgorithm("desperate", "asparagus", 1, -1, -2));

    printf("Local sequence alignment: %d\n", weightedSmithWatermanAlgorithm("AGCTTAGTTA", "CGTTATTAG", 1, -1, -2));
} 