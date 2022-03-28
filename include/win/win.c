#include "../win.h"

struct WINDOW
{
  int X;
  int Y;
  int COLS;
  int ROWS;

  WINDOW* Parent;
};

void innit(){
  #ifdef _WIN32
    setConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING); 
  #endif

  setlocale(LC_ALL, "");
}

WINDOW* newWin(int y, int x, int COLS, int ROWS, WINDOW* Parent){
  WINDOW* Window = (struct WINDOW*)calloc(1,sizeof(struct WINDOW));
  Window->X = x;
  Window->Y = y;
  Window->COLS = COLS;
  Window->ROWS = ROWS;
  return Window;
}

void winprint(WINDOW* window,int X, int Y, char* text, char* mode){
  X+= getx(window);
  Y+= gety(window);
  printf("\x1B[%i;%iH%s%s%s",Y,X,mode,text,RESET);
}

void getcolsrows(WINDOW* Window, int* COLS, int* ROWS){
  if(Window == STDOUTPUT){
    #ifdef _WIN32
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      COLS = csbi.srWindow.Bottom - (int)csbi.srWindow.Top + 1;
      ROWS = csbi.srWindow.Right - (int)csbi.srWindow.Left + 1;
    #endif

    #ifdef __linux__
      struct winsize w;
      ioctl(1, 0x5413, &w);

      *COLS = (int) w.ws_col;
      *ROWS = (int) w.ws_row;
    #endif
    return;
  }

  *COLS = Window->COLS;
  *ROWS = Window->ROWS;
  return;
}

int getcols(WINDOW* Window){
  if(Window == STDOUTPUT){
    #ifdef _WIN32
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      return csbi.srWindow.Bottom - (int)csbi.srWindow.Top + 1;
    #endif

    #ifdef __linux__
      struct winsize w;
      ioctl(1, 0x5413, &w);

      return (int) w.ws_col;
    #endif
  }

  return Window->COLS;
}

int getrows(WINDOW* Window){
  if(Window == STDOUTPUT){
    #ifdef _WIN32
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      return csbi.srWindow.Right - (int)csbi.srWindow.Left + 1;
    #endif

    #ifdef __linux__
      struct winsize w;
      ioctl(1, 0x5413, &w);

      return (int) w.ws_row;
    #endif
  }
  return Window->ROWS;
}

void getxy(WINDOW* Window, int* X, int* Y){
  if(Window == STDOUTPUT){
    X = 0;
    Y = 0;
    return;
  }

  *X = Window->X;
  *Y = Window->Y;
}

int getx(WINDOW* Window){
  if(Window == STDOUTPUT){
    return 0;
  }

  return Window->X;
}

int gety(WINDOW* Window){
  if(Window == STDOUTPUT){
    return 0;
  }

  return Window->Y;
}

void printinthemiddle(WINDOW* Window, int Y, char* texto,char* mode){
  int X = getcols(Window);
  int tam = strlen(texto);
  X = X - tam;
  X = X / 2;
  Y+=1;
  winprint(Window,X,Y,texto,mode);
}
void printinthemiddlesize(WINDOW* Window, int Y, char* texto,char* mode, int tam){
  int X = getcols(Window);
  X = X - tam;
  X = X / 2;
  Y+=1;
  winprint(Window,X,Y,texto,mode);
}

void box(WINDOW* Window, char* mode){
  // int X = getx(Window);
  // int Y = gety(Window);
  int COLS = getcols(Window);
  int ROWS = getrows(Window);

  for(int i = 0; i < COLS; i++) winprint(Window,0 + i,0,"─", mode);
  for(int i = 0; i < COLS; i++) winprint(Window,0 + i,0 + ROWS,"─", mode);

  for(int i = 0; i < ROWS; i++) winprint(Window,0,0 + i,"│",mode);
  for(int i = 0; i < ROWS; i++) winprint(Window,0 + COLS,0 + i,"│",mode);

  // Imprimimos las esquinas
  winprint(Window,0,0, "┌",mode);        //IZQ SUP
  winprint(Window,0 + COLS, 0, "┐",mode);    //IZQ INF
  winprint(Window,0, 0 + ROWS, "└",mode);    //DER SUP
  winprint(Window,0 + COLS, 0 + ROWS, "┘",mode); //DER INF

}