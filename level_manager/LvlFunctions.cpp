#include "LvlManager.h"
#include <iostream>
#include <experimental/algorithm>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>

  using namespace std;

lvlMan::lvlMan(int numLvls) // Custom game constructor 
{
  for (int i = 1; i < numLvls; i++) // Create the list of levels from given variable
  {
    Puzzle.push_back(i);
  }

  gameSize = Puzzle.size();
}

lvlMan::lvlMan() // Default game constructor
{
  Puzzle = {1, 2, 3, 4, 5};

  gameSize = Puzzle.size();
}

lvlMan::~lvlMan(){}

int lvlMan::selectRandomLvl()
{
  vector<int> out;
  size_t nelems = 1;
  experimental::sample(Puzzle.begin(), Puzzle.end(), back_inserter(out), nelems, std::mt19937{std::random_device{}()});

  int rando = out.front();

  // deletes the level from the vector
  Puzzle.erase(remove(Puzzle.begin(), Puzzle.end(), rando), Puzzle.end());

  return rando;
}

bool lvlMan::puzzleCall(int lvl)
{
  string lvlCall = "./level_manager/startEndLvl.sh " + to_string(lvl);
  sleep(2);
  system(lvlCall.c_str());

  return true;
}

void lvlMan::finalLevelCall()
{
  sleep(2);
  system("clear");
  system("./level_manager/final_level/code_entry.py");
}

void lvlMan::getExitCode()
{
  srand(time(NULL)); // set random seed 
  int codeNum = (rand() % 10); // get random number from 0 - 9
  ofstream exitCodeFile;
  exitCodeFile.open("level_manager/final_code.txt", ios_base::app);
  exitCodeFile << codeNum; // append random number to exit code file
  exitCodeFile.close();

  exitCodeFile.open("level_manager/notePad.txt", ios_base::app);
  exitCodeFile << endl << "Exit code digit: " << codeNum << endl; // append random number to players notepad
  exitCodeFile.close();
}
