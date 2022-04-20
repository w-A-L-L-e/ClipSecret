/*=============================================================================
 File         : clips.cpp
 Author       : Walter Schreppers
 Description  : Little program with ncurses to show a pincode and 
                copy a secret to clipboard.
                Easy for re-entering long passes during a day.
=============================================================================*/
#include <iostream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include "secrets.h"

std::string exec( const std::string& command ){
  FILE *pstream;
  pstream = popen( command.c_str(), "r" );
  if( !pstream ) return "ERROR in command";

  std::string result;
  char buf[100];

  while( fgets(buf, sizeof(buf), pstream) !=NULL){
    result += buf;
  }
  pclose(pstream);

  return result;
}


std::string paste()
{
  return exec("pbpaste");
}

std::string copy_to_clipboard(const std::string& new_clipboard)
{
  std::stringstream cmd;
  cmd << "printf \"" << new_clipboard << "\" | pbcopy";
  return exec(cmd.str().c_str());
}

int main(){
  std::string input;
  int row, col;


  initscr(); // init curses
  getmaxyx(stdscr,row,col); // get screen size

  std::string msg="Secret?";
  int centerx = ( col - msg.length() )/2;
  mvprintw(row/2, centerx, msg.c_str());
  mvprintw(row/2+1, centerx-1, " ");
  noecho();
  refresh();

  int c = getch(); // wait user input
  while(c != 10){  // while not ENTER pressed = ascii 10
    input+=(char)c;
    mvprintw(row/2+1, centerx-1+input.length(), "*");
    c=getch();
    refresh();
  }

  if(input==pincode()){
    copy_to_clipboard(secret());

    int erase_count = 10;
    while(erase_count-- > 0){
      sleep(1);
      std::stringstream erase_msg;
      erase_msg<<"erasing in "<<erase_count<<" seconds...";
      mvprintw(row/2+1, centerx, erase_msg.str().c_str());
      refresh();
    }
  }

  endwin(); // end curses mode
  copy_to_clipboard("");

  return 0;
}


