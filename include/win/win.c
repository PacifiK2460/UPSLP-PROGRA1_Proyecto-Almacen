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

  setlocale(LC_ALL, "en_US.UTF-8");
}

void newWin(WINDOW* Window, int y, int x, int COLS, int ROWS, WINDOW* Parent){
  Window->X = x;
  Window->Y = y;
  Window->COLS = COLS;
  Window->ROWS = ROWS;
}

void winprint(int X, int Y, wchar_t* text, wchar_t* mode){
  printf("\x1B[%i;%iH%ls%ls%ls",X,Y,mode,text,RESET);
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

void printinthemiddle(WINDOW* Window, int Y, wchar_t* texto,wchar_t* mode){
  int X;
  int tam = wcslen(texto);
  if(Window == STDOUTPUT){
    X = getcols(Window);
  } else {
    X = Window->COLS;
  }
  X = X - tam;
  X = X / 2;
  Y+=1;
  winprint(Y,X,texto,mode);
}

void box(WINDOW* Window, wchar_t* mode){
  int X = 0, Y = 0,COLS = 0,ROWS = 0;
  
  if(Window != STDOUTPUT){
    X += Window->X;
    Y += Window->Y;
  };

  getcolsrows(Window,&COLS,&ROWS);
  for(int i = 0; i < COLS; i++) winprint(X,i + Y,L"─", mode);
  for(int i = 0; i < COLS; i++) winprint(ROWS + X,i + Y,L"─", mode);

  for(int i = 0; i < COLS; i++) winprint(i + X,Y,L"│",mode);
  for(int i = 0; i < COLS; i++) winprint(i + X,COLS + Y,L"│",mode);

  // Imprimimos las esquinas
  winprint(X,Y, L"┌",mode);        //IZQ SUP
  winprint(X, Y + COLS, L"┐",mode);    //IZQ INF
  winprint(X + ROWS, Y, L"└",mode);    //DER SUP
  winprint(X + ROWS, Y + COLS, L"┘",mode); //DER INF

}