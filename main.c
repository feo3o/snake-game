#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <unistd.h>

//declare variables here
bool run = true;
short i, j;
short width = 30;
short heigth = 20;
int sX, sY;
int fX = 0;
int fY = 0;
short scoreboard;
short key;

void input()
{
    if (kbhit())
    {
        switch (getch())
        {
            case 'a':
            key = 1;
            break;
            case 's':
            key = 2;
            break;
            case 'd':
            key = 3;
            break;
            case 'w':
            key = 4;
            break;
            case 'l':
            run = false;
            break;
            default:
            break;
        }
    }
}

void read_input()
{
    if (key == 1)
    {
        sX--;
    }
    else if (key == 2)
    {
        sY++;
    }
    else if (key == 3)
    {
        sX++;
    }
    else if (key == 4)
    {
        sY--;
    }
}

void generate_fruit()
{
    //generate fruit
    label1:
    fX = rand() % 30;
    if (fX == 0)
    {
        goto label1;
    }
    label2:
    fY = rand() % 20;
    if (fY == 0)
    {
        goto label2;
    }
}

void entities()
{
    scoreboard = 0;

    //center snake
    sX = width / 2;
    sY = heigth / 2;

    generate_fruit();
}

void rule()
{
    //snake and fruit interaction
    if (sX == fX && sY == fY)
    {   
        scoreboard++;
        generate_fruit();
    }

    //snake and wall interaction
    if (sX < 0 || sX > width || sY < 0 || sY > heigth)
    {
        run = false;
    }
}

void screen()
{   
    printf("\e[?25l");
    system("cls");
    printf("           Score: %d\n", scoreboard);
    for (i = 0; i < heigth; i++)
    {
        for (j = 0; j < width; j++)
        {
            if(i == 0 || i == heigth - 1 || j == 0 || j == width - 1)
            {
                printf("#");
            }
            else
            {
                if (i == fY &&  j == fX)
                {
                    printf("*");
                }
                else if (i == sY && j == sX)
                {
                    printf("S");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("\nPress \"L\" to leave");
}

void main()
{
    entities();
    while (run)
    { 
        sleep(0.05);
        rule();
        input();
        read_input();
        screen();  
    }
    if (run == false)
    {
        system("cls");
        printf("\nGAMEOVER");
        printf("\n");
    }
}