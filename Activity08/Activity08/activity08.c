#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
int main(void) {
    
    FILE* fp;
    fp = fopen("mytests3.txt", "w");
    fprintf(fp," เขียนทับ");

    fclose(fp);

    return 0;
}
*/

typedef struct
{
    char name[2021];
    int level;
    int score;
}player;

int main()
{
    player a[5];
    for (int i = 0; i < 5; i++)
    {
        strcpy(a[i].name, "Anonymous");
        a[i].level = i;
        a[i].score = 100 * i;
    }
    FILE* fp = fopen("activity7test.txt", "w");
    //fwrite(a, sizeof(a), 5, fp);
    
    
    for (int i = 0; i < 5;i++) {
        fprintf(fp, "name  :  %s \t",a[i].name);
        fprintf(fp, "level  :  %d \t", a[i].level);
        fprintf(fp, "score  :  %d\n", a[i].score);
 //       fprintf(fp,"\n");
    }
    

 
    
    fclose(fp);
    return 0;
}