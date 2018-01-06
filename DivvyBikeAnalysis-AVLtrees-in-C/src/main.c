/*main.cpp*/
// Divvy Bike Ride Route Analysis, using AVL trees.
// <<Ahmed Khan akhan227 652469935>>
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project #04

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "avl.h"

// function prototypes
char *getFileName();
void skipRestOfInput(FILE *stream);

// main
//------------------------------------------------------------------------------------------------------
int main()
{
  printf("** Welcome to Divvy Route Analysis **\n");

  // get filenames from the user/stdin:
  char *StationsFileName = getFileName();
  char *TripsFileName = getFileName();

  // create empty trees
  AVL *stations = AVLCreate();		
  AVL *trips = AVLCreate();			
  AVL *bikes = AVLCreate();		

								// fill the trees
  BuildTrees(StationsFileName, TripsFileName, stations, trips, bikes);


  // now interact with user:
  printf("** Ready **\n");

  char  cmd[64];
  int   ID;
  double Lat, Long, Dist;

  printf("\n>> ");
  scanf("%s", cmd);

  while (strcmp(cmd, "exit") != 0)
  {
    if (strcmp(cmd, "stats") == 0)			// stats
    {
	 DoStats(stations, trips, bikes);
    }
    else if (strcmp(cmd, "station") == 0)	// station
    {
	 scanf("%d", &ID);
	 DoStation(stations, ID);
    }
    else if (strcmp(cmd, "trip") == 0)		// trip
    {
	 scanf("%d", &ID);
	 DoTrips(trips, ID);
    }
    else if (strcmp(cmd, "bike") == 0)		// bike
    {
	 scanf("%d", &ID);
	 DoBikes(bikes, ID);
    }
    else if (strcmp(cmd, "find") == 0)		// find
    {
	 scanf("%lf %lf %lf", &Lat, &Long, &Dist);
	 int index = 0;
	 AVLValue *values = DoFind(stations, Lat, Long, Dist, &index);
	 SelectionSort(values, index);
	 printArrayInOrder(values, index);

	 free(values);
    }
    else if (strcmp(cmd, "route") == 0)		// route
    {
	 scanf("%d %lf", &ID, &Dist);
	 DoRoute(stations, trips, ID, Dist);
    }
    else
    {
	 printf("**unknown cmd, try again...\n");
    }
    printf("\n>> ");
    scanf("%s", cmd);
  }

  printf("** Done **\n");

  system("pause");
  return 0;
}
//------------------------------------------------------------------------------------------------------
//
// getFileName: 
//
// Inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be 
// opened, an error message is output and the program is exited.
//
char *getFileName()
{
  char filename[512];
  int  fnsize = sizeof(filename) / sizeof(filename[0]);

  // input filename from the keyboard:
  fgets(filename, fnsize, stdin);
  filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

									  // make sure filename exists and can be opened:
  FILE *infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }

  fclose(infile);

  // duplicate and return filename:
  char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));					
  strcpy(s, filename);

  return s;
}
//------------------------------------------------------------------------------------------------------
//
// skipRestOfInput:
//
// Inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s).
//
void skipRestOfInput(FILE *stream)
{
  char restOfLine[256];
  int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

  fgets(restOfLine, rolLength, stream);
}
//------------------------------------------------------------------------------------------------------