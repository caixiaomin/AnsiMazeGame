//
//  main.c
//  pj_lauracai
//
//  Created by Laura on 2024/10/13.
//

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 21
#define MAX 101

static struct termios stored_settings0;
static struct termios stored_settings1;
bool isFinished = false;
int step=0,Tnum=0;
char trace[MAX];
bool t_history[MAX][MAX]={0};
int maze1[15][15]={
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 3, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};
int maze2[SIZE][SIZE]={
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1, 2, 2, 0, 1, 0, 0, 0, 0, 2, 0, 2, 0, 0, 1,
    1, 1, 1, 1, 1, 0, 1, 0, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 2, 0, 1, 0, 0, 2, 1, 0, 0, 2, 0, 0, 1, 0, 0, 2, 1, 0, 1,
    1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 0, 1,
    1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 2, 0, 0, 1, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 0, 0, 1, 0, 1, 2, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1,
    1, 0, 1, 0, 1, 3, 1, 0, 0, 2, 1, 0, 1, 0, 0, 0, 1, 0, 1, 2, 1,
    1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 1, 1, 1, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 2, 2, 1, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};
void clearScreen(void);

void initKeyPress(void) {//启用非icanon输入，不需要回车和等待时间就可以交互
    struct termios new_settings;
    tcgetattr(0,&stored_settings0);
    new_settings=stored_settings0;
    new_settings.c_lflag&=(~ICANON);
    new_settings.c_cc[VTIME]=0;
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0,TCSANOW,&new_settings);
    stored_settings1 = new_settings;
}
void enterInteractMode(void) {
    tcsetattr(0,TCSANOW,&stored_settings1);
}
void enterLegacyMode(void) {
    tcsetattr(0,TCSANOW,&stored_settings0);
}
void printMaze(int heroRow,int heroCol) {
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            if(i==heroRow&&j==heroCol) {//确保小黄置于顶层
                printf("\033[40;31mY ");
            } else {
                switch(maze2[i][j]) {
                    case 1:printf("\033[40;37mW ");break;
                    case 0:printf("\033[40;37m  ");break;
                    case 2:printf("\033[40;32mD ");break;
                    case 3:printf("\033[40;34mT ");break;
                }
            }
        }
        printf("\n");
    }
}
void moveHero(char direction,int *heroRow,int *heroCol) {
    int newRow=*heroRow;
    int newCol=*heroCol;
    switch(direction) {
        case 'W':newRow--;trace[step++]='U';break;
        case 'A':newCol--;trace[step++]='L';break;
        case 'S':newRow++;trace[step++]='D';break;
        case 'D':newCol++;trace[step++]='R';break;
        default:printf("输入错误，请重新输入");
    }
    if(maze2[newRow][newCol]==3&&!t_history[newRow][newCol]){
        Tnum++;
        t_history[newRow][newCol]=1;
    }
    if(newRow>=0&&newRow<SIZE&&newCol>=0&&newCol<SIZE&&maze2[newRow][newCol]!=1) {
        *heroRow=newRow;
        *heroCol=newCol;
    }
}
void settlement(void){
    int i;
    isFinished = true;
    clearScreen();

    printf("\n行动路径: ");
    for(i=0;i<step;i++)printf("%c",trace[i]);
    printf("\n消耗的体力: ");
    printf("\n找到的宝箱数量: ");
    printf("%d",Tnum);
}
void maze2_mode1(void) {//实时模式
    int heroRow=1,heroCol=1;Tnum=0;step=0;
    char input;
    enterInteractMode();
    while(1) {
        
        clearScreen();

        printMaze(heroRow,heroCol);
        printf("请输入WASD控制Y移动，Q退出：");
        input=getchar();
        input=toupper(input);
        if(input=='Q'){
            printf("用户选择退出。进入结算\n");
            settlement();
            return;
        }
        if(Tnum==2){
            printf("恭喜找到所有宝藏！进入结算\n");
            settlement();
            return;
        }
        moveHero(input,&heroRow,&heroCol);
    }
}

void maze2_mode2(void) {//编程模式
    int heroRow=1,heroCol=1,i;Tnum=0;step=0;
    char input[100];
    printMaze(heroRow,heroCol);
    int n;//编程模式下一次性输入的指令的长度
    while(1){
        clearScreen();
        printMaze(heroRow,heroCol);
        enterLegacyMode();
        printf("请一次性输入您的指令（WSAD对应上下左右，Q退出），回车结束");
        fgets(input, sizeof(input), stdin);
        n=(int)strlen(input);
        //printf("%s\n",input);
        for(i=0;i<n;i++){
            char x=toupper(input[i]);
            if(x=='Q'){
                printf("用户选择退出。进入结算\n");
                settlement();return;
            }
            if(x!='W'&&x!='A'&&x!='S'&&x!='D'){
                printf("输入有误。进入结算\n");
                settlement();
                return;
            }
            //printf("%d*\n",Tnum);
            
            if(Tnum==2){
                printf("恭喜找到所有宝藏！进入结算\n");
                settlement();
                return;
            }
            moveHero(x,&heroRow,&heroCol);
            clearScreen();
            printMaze(heroRow,heroCol);
            sleep(1);
        }
    }
}
 
void clearScreen(void) {
    printf("\033[H\033[J");
}

int main(void) {
    char move;
    int y=0;
    initKeyPress();
    while(1) {
        enterInteractMode();
        clearScreen();
        printf("\033[%d;%dH>",y+1,1);
        printf("\033[1;4H开始第一关");
        printf("\033[2;4H开始第二关");
        printf("\033[3;4H退出");
        printf("\033[5;1HW,S控制光标上下移动，回车键进入下级菜单。");
        move=getchar();
        if(move=='Q'||move=='q')break;
        if((move=='W'||move=='w')&&y>0)y--;
        if((move=='S'||move=='s')&&y<2)y++;
        if(move=='\n'||move=='\t') {
            if(y==1) {
                while(1){
                    isFinished = false;
                    enterInteractMode();
                    clearScreen();
                    printf("\033[%d;%dH>",y+1,1);
                    printf("\033[1;4H 0:实时模式");
                    printf("\033[2;4H 1:编程模式");
                    printf("\033[3;4H 退出");
                    printf("\033[5;1HW,S 控制方法：按W向上移动，按S向下移动，按<Enter>选择。");
                    move=getchar();
                    if(move=='Q'||move=='q')break;
                    if((move=='W'||move=='w')&&y>0)y--;
                    if((move=='S'||move=='s')&&y<2)y++;
                    if(move=='\n'||move=='\t') {
                        if(y==0)maze2_mode1();
                        if(y==1)maze2_mode2();
                        if(y==2)break;
                    }
                    enterInteractMode();
                    if (isFinished) {
                        printf("\npress any key to continue...\n");
                        getchar();
                    }
                }
                
            } else if(y==2) {
                break;
            }
        }
        //move=toupper(move);
    }
    enterLegacyMode();
    return 0;
}

/*
while(1) {
    printMaze(heroRow,heroCol);
    printf("请输入WASD控制Y移动，Q退出：");
    input=getchar();
    input=toupper(input);
    if(input=='Q')break;
    moveHero(input,&heroRow,&heroCol);
    printf("\033[H\033[J");
}
//reset_keypress();
}*/

