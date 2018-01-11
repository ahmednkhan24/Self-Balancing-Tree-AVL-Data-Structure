# University of Illinois (Chicago)
# Divvy Bike Ride Analysis in C

## Objective
This project uses data obtained from the official Divvy Bike website. The files are in .csv format.
It takes the raw data and creates a self balancing tree that can be searched through in much less than a second.

The two files must be input first before any statistics can be calculated. A sample picture of valid input is given to demonstrate the functionality of the program. Although input error-checking is done within the program, the sample picture only shows valid input.

## Functionality
	Find
		Input format: Latitude Longitude Distance
		Finds all Divvy Bike stations that are within ‘Distance’ range of the given location
	Stats
		Input format: station 'stationID'
		Provides overall statistics of the files and their respective data
	Trip
		Input format: trip 'tripID'
		Provides overall statistics of the specified trip
	Bike
		Input format: bike 'bikeID'
		Provides overall statistics of the specific bike



###### Self Balancing Binary Search Tree Information

Binary search trees are one of the most powerful and reliable data structures in computer programming due to their fast search time.
A self-balancing tree containing N items allows the lookup, insertion, and removal of an item in O(logN) for the worst-case. Creating and using binary search trees involve a heavy use and understanding of recursion.

The specific self-balancing tree implementation I used for this project was an AVL tree.
In an AVL tree, the heights of the two child subtrees of any node differ by at most one.
The balance factor of a node is the height of its right subtree minus the height of its left subtree.
A node with a balance factor of 1, 0, or -1 is considered to be balanced.

Insertion is where the tree may become unbalanced. After inserting a node into the tree it is necessary to traverse back up the tree and fix any unbalancing issues that may have been caused. 

Rebalancing the tree is done by a…
* Left rotate
* Right rotate
* Left-Right rotate
* Right-Left rotate

