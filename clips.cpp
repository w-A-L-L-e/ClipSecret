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


int row, col, centerx;

std::string run( const std::string& command ){
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
  return run("pbpaste");
}

std::string copy_to_clipboard(const std::string& new_clipboard)
{
  std::stringstream cmd;
  cmd << "printf \"" << new_clipboard << "\" | pbcopy";
  return run(cmd.str().c_str());
}

void erase_clipboard(int sec){
  while(--sec > 0){
    std::stringstream erase_msg;
    erase_msg << "erasing in " << sec << " seconds...";
    mvprintw(row/2+1, centerx, erase_msg.str().c_str());
    refresh();
    sleep(1);
  }
  copy_to_clipboard("");
}

void print_center(const std::string& msg){
  getmaxyx(stdscr,row,col); // get screen size
  centerx = ( col - msg.length() )/2;
  mvprintw(row/2, centerx, msg.c_str());
  move(row/2+1, centerx);
  refresh();
}

void print_status(const std::string& msg){
  mvprintw(row/2+1, centerx, msg.c_str());
  refresh();
}



std::string read_pin(){
  std::string input = "";
  int c = getch(); // wait user input
  while(c != 10){  // while not ENTER pressed = ascii 10
    input+=(char)c;
    mvprintw(row/2+1, centerx-1+input.length(), "*");
    c=getch();
    refresh();
  }

  // clear input line
  move(row/2+1,0);
  clrtoeol();
  move(row/2+1, centerx);
  refresh();
 
  return input;
}

void self_destruct(const std::string exe_name){
  run("rm ~/bin/clips");
  print_status("Self destructing...");
  usleep(500000);
}

int main(int argc, char* argv[]){
  std::string input;
  initscr(); // init curses
  noecho();

  print_center("Secret?");
  
  int allowed_retries = 3;
  while(allowed_retries >= 0){
    input = read_pin();
    
    if(input==pincode()){
      copy_to_clipboard(secret());
      erase_clipboard(10);
      break;
    }

    if(--allowed_retries <= 0){
      self_destruct(argv[0]);
      break;
    }
  }
  endwin(); // end curses mode

  return 0;
}


