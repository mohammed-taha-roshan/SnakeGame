#include <string.h>
#include <stdio.h>  // for standard input output function
#include <conio.h>  // to use kbhit() function which tells a key is pressed or not
#include <stdlib.h> // to use rand() function which returns a random int when its called
#include <unistd.h> // to use sleep() function

int i, j, height = 30, width = 30;
int gameover, score;
int x, y, fruitx, fruity, flag;

void sort(int *s, int n)
{
    int index;
    for (int i = 0; i < n - 1; i++)
    {
        index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (s[index] > s[j])
            {
                index = j;
            }
        }
        int temp = s[i];
        s[i] = s[index];
        s[index] = temp;
    }

}

void display(int *s, int c, char names[c])
{
    FILE *ptr1;
    int z = 1;
    ptr1 = fopen("scoreboard.txt", "a");
    for (int i = c; i > 0; i--)
    {
        printf("POS:%d-NAME:%s-SCORE:%d \n", z, names[i], s[i]);
        fprintf(ptr1, "POS:%d-NAME:%s-SCORE:%d \n", z, names[i], s[i]);
        z++;
    }
}
void draw()
{
    system("cls");
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
            {
                printf("=");
            }
            else
            {
                if (i == x && j == y)
                {
                    printf(">"); // snake
                }

                else if (i == fruitx && j == fruity)
                {
                    printf("0"); // fruit
                }

                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

    printf("score = %d\n", score); // prints the score after the game ends
    printf("press X to quit the game");
}

// now writing a function to generate fruit randomly within the defined boundaries:-

void setup()
{
    gameover = 0;

    // to store height and width
    x = height / 2;
    y = width / 2;
label1:
    fruitx = rand() % 20;
    if (fruitx == 0)
    {
        goto label1;
    }

label2:
    fruity = rand() % 20;
    if (fruity == 0)
    {
        goto label2;
    }
    score = 0;
}

// making another function to take input from keyboard for movement of snake using W A S D X keys:-

void input()
{
    if (kbhit()) // kbhit is a inbuilt function of conio.h which checks if a key is pressed or not.
    {
        switch (getch())
        {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

// now making a function for logic like:-
// 1 Movement of snake
// For increasing score
// What happens when snake touches the boundary
// To exit the game
// Random generation of fruit if snakes eats

void logic()
{
    sleep(0.001);
    switch (flag)
    {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    // if the game is over then:-

    if (x < 0 || x > height || y < 0 || y > width)
    {
        gameover = 1;
    }

    // if the snake reaches the fruit then to increase the score by 10:-

    if (x == fruitx && y == fruity)
    {
    label3:
        fruitx = rand() % 25;
        if (fruitx == 0)
        {
            goto label3;
        }

        // after snake eats the fruit then to generate another furit at random position:-

    label4:
        fruity = rand() % 25;
        if (fruity == 0)
        {
            goto label4;
        }

        score += 10;
    }
}

int main()
{
    int c = 0;
    system("cls");
    char names[100][100];
    int s[5];
    printf("#####################################################################################\n");
    printf("#  ::         ::  ::::::::  ::        ::::::::  ::::::::  ::::    ::::  ::::::::    #\n");
    printf("#  ::   ...   ::  ::,,,,,,  ::        ::    **  ::    ::  :: ::  :: ::  ::,,,,,,    #\n");
    printf("#  ::  :: ::  ::  ::******  ::        ::    ..  ::    ::  ::   **   ::  ::******    #\n");
    printf("#  :::::   :::::  ::::::::  ::::::::  ::::::::  ::::::::  ::        ::  ::::::::    #\n");
    printf("#####################################################################################\n");

    char words[] = "YOU HAVE ENTERED THE SNAKE GAME.\n";
    char wrds[] = "SHALL WE BEGIN yes=1/no=0 :";
    for (int i = 0; i < strlen(words); i++)
    {
        usleep(100005);
        putchar(words[i]);
    }
    printf("\n");
    for (int i = 0; i < strlen(wrds); i++)
    {
        usleep(100005);
        putchar(wrds[i]);
    }
    int n;
    scanf("%d", &n);
    char m[100];

    while (n == 1)
    {
        int a;
        char q;

        printf("PLEASE ENTER YOUR NAME:");
        scanf("%s", names[c]);
        setup(); // to generate boundaries

        // now to run code until the game is over by using while loop:-

        while (!gameover)
        {
            draw();
            input();
            logic();
        }
        printf("\n");

        printf("NICE TRY:%d\n", score);

        printf("U WANNA CONTINUE? : ");
        scanf("%d", &n);
        a = score;
        FILE *ptr;
        ptr = fopen("3.txt", "a");
        fprintf(ptr, "THE SCORE OF %s IS %d\n", names[c], a);
        s[c] = a;
        c++;
        fclose(ptr);
    }
    for (int i = 0; i < c; i++)
    {
        printf("%s --> %d\n", names[i], s[i]);
    }
    int size = sizeof(s) / sizeof(int);
    sort(s, c);
   
    FILE *ptr1;
    int z = 1;
    ptr1 = fopen("scoreboard.txt", "a");
    for (int i = c - 1; i >= 0; i--)
    {
        printf("POS:%d-NAME:%s-SCORE:%d \n", z, names[i], s[i]);
        fprintf(ptr1, "POS:%d-NAME:%s-SCORE:%d \n", z, names[i], s[i]);
        z++;
    }
    for (int i = 0; i < c; i++)
    {
        printf("%s --> %d\n", names[i], s[i]);
    }
    fclose(ptr1);
}