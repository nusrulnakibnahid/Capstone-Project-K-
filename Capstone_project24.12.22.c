#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

struct Player_info{
    char name[20];
    int id[11];
    int games;
    int hscore;
    int flag;
}player[1000], log;
   

void filesave();
void fileload();
int login();
int menu1();
int menu2();
void menu3(int i);
void leaderboard();
int easy();
int med();
int hard();
void result(int score, int entry, int diff);

int main(){
    fileload();
    int choice, diff, score, entry;

    point_a:
    entry=login();
    menu:
        choice=menu1();
        if(choice==1){
            diff=menu2();
            if(diff==4)
                goto menu;

            else if(diff==1){
                score=easy();
                player[entry].games++;
                score*=1;
                result(score, entry, diff);
                goto menu;
            }
            else if(diff==2){
                score=med();
                player[entry].games++;
                score*=2;
                result(score, entry, diff);
                goto menu;
            }
            else if(diff==3){
                score=hard();
                player[entry].games++;
                score*=3;
                result(score, entry, diff);
                goto menu;
            }

        }
        else if(choice==2){
            leaderboard();
            goto menu;
        }
        else if(choice==3){
            menu3(entry);
            getchar();
            filesave();
            goto point_a;
        }
        else if(choice==5){
            getchar();
            goto point_a;
        }
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t  Do you really want to Quit Quiz Game?");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t 1 -> Yes");
    printf("\n\t\t\t\t\t 2 -> No");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t: ");
    scanf("%d", &choice);
    if(choice==2){
        system("cls");
        goto menu;
    }

    filesave();

    return 0;
}

int login(){
    int i;
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t\t        WELCOME TO THE QUIZ GAME ");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t\t  PLEASE LOGIN FIRST");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tName: ");
    gets(log.name);
    printf("\t\t\t\t\tID: ");
    gets(log.id);
    printf("\t\t\t\t\t________________________________________");

    printf("\n\t\t\t\t\tLogging in.");
    system("cls");
    for(i=0; i<1000; i++){
        if(strcmp(log.name, player[i].name)==0){
            strcpy(player[i].id, log.id);
            return i;
        }
    }
    printf(".");
    for(i=0; i<1000; i++){
        if(player[i].flag==0){
            player[i].flag=1;
            strcpy(player[i].name, log.name);
            strcpy(player[i].id, log.id);
            return i;
        }
    }
    printf(".");
}

int menu1(){
    int input;
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t\t        WELCOME ");
    printf("\n\t\t\t\t\t\t          TO ");
    printf("\n\t\t\t\t\t\t       QUIZ GAME ");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t 1 -> Start the game");
    printf("\n\t\t\t\t\t 2 -> Leaderboard  ");
    printf("\n\t\t\t\t\t 3 -> Remove your info");
    printf("\n\t\t\t\t\t 4 -> Quit            \n");
    printf("\n\t\t\t\t\t 5 -> Log Out           ");
    printf("\n\t\t\t\t\t________________________________________\n\n");
    printf("\t\t\t\t\t: ");
    scanf("%d", &input);
    system("cls");
    return input;
}

int menu2(){
    int input;
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t\t        WELCOME ");
    printf("\n\t\t\t\t\t\t          TO ");
    printf("\n\t\t\t\t\t\t       QUIZ GAME ");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t\t   SELECT DIFFICULTY");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t 1 -> Easy");
    printf("\n\t\t\t\t\t 2 -> Medium");
    printf("\n\t\t\t\t\t 3 -> Hard\n");
    printf("\n\t\t\t\t\t 4 -> Main Menu           ");
    printf("\n\t\t\t\t\t________________________________________\n\n");
    printf("\t\t\t\t\t: ");
    scanf("%d", &input);
    system("cls");
    return input;
}

void menu3(int i){
    int input;
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t\tDo You Really Want to");
    printf("\n\t\t\t\t\t      Remove Your Informations?");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t 1 -> Yes");
    printf("\n\t\t\t\t\t 2 -> No");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t: ");
    scanf("%d", &input);

    if(input==1){
        player[i].flag=0;
        printf("\n\t\t\t\t\tDone!");
        sleep(1);
    }
    system("cls");
}

void fileload(){
    FILE*ptr;
    ptr=fopen("savefile.txt", "r");
    int i=0, j;
    for (i=0; i<1000; i++){
        player[i].flag=0;
        player[i].hscore=0;
        player[i].games=0;
    }
    i=0;
    while ((fscanf(ptr, "%s%s%d%d%d", player[i].name, player[i].id, &player[i].games, &player[i].hscore, &player[i].flag)) != EOF){
        for (j=0; player[i].name[j]!='\0'; j++)
            if (player[i].name[j]=='_')
                player[i].name[j]=' ';
        for (j=0; player[i].id[j]!='\0'; j++)
            if (player[i].id[j]=='_')
                player[i].id[j]=' ';
        i++;
    }
    fclose(ptr);
}

void filesave(){
    FILE*ptr;
    ptr=fopen("savefile.txt", "w");
    int i, j;
    for (i=0; i<1000; i++){
        for (j=0; player[i].name[j]!='\0'; j++)
            if (player[i].name[j]==' ')
                player[i].name[j]='_';
        for (j=0; player[i].id[j]!='\0'; j++)
            if (player[i].id[j]==' ')
                player[i].id[j]='_';
        if (player[i].flag==0)
            continue;
        fprintf(ptr, "%s\n", player[i].name);
        fprintf(ptr, "%d\n", player[i].id);
        fprintf(ptr, "%d\n", player[i].games);
        fprintf(ptr, "%d\n", player[i].hscore);
        fprintf(ptr, "%d\n", player[i].flag);
    }
    fclose(ptr);
}

void leaderboard(){
    int i;
    filesave();
    fileload();
    for(i=0; i<1000; i++){
        if(player[i].flag==1){
            printf("\n\t\t\t\t\t________________________________________");
            printf("\n\t\t\t\t\tPlayer Name\t: %s", player[i].name);
            printf("\n\t\t\t\t\tPlayer ID\t: %s", player[i].id);
            printf("\n\t\t\t\t\tGames Played\t: %d", player[i].games);
            printf("\n\t\t\t\t\tHigh Score\t: %d", player[i].hscore);
            printf("\n\t\t\t\t\t________________________________________");
        }
    }
            printf("\n\t\t\t\t\tPress Enter to continue...");
            getchar();
            getchar();
            system("cls");
}

void result(int score, int entry, int diff){
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tYou Got %d out of 10", score/diff);
    printf("\n\t\t\t\t\tYour score: %d", score);
    printf("\n\t\t\t\t\t________________________________________");
    if(score>player[entry].hscore){
        printf("\n\t\t\t\t\tCongratulations!");
        printf("\n\t\t\t\t\tYou've set a new High Score!");
        printf("\n\t\t\t\t\t________________________________________");
        player[entry].hscore=score;
    }
    printf("\n\t\t\t\t\tPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
}

int easy(){
    int score=0;
    int input[10], i=0;

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t1. C was developed in the year?\n");
    printf("\n\t\t\t\t\t1) 1970\t\t");
    printf("2) 1972\n");
    printf("\t\t\t\t\t3) 1986\t\t");
    printf("4) 1988");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==2){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 2) 1972");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t2.C language is available for which of ");
    printf("\n\t\t\t\t\tthe following operating system?\n");
    printf("\n\t\t\t\t\t1)DOS\t\t");
    printf("2)Windows");
    printf("\n\t\t\t\t\t3)Unix\t\t");
    printf("4)All of these");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 4)All of these ");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t3. Who invented the computer first? ");
    printf("\n\t\t\t\t\t1)Isaac Newton\t\t");
    printf("2)Charles Babbage");
    printf("\n\t\t\t\t\t3)albert einstein\t\t");
    printf("4)You");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==2){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 2)Charles Babbage");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t4. When was the Internet first invented? ");
    printf("\n\t\t\t\t\tdata type?\n");
    printf("\n\t\t\t\t\t1)January 1, 1983 \t\t");
    printf("2)July 1, 1990");
    printf("\n\t\t\t\t\t3)January 1, 1883\t\t\t");
    printf("4)January 19, 1500");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==1){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 1)January 1, 1983");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t5. Which of the following array token ");
    printf("\n\t\t\t\t\tis C?\n");
    printf("\n\t\t\t\t\t1)Keywords \t\t");
    printf("2)Variable");
    printf("\n\t\t\t\t\t3)Constant\t\t");
    printf("4)All of the above");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:4)All of the above");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t6. What is the largest canyon in the world? ");
    printf("\n\t\t\t\t\t1)Verdon Gorge,France\t\t");
    printf("2)King’s Canyon, Australia");
    printf("\n\t\t\t\t\t3)Canyon, Iceland\t\t");
    printf("4) Grand Canyon, USA");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:4) Grand Canyon, USA");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t7. How long is the border between the Bangladesh and India? ");
    printf("\n\t\t\t\t\trepresents increment?\n");
    printf("\n\t\t\t\t\t1)5,975-kilometre-\t\t");
    printf("2)4,096-kilometre");
    printf("\n\t\t\t\t\t3)7,468-kilometre\t\t");
    printf("4)4,500-kilometre-");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==2){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:2)4,096-kilometre");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t8. which year was Isaac Newton born? _\n");
    printf("\n\t\t\t\t\t1)1720\t\t");
    printf("\n\t\t\t\t\t2)1643");
    printf("\n\t\t\t\t\t3)1689\t\t");
    printf("\n\t\t\t\t\t4)1920");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==2){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:2)1643");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t9.Which year Stephen Hawking died? ");
    printf("\n\t\t\t\t\t1)2010\t\t");
    printf("\n\t\t\t\t\t2)2011");
    printf("\n\t\t\t\t\t3)2017\t\t");
    printf("\n\t\t\t\t\t4)2018");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:4)2018");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t10.How many alphabet in english _ \n");
    printf("\n\t\t\t\t\t1)29\t\t");
    printf("\n\t\t\t\t\t2)30");
    printf("\n\t\t\t\t\t3)26\t\t");
    printf("\n\t\t\t\t\t4)27");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==3){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:3)26");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    return score;
}

int med(){
    int score=0;
    int input[10], i=0;

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t1. 77+33=? ");
    printf("\n\t\t\t\t\t1)99\t");
    printf("\n\t\t\t\t\t2)90");
    printf("\n\t\t\t\t\t3)100");
    printf("\n\t\t\t\t\t4)110");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:4)110 ");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t2. When counting from 1–100, how many ");
    printf("\n\t\t\t\t\ttimes will you come across the number 7?");
    printf("\n\t\t\t\t\t1)17 \t\t");
    printf("2)18");
    printf("\n\t\t\t\t\t3)19 \t\t");
    printf("4)20");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:4)20 ");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t3.Which of these numbers is not prime? ");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)89\t\t");
    printf("2)127");
    printf("\n\t\t\t\t\t3)297 \t\t");
    printf("4)none");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==3){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 3)297 ");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t 4.X - =Y+1 ;means");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)x=x-y-1 \t\t");
    printf("2)X=x-y+1");
    printf("\n\t\t\t\t\t3)x=-x+y+1\t\t");
    printf("4)x=-x-y-1");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==1){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:1)x=x-y-1  ");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t5.The day before the day before yesterday  ");
    printf("\n\t\t\t\t\tis three days after Saturday. What day is ");
    printf("\n\t\t\t\t\it today? ");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)Monday\t\t\t");
    printf("2)Sunday");
    printf("\n\t\t\t\t\t3)Friday \t");
    printf("4)Wednesday");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==3){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:3)Friday");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t6.How many corners are there in a cube? ");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)4\t\t");
    printf("2)6");
    printf("\n\t\t\t\t\t3)7\t\t");
    printf("4)8");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:4)8");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t7.If 3 + 5 = 9 and 5 + 5 = 10, ");
    printf("\n\t\t\t\t\what does 3 equal? ");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)3\t");
    printf("2)4");
    printf("\n\t\t\t\t\t3)6\t\t");
    printf("4)9");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==2){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:2)4");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t8.Which number comes next in this pattern:3,4,7,11,18,_?\n");
    printf("\n\t\t\t\t\t1)13\t\t");
    printf("2)23");
    printf("\n\t\t\t\t\t3)29\t\t");
    printf("4)31");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==3){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:3)29");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t9.Book is to Reading as Fork is to: ");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)eating\t\t");
    printf("\n\t\t\t\t\t2)drawing");
    printf("\n\t\t\t\t\t3)writing\t\t");
    printf("\n\t\t\t\t\t4)All of the above");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==1){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:1)eating");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");




    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t10.Which of the following computer ");
    printf("\n\t\t\t\t\tlanguage is used for artificial ");
    printf("\n\t\t\t\t\tintelligence?\n");
    printf("\n\t\t\t\t\t1)FORTRAN\t");
    printf("2)PROLOG");
    printf("\n\t\t\t\t\t3)C\t\t");
    printf("4)COBOL");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==2){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:2)PROLOG");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    return score;
}

int hard(){
    int score=0;
    int input[10], i=0;

    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t1. What is the 16-bit compiler allowable ");
    printf("\n\t\t\t\t\trange for integer constants?\n");
    printf("\n\t\t\t\t\t1) -3.4e38 to 3.4e38\t\t");
    printf("\n\t\t\t\t\t2)-32767 to 32768 \n");
    printf("\t\t\t\t\t3)-32668 to 32667\t\t");
    printf("\n\t\t\t\t\t4)-32768 to 32767");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 4)-32768 to 32767");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t2.Which animal lays eggs? ");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)Dog ");
    printf("\n\n\t\t\t\t\t2)Cat ");
    printf("\n\n\t\t\t\t\t3)Duck ");
    printf("\n\n\t\t\t\t\t4)Sheep");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==3){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 3)Duck ");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t3.What is a lint?");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)C compiler\t\t");
    printf("\n\t\t\t\t\t2)Interactive debugger");
    printf("\n\t\t\t\t\t3)Analyzing tool \t");
    printf("\n\t\t\t\t\t4)C interpreter");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==3){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 3)Analyzing tool ");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t4.What is Earth’s only natural satellite? ");
    printf("\n\t\t\t\t\tfunction?");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)Sun \t\t");
    printf("\n\t\t\t\t\t2)Mars");
    printf("\n\t\t\t\t\t3)Venus\t\t");
    printf("\n\t\t\t\t\t4)Moon");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is: 4)Moon");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t5.In the C language, the constant is ");
    printf("\n\t\t\t\t\tdefined ___. ");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)Before main\t\t");
    printf("\n\t\t\t\t\t2)After main");
    printf("\n\t\t\t\t\t3)Anywhere, but starting on a new line. \t\t");
    printf("\n\t\t\t\t\t4)None of the these.");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==3){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:3)Anywhere, but starting on a new line.");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t6.Legs have feet and arms have ___. ");
    printf("\n\t\t\t\t\tconstruct that will always be executed ");
    printf("\n\t\t\t\t\tonce?");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)Ankles\t\t\t");
    printf("2)Pelvis");
    printf("\n\t\t\t\t\t3)Skull\t\t");
    printf("4)Hands");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==4){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:4)Hands");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t7.Which shape is a round?\n");
    printf("\n\t\t\t\t\t1)Circle\t\t");
    printf("2)Rectangle");
    printf("\n\t\t\t\t\t3)Square\t\t");
    printf("4)Triangle");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==1){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:1)Circle");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");





    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t8.Who invented the first ");
    printf("\n\t\t\t\t\tfunctional telephone? ");
    printf("\n\t\t\t\t\t1)Alexander Graham Bell\t\t");
    printf("\n\t\t\t\t\t2)Nikola Tesla");
    printf("\n\t\t\t\t\t3)Thomas Alva Edison\t\t");
    printf("\n\t\t\t\t\t4)Albert Einstein");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==1){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:1)Alexander Graham Bell");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");


    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t9.What is the name given to the ");
    printf("\n\t\t\t\t\tmolecular-scale computer?");
    printf("\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t1)Femtocomputer\t\t");
    printf("\n\t\t\t\t\t2)Nanocomputer");
    printf("\n\t\t\t\t\t3)Supercomputer\t\t");
    printf("\n\t\t\t\t\t4)Microcomputer");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==2){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:2)Nanocomputer");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");




    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\t10.What is the boiling point of water? ");
    printf("\n\t\t\t\t\t1)25°C\t\t");
    printf("\n\t\t\t\t\t2)100°C");
    printf("\n\t\t\t\t\t3)50°C\t\t");
    printf("\n\t\t\t\t\t4)All of the above");
    printf("\n\t\t\t\t\t________________________________________");
    printf("\n\t\t\t\t\tAns: ");
    scanf("%d", &input[i]);
    if(input[i]==2){
        score++;
        printf("\n\t\t\t\t\tCorrect Answer!");
    }
    else{
        printf("\n\t\t\t\t\tWrong Answer! Correct answer is:2)100°C");
        sleep(1);
    }
    i++;
    sleep(1);
    system("cls");

    return score;
}
