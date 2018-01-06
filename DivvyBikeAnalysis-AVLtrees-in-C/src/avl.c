/*avl.c*/
//
// AVL Tree ADT implementation file.
//
// <<Ahmed Khan akhan227 652469935>>
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "avl.h"

int _TRUE = 1;
int _FALSE = 0;

//------------------------------------------------------------------------------------------------------
//
// AVLCreate:
//
// Dynamically creates and returns an empty AVL tree.
//
AVL *AVLCreate()
{
  AVL *tree;

  tree = (AVL *)malloc(sizeof(AVL));															// FREEEEEEE
  tree->Root = NULL;
  tree->Count = 0;

  return tree;
}
//------------------------------------------------------------------------------------------------------
void Deallocate(AVLNode *Root)
{
  if (Root == NULL)
    return;

  Deallocate(Root->Left);
  Deallocate(Root->Right);

  free(Root);
}
//------------------------------------------------------------------------------------------------------
//
// AVLFree:
//
// Frees the memory associated with the tree: the handle and the nodes.
// The provided function pointer is called to free the memory that
// might have been allocated as part of the key or value.
//
void AVLFree(AVL *tree, void(*fp)(AVLKey key, AVLValue value))
{
  AVLNode *cur = tree->Root;

  Deallocate(cur);

  free(tree);

  //printf(">>>>> AVLFree needs to be implemented <<<<<\n");

}
//------------------------------------------------------------------------------------------------------
//
// AVLCompareKeys: 
//
// Compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int AVLCompareKeys(AVLKey key1, AVLKey key2)
{
  if (key1 < key2)
    return -1;
  else if (key1 == key2)
    return 0;
  else
    return 1;
}
//------------------------------------------------------------------------------------------------------
//
// AVLCount:
//
// Returns # of nodes in the tree.
//
int AVLCount(AVL *tree)
{
  return tree->Count;
}
//------------------------------------------------------------------------------------------------------
//
// AVLHeight: 
//
// Returns the overall height of the AVL tree.
//
int AVLHeight(AVL *tree)
{
  if (tree->Root == NULL)
    return -1;
  else
    return tree->Root->Height;
}
// start insert functions
//------------------------------------------------------------------------------------------------------
//--------------------------------------
int _findMax(int left, int right)
{
  if (left > right)
    return left;
  else
    return right;
}
//--------------------------------------
int _HummelHeight(AVLNode *root)
{
  if (root == NULL)
    return -1;

  return 1 + _findMax(_HummelHeight(root->Left), _HummelHeight(root->Right));
}
//--------------------------------------
int findHeight(AVLNode *root)
{
  if (root == NULL)
    return -1;

  int Left = findHeight(root->Left);
  int Right = findHeight(root->Right);

  int height = 1 + _findMax(Left, Right);

  return height;
}
//--------------------------------------
//
// Rotate right the sub-tree rooted at node k2, return pointer
// to root of newly-rotated sub-tree --- i.e. return pointer
// to node k1 that was rotated up to top of sub-tree.  Heights
// of the rotated sub-tree are also updated by this function.
//
AVLNode *RightRotate(AVLNode *k2)
{
  // grab pointers to various components shown in diagram
  AVLNode *k1 = k2->Left;
  AVLNode *Y = k1->Right;
  //AVLNode *X = k1->Left;
  //AVLNode *Z = k2->Right;

  // rotate k1 up, and k2 down
  k1->Right = k2;
  k2->Left = Y;

  // check heights
  k1->Height = findHeight(k1);
  k2->Height = findHeight(k2);

  return k1;
}
//
// Rotate left the sub-tree rooted at node k1, return pointer
// to root of newly-rotated sub-tree --- i.e. return pointer
// to node k2 that was rotated up to top of sub-tree.  Heights
// of the rotated sub-tree are also updated by this function.
//
AVLNode *LeftRotate(AVLNode *k1)
{
  AVLNode *k2 = k1->Right;
  AVLNode *Y = k2->Left;
  //AVLNode *X = k1->Left;
  //AVLNode *Z = k2->Right;

  // rotate k2 up, and k1 down
  k2->Left = k1;
  k1->Right = Y;

  // check heights
  k2->Height = findHeight(k2);
  k1->Height = findHeight(k1);

  return k2;
}
//--------------------------------------
AVLNode *LeftRightRotate(AVLNode *k3)
{
  AVLNode *k1 = k3->Left;
  AVLNode *k2 = k1->Right;
  AVLNode *B = k2->Left;
  AVLNode *C = k2->Right;

  // Left Rotate at k1
  k1 = LeftRotate(k1);

  k3->Left = k1;
  // Right Rotate at k3
  k3 = RightRotate(k3);

  return k3;
}
//--------------------------------------
AVLNode *RightLeftRotate(AVLNode *k1)
{
  AVLNode *k3 = k1->Right;
  AVLNode *k2 = k3->Left;
  AVLNode *B = k2->Left;
  AVLNode *C = k2->Right;

  k3 = RightRotate(k3);

  k1->Right = k3;

  k1 = LeftRotate(k1);

  return k1;
}
//--------------------------------------
// I use the keys to determine whether it's case 1, 2, 3, or 4.  
// You compare the key of the node you inserted to the key of where the AVL condition is broken. 
// That tells you case 1/2 vs. 3/4.  
// And same approach to determine 1 vs 2 and 3 vs. 4
AVLNode *DoRotate(AVLNode *BrokenRoot, AVLNode *InsertedNode)
{
  if ((AVLCompareKeys(InsertedNode->Key, BrokenRoot->Key)) < 0)	// case 1 or 2
  {	// open if statement
    if ((AVLCompareKeys(InsertedNode->Key, BrokenRoot->Left->Key)) < 0)
    {
	 // case 1
	 BrokenRoot = RightRotate(BrokenRoot);
    }
    else
    {
	 // case 2
	 BrokenRoot = LeftRightRotate(BrokenRoot);
    }
  }	// close if statement
  else	// case 3 or 4
  {	// open else statement
    if ((AVLCompareKeys(InsertedNode->Key, BrokenRoot->Right->Key)) < 0)
    {
	 // case 3
	 BrokenRoot = RightLeftRotate(BrokenRoot);
    }
    else
    {
	 // case 4
	 BrokenRoot = LeftRotate(BrokenRoot);
    }
  }	// close else statement
  return BrokenRoot;
}
//--------------------------------------
////------------------------------------------------------------------------
int AVLInsert(AVL *tree, AVLKey key, AVLValue value)
{
  AVLNode *cur = tree->Root;
  AVLNode *prev = NULL;

  AVLNode *stack[64];
  int top = -1;

  // search for insertion point
  while (cur != NULL)
  {
    top++;						// incremnt stack index
    stack[top] = cur;			// store the path we follow into the stack

    if (AVLCompareKeys(key, cur->Key) == 0)
	 return _FALSE;				// key is already in the tree so return
    else if (AVLCompareKeys(key, cur->Key) < 0)
    {
	 prev = cur;
	 cur = cur->Left;
    }
    else
    {
	 prev = cur;
	 cur = cur->Right;
    }
  }

  // if we got here then we did not find the key in the tree and we also fell out of the tree
  AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));    // create a new node to add to the tree		// FREEEEEEE
  node->Key = key;
  node->Value = value;
  node->Left = NULL;
  node->Right = NULL;
  node->Height = 0;

  // now insert
  if (prev == NULL)          // if the tree is empty
    tree->Root = node;
  else if (AVLCompareKeys(key, prev->Key) < 0)
    prev->Left = node;
  else
    prev->Right = node;
  tree->Count++;				// increment tree count

							// node has been inserted. Now walk back up the tree and see if we broke the AVL condition
							// walk back up the tree

  int rebalance = _FALSE;
  AVLNode *N;
  while (top >= 0)		// while stack is not empty
  {
    N = stack[top];		// pop 
    top--;				// the stack
    if (top == -1)
	 prev = NULL;
    else
	 prev = stack[top];


    int LeftH = _HummelHeight(N->Left);
    int RightH = _HummelHeight(N->Right);
    int newH = 1 + _findMax(LeftH, RightH);

    if (newH == N->Height)				// height did not change
    {
	 rebalance = _FALSE;
	 break;
    }
    else if (abs(LeftH - RightH) > 1)	// broke the AVL condition
    {
	 rebalance = _TRUE;
	 break;
    }
    else								// height changed, but did not break the AVL condition
    {
	 N->Height = newH;
    }
  }

  // we broke from the loop, now we have to see if we have to rebalance the tree
  if (rebalance == _TRUE)
  {
    //AVLNode *rotated = DoRotate(N);
    AVLNode *rotated = DoRotate(N, node);

    if (prev == NULL)		// rotated node is the root of the tree
	 tree->Root = rotated;
    else
    {
	 if (prev->Left == N)		// current is the left child of prev
	   prev->Left = rotated;
	 else
	   prev->Right = rotated;
    }
  }

  return _TRUE;
}
////------------------------------------------------------------------------
//---------------------------------------------------------------------------------
AVLNode *AVLSearch(AVL *tree, AVLKey key)
{
  AVLNode *cur = tree->Root;

  //
  // search the tree to see if it contains a matching key:
  //
  while (cur != NULL)
  {
    if (AVLCompareKeys(key, cur->Key) == 0)		// found!
	 return cur;
    else if (AVLCompareKeys(key, cur->Key) < 0)  // smaller, go left:
    {
	 cur = cur->Left;
    }
    else  // larger, go right:
    {
	 cur = cur->Right;
    }
  }

  // if we get here, we fell out of the tree, and didn't find it:
  return NULL;

  // BSTSearch: searches the binary search tree for a node containing the
  // same key.  If a match is found, a pointer to the node is returned, 
  // otherwise NULL is returned.
}
//------------------------------------------------------------------------------------------------------
void BuildTrees(char StationsFileName[], char TripsFileName[], AVL *stations, AVL *trips, AVL *bikes)
{
  FILE *pStationFile;
  pStationFile = fopen(StationsFileName, "r");

  char StationData[500];
  fgets(StationData, 500, pStationFile);	// ignore first line

  int StationInserted = 0;
  int StationFailed = 0;

  int    key;
  double value;
  char   *token1;
  int i = 1;
  while (fgets(StationData, 500, pStationFile) != NULL)
  {	// open while loop

	// Insert a new station:
    AVLValue stationValue;
    stationValue.Type = STATIONTYPE;		// union holds a station:
									// ID
    token1 = strtok(StationData, ",");
    key = atoi(token1);					// convert to an int
    stationValue.Station.StationID = key;

    // NAME
    token1 = strtok(NULL, ",");
    strcpy(stationValue.Station.StationName, token1);

    // LATITUDE
    token1 = strtok(NULL, ",");
    value = atof(token1);				// convert to a float
    stationValue.Station.Latitude = value;

    // LONGITUDE
    token1 = strtok(NULL, ",");
    value = atof(token1);
    stationValue.Station.Longitude = value;

    // DCAPACITY
    token1 = strtok(NULL, ",");
    key = atoi(token1);
    stationValue.Station.Dcapacity = key;

    // ONLINE_DATE
    stationValue.Station.OnlineDate = strtok(NULL, ",");

    stationValue.Station.TripCount = 0;

    if (AVLInsert(stations, stationValue.Station.StationID, stationValue))
	 StationInserted++;
    else
	 StationFailed++;

    i++;
  }	// close while loop
  fclose(pStationFile);
  //=================================================================================================
  // trip
  //=================================================================================================
  FILE *pTripFile;
  pTripFile = fopen(TripsFileName, "r");

  char TripData[500];
  fgets(TripData, 500, pTripFile);	// ignore first line

  int TripInserted = 0;
  int TripFailed = 0;

  int BikeInserted = 0;
  int BikeFailed = 0;

  char *UserType;		// dont need
  char *Gender;		// dont need
  int  BirthYear;		// dont need

  char *token2;

  while (fgets(TripData, 500, pTripFile) != NULL)
  {	// open while loop

	// Insert a new trip:
    AVLValue tripValue;
    tripValue.Type = TRIPTYPE;  // union holds a trip:

    AVLValue bikeValue;
    bikeValue.Type = BIKETYPE;  // union holds a bike:

						  // ID
    token1 = strtok(TripData, ",");
    key = atoi(token1);
    tripValue.Trip.TripID = key;

    // START TIME
    token1 = strtok(NULL, ",");
    strcpy(tripValue.Trip.StartTime, token1);

    // STOP TIME
    token1 = strtok(NULL, ",");
    strcpy(tripValue.Trip.StopTime, token1);

    // BIKE ID
    token1 = strtok(NULL, ",");
    key = atoi(token1);
    tripValue.Trip.BikeID = key;

    // bikes
    //====================================================================
    // Insert a new bike:
    bikeValue.Bike.BikeID = key;
    AVLNode *temp = AVLSearch(bikes, bikeValue.Bike.BikeID);
    if (temp == NULL)
    {
	 bikeValue.Bike.TripCount = 1;
	 if (AVLInsert(bikes, bikeValue.Bike.BikeID, bikeValue))
	   BikeInserted++;
	 else
	   BikeFailed++;
    }
    else
    {
	 (temp->Value.Bike.TripCount)++;
    }
    //====================================================================		
    // TRIP DURATION
    token1 = strtok(NULL, ",");
    key = atoi(token1);
    tripValue.Trip.TripDuration = key;

    // FROM STATION ID
    token1 = strtok(NULL, ",");
    key = atoi(token1);
    tripValue.Trip.FromStationID = key;

    AVLNode *count = AVLSearch(stations, tripValue.Trip.FromStationID);

    if (count != NULL)
    {
	 (count->Value.Station.TripCount)++;
    }

    // FROM STATION NAME
    token1 = strtok(NULL, ",");
    strcpy(tripValue.Trip.FromStationName, token1);

    // TO STATION ID
    token1 = strtok(NULL, ",");
    key = atoi(token1);
    tripValue.Trip.ToStationID = key;

    count = AVLSearch(stations, tripValue.Trip.ToStationID);

    if (count != NULL)
    {
	 (count->Value.Station.TripCount)++;
    }

    // TO STATION NAME
    token1 = strtok(NULL, ",");
    strcpy(tripValue.Trip.ToStationName, token1);

    // dont need
    UserType = strtok(NULL, ",");
    Gender = strtok(NULL, ",");
    token2 = strtok(NULL, ",");
    // dont need

    if (AVLInsert(trips, tripValue.Trip.TripID, tripValue))
	 TripInserted++;
    else
	 TripFailed++;

  }	// close while loop
  fclose(pTripFile);
}
//------------------------------------------------------------------------------------------------------
void MinutesAndSeconds(int time)
{
  int seconds = (time % 60);
  int minutes = (time - seconds) / 60;

  printf("  Duration: %d min, %d secs\n", minutes, seconds);
}
//------------------------------------------------------------------------------------------------------
void DoStats(AVL *stations, AVL *trips, AVL *bikes)
{
  printf("** Trees:\n");

  printf("   Stations: count = %d, height = %d\n", AVLCount(stations), AVLHeight(stations));
  printf("   Trips:    count = %d, height = %d\n", AVLCount(trips), AVLHeight(trips));
  printf("   Bikes:    count = %d, height = %d\n", AVLCount(bikes), AVLHeight(bikes));
}
//------------------------------------------------------------------------------------------------------
void DoStation(AVL *stations, int ID)
{
  AVLNode *desiredNode = AVLSearch(stations, ID);

  if (desiredNode == NULL)
    printf("**not found\n");
  else
  {
    printf("**Station %d:\n", desiredNode->Value.Station.StationID);
    printf("  Name: '%s'\n", desiredNode->Value.Station.StationName);
    printf("  Location:   (%lf,%lf)\n", desiredNode->Value.Station.Latitude, desiredNode->Value.Station.Longitude);
    printf("  Capacity:   %d\n", desiredNode->Value.Station.Dcapacity);
    printf("  Trip count: %d\n", desiredNode->Value.Station.TripCount);
  }
}
//------------------------------------------------------------------------------------------------------
void DoTrips(AVL *trips, int ID)
{
  AVLNode *desiredNode = AVLSearch(trips, ID);

  if (desiredNode == NULL)
    printf("**not found\n");
  else
  {
    printf("**Trip %d:\n", desiredNode->Value.Trip.TripID);
    printf("  Bike: %d\n", desiredNode->Value.Trip.BikeID);
    printf("  From: %d\n", desiredNode->Value.Trip.FromStationID);
    printf("  To:   %d\n", desiredNode->Value.Trip.ToStationID);
    MinutesAndSeconds(desiredNode->Value.Trip.TripDuration);
  }
}
//------------------------------------------------------------------------------------------------------
void DoBikes(AVL *bikes, int ID)
{
  AVLNode *desiredNode = AVLSearch(bikes, ID);

  if (desiredNode == NULL)
    printf("**not found\n");
  else
  {
    printf("**Bike %d:\n", desiredNode->Value.Bike.BikeID);
    printf("  Trip count: %d\n", desiredNode->Value.Bike.TripCount);
  }
}
//------------------------------------------------------------------------------------------------------
// distBetween2Points: 
// Returns the distance in miles between 2 points (lat1, long1) and (lat2, long2).
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  // Reference: http://www8.nau.edu/cvm/latlon_formula.html
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad)*cos(long1_rad)*cos(lat2_rad)*cos(long2_rad))
    +
    (cos(lat1_rad)*sin(long1_rad)*cos(lat2_rad)*sin(long2_rad))
    +
    (sin(lat1_rad)*sin(lat2_rad))
  );
  return dist;
}
//------------------------------------------------------------------------------------------------------
void printArrayInOrder(AVLValue values[], int index)
{
  int i;
  for (i = 0; i < index; i++)
  {
    printf("Station %d: distance %lf miles\n", values[i].Station.StationID, values[i].Station.Distance);
  }
}
//------------------------------------------------------------------------------------------------------
void SelectionSort(AVLValue subtree[], int numSubtrees)
{
  int index;
  int i;
  int j;
  for (i = 0; i < numSubtrees - 1; i++)
  {
    index = i;

    for (j = i + 1; j < numSubtrees; j++)
    {
	 if (subtree[j].Station.Distance < subtree[index].Station.Distance)		// j is smaller
	   index = j;

	 else if (subtree[j].Station.Distance == subtree[index].Station.Distance)
	 {
	   if (subtree[j].Station.StationID < subtree[index].Station.StationID)		// j is smaller
		index = j;
	 }
    }
    if (index != i)
    {
	 AVLValue M = subtree[i];
	 subtree[i] = subtree[index];
	 subtree[index] = M;
    }
  }
}
//------------------------------------------------------------------------------------------------------------------
void Find(AVLNode *Root, AVLValue *values, int *index, double Lat, double Long, double DesiredD)
{
  if (Root == NULL)
    return;
  else
  {
    Find(Root->Left, values, index, Lat, Long, DesiredD);

    double Distance = distBetween2Points(Root->Value.Station.Latitude, Root->Value.Station.Longitude, Lat, Long);

    if (Distance <= DesiredD)
    {
	 values[(*index)].Station.StationID = Root->Value.Station.StationID;
	 values[(*index)].Station.Distance = Distance;
	 (*index)++;
    }

    Find(Root->Right, values, index, Lat, Long, DesiredD);
  }
}
//------------------------------------------------------------------------------------------------------
AVLValue *DoFind(AVL *stations, double Latitude, double Longitude, double Distance, int *index)
{
  AVLValue *values = (AVLValue *)malloc(stations->Count * sizeof(AVLValue));						// FREEEEEEE

  Find(stations->Root, values, *&index, Latitude, Longitude, Distance);

  return values;
}
//------------------------------------------------------------------------------------------------------
void FindTripsFrom(AVLNode *Root, AVLValue *values, int stationID, int *index)
{
  if (Root == NULL)
    return;
  else
  {
    FindTripsFrom(Root->Left, values, stationID, index);

    if (Root->Value.Trip.FromStationID == stationID);
    {
	 values[(*index)].Trip = Root->Value.Trip;
	 (*index)++;
    }
    FindTripsFrom(Root->Right, values, stationID, index);
  }
}
//------------------------------------------------------------------------------------------------------
void FindTripsTo(AVLNode *Root, AVLValue *values, int stationID, int *index)
{
  if (Root == NULL)
    return;
  else
  {
    FindTripsTo(Root->Left, values, stationID, index);

    if (Root->Value.Trip.ToStationID == stationID);
    {
	 values[(*index)].Trip = Root->Value.Trip;
	 (*index)++;
    }
    FindTripsTo(Root->Right, values, stationID, index);
  }
}
//------------------------------------------------------------------------------------------------------
void lol(AVLNode *Root, int *index, int fromID, int toID)
{
  if (Root == NULL)
    return;
  else
  {
    lol(Root->Left, index, fromID, toID);

    if ((Root->Value.Trip.FromStationID == fromID) && (Root->Value.Trip.ToStationID == toID))
    {
	 (*index)++;
    }

    lol(Root->Right, index, fromID, toID);
  }
}
//------------------------------------------------------------------------------------------------------
int _route(AVL *stations, AVL *trips, int TripID, double Dist, int s, int d)
{
  AVLNode *FromStation = AVLSearch(stations, s);	// find station S
  AVLNode *ToStation = AVLSearch(stations, d);	// find station D

  int SIndex = 0;
  AVLValue *SPrime = DoFind(stations, FromStation->Value.Station.Latitude,
    FromStation->Value.Station.Longitude, Dist, &SIndex);

  // find all stations that are Dist away from station D
  int DIndex = 0;
  AVLValue *DPrime = DoFind(stations, ToStation->Value.Station.Latitude,
    ToStation->Value.Station.Longitude, Dist, &DIndex);

  int i, j;
  int k = 0;

  for (i = 0; i < SIndex; i++)
  {
    AVLValue tempS = SPrime[i];

    for (j = 0; j < DIndex; j++)
    {
	 AVLValue tempD = DPrime[j];
	 lol(trips->Root, &k, tempS.Station.StationID, tempD.Station.StationID);
    }
  }

  free(SPrime);
  free(DPrime);

  return k;
}
//------------------------------------------------------------------------------------------------------
void DoRoute(AVL *stations, AVL *trips, int TripID, double Dist)
{
  AVLNode *Route = AVLSearch(trips, TripID);		// find the trip
  if (Route == NULL)								// check if the trip exists
  {
    printf("**not found\n");
    return;
  }

  int s = Route->Value.Trip.FromStationID;	// get station ID for S
  int d = Route->Value.Trip.ToStationID;		// get station ID for D

  int tripCount = _route(stations, trips, TripID, Dist, s, d);

  double percentage = ((double)tripCount / trips->Count) * 100;

  printf("** Route: from station #%d to station #%d\n", s, d);
  printf("** Trip count: %d\n", tripCount);
  printf("** Percentage: %lf", percentage);
  printf("%\n");
}
//------------------------------------------------------------------------------------------------------

