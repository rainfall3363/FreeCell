#ifndef FREECELL_MAIN_H
#define FREECELL_MAIN_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <algorithm>
#include <cstdlib>

#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#define sleep(x) Sleep(x * 1000)
#define system("clear") system("cls")
#endif

#define RED 1
#define BLACK 2
#define BOARD_WIDTH 33
#define BOARD_HEIGHT 20
#define FREECELL_SIZE 4
#define HOMECELL_SIZE 4
#define CASCADES_SIZE 8
#define CARD_AMOUNT 52

using namespace std;

#include "FreeCell_Component.h"
#include "FreeCell_UI.h"


#endif