/*avl.h*/
// AVL Tree ADT header file.
// <<Ahmed Khan akhan227 652469935>>
// U. of Illinois, Chicago
// CS251, Spring 2017

#pragma once

typedef int  AVLKey;

//----------------------
typedef struct STATION
{
  int     StationID;
  char    StationName[100];
  double  Latitude;
  double  Longitude;
  int     Dcapacity;
  char   *OnlineDate;
  int     TripCount;
  double  Distance;

} STATION;
//----------------------
typedef struct TRIP
{
  int   TripID;
  char  StartTime[100];
  char  StopTime[100];
  int   BikeID;
  int   TripDuration;
  int   FromStationID;
  char  FromStationName[100];
  int   ToStationID;
  char  ToStationName[100];

} TRIP;
//----------------------
typedef struct BIKE
{
  int  BikeID;
  int  TripCount;

} BIKE;
//----------------------
enum UNIONTYPE
{
  STATIONTYPE,
  TRIPTYPE,
  BIKETYPE
};
//----------------------


//----------------------
typedef struct AVLValue
{
  enum UNIONTYPE Type;  // Station, Trip, or Bike:
  union
  {
    STATION  Station;   // union => only ONE of these is stored:
    TRIP     Trip;
    BIKE     Bike;
  };
} AVLValue;
//----------------------
typedef struct AVLNode
{
  AVLKey    Key;
  AVLValue  Value;
  struct AVLNode  *Left;
  struct AVLNode  *Right;
  int       Height;
} AVLNode;
//----------------------
typedef struct AVL
{
  AVLNode *Root;
  int      Count;
} AVL;
//----------------------

//------------------------------------------------------------------------------------------------------
AVL *AVLCreate();
void BuildTrees(char StationsFileName[], char TripsFileName[], AVL *stations, AVL *trips, AVL *bikes);
void AVLFree(AVL *tree, void(*fp)(AVLKey key, AVLValue value));

int      AVLCompareKeys(AVLKey key1, AVLKey key2);
AVLNode *AVLSearch(AVL *tree, AVLKey key);
int      AVLInsert(AVL *tree, AVLKey key, AVLValue value);

int  AVLCount(AVL *tree);
int  AVLHeight(AVL *tree);
double distBetween2Points(double lat1, double long1, double lat2, double long2);
void printArrayInOrder(AVLValue values[], int index);
void SelectionSort(AVLValue subtree[], int numSubtrees);

void DoStats(AVL *stations, AVL *trips, AVL *bikes);
void DoStation(AVL *stations, int ID);
void DoTrips(AVL *trips, int ID);
void DoBikes(AVL *bikes, int ID);
AVLValue *DoFind(AVL *stations, double Latitude, double Longitude, double Distance, int *index);
void DoRoute(AVL *stations, AVL *trips, int TripID, double Dist);
//------------------------------------------------------------------------------------------------------


