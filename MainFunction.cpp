#include "MainFunction.h"

void gotoXY(int x, int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

void clearScreen()
{
    //cout << "\033[2J\033[1;1H";
    system("clear");
}

char getch()
{
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
   
    return buf;
 }

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

void delay(long miliseconds)
{
    long milli_time;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    while (1==1)
    {
        struct timeval end_time;
        gettimeofday(&end_time, NULL);

        gotoXY(1,1);
        cout << "";

        long seconds = end_time.tv_sec - start_time.tv_sec; //seconds
        long useconds = end_time.tv_usec - start_time.tv_usec; //milliseconds
        milli_time = ((seconds) * 1000 + useconds/1000.0);

        if (milli_time >= miliseconds) break;
    }
}

void playMusic(string path)
{
    g_chunk = Mix_LoadWAV(path.c_str());
    Mix_PlayChannel( -1, g_chunk, 0 );
}