#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char *argv[]){
        char new_char, original;
        int keyLen, i;

        if(argc == 3){

                keyLen = strlen(argv[2]);
                i = 0;

                printf("Result: ");
                for(i=0; argv[1][i]!='\0'; i++){
                        original = argv[1][i];

                        new_char = original ^ argv[2][i%keyLen];

                        if(isprint(original) && isprint(new_char))
                                putchar(new_char);
                        else
                                putchar(original);
                }
                printf("\n");
        }else{
                printf("-> Usage:\t ./xor  plaintext  key\n");
        }



        return 0;
}
