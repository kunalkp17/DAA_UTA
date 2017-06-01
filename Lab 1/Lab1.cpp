/*
Lab 1 : 2D Closest Pair by Sweepline Algorithm using Treaps



Refrences:
	-GeeksForGeeks : Treaps Utlilty Functions
	-StackOverFlow : Time measurement
*/

#include<iostream>
#include<conio.h>
#include<string>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>
using namespace std;
const int size = 30000;

int MinDistInRect = 0;
int deleteNodeList[size][2];
int deleteIndex;
int rightRotationsCounter = 0;
int left_rotations_counter = 0;
int sweepClosestPair[2][2];
int bruteClosestPair[2][2];
int finalCountOfNodes=0;
int maxCountOfNodes = 0;
int bruteForceDistance=INT_MAX;
int sweepLineDistance=-1;
/* Distance()
Calcualtes the distance between two points*/
int distance(int x1, int y1, int x2, int y2)
{
	int dist = (x1 - x2)*(x1 - x2) + (y1 - y2) *(y1 - y2);
	return dist;
}
/*Quick Sort Methods
	quickSort()
	divide()
	swap()

	quickSort() is the master function that is recurrsive and calls upon divide() to sort the given aray.
	It deals with two aray, sorts on the basis of X  

*/
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int divide(int(&arrayOfX)[size], int(&arrayOfY) [size],int lower, int upper)
{
	int pole = arrayOfX[upper] ,j = (lower - 1);
	
	for (int i = lower; i <= upper - 1; i++)
	{
		if (arrayOfX[j] <= pole)
		{
			j++;
			swap(&arrayOfX[j], &arrayOfX[i]);
			swap(&arrayOfY[j], &arrayOfY[i]);
		}
	}
	swap(&arrayOfX[j + 1], &arrayOfX[upper]);
	swap(&arrayOfY[j + 1], &arrayOfY[upper]);
	return (j + 1);
}

void quickSort(int(&arrayOfX)[size], int(&arrayOfY)[size], int lower, int upper)
{
	if (lower < upper)
	{
		int index = divide(arrayOfX, arrayOfY, lower, upper);

		quickSort(arrayOfX, arrayOfY, lower, index - 1);
		quickSort(arrayOfX, arrayOfY, index + 1, upper);
	}
}


/* Treaps functions and structures
	struct node						: Structure definition
	rightRotate()					: Right Rotate the Tree
	leftRotate()					: Left Rotate the Tree
	newNode()						: Create the node 
	insertNode()					: Insert the node into the tree using recursion
	deleteNode()					: Delete the node from the tree after reaching it using recursion
	treapsTraversalUpdater()		: Traverses the tree in serach for elements within the rectangular dimension of the sweep line point; Creates a ist of elements that are out of biunds



*/
struct Node
{
	int y, priority;
	int x;
	Node *left, *right;
};

Node *rightRotate(Node *y)
{
	rightRotationsCounter++;
	Node *x = y->left, *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Return new root
	return x;
}

Node *leftRotate(Node *x)
{
	left_rotations_counter++;
	Node *y = x->right, *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Return new root
	return y;
}


Node* newNode(int pointOfX,int pointOfY)
{
	Node* temp = new Node;
	temp->y = pointOfY;
	temp->x = pointOfX;
	temp->priority = rand() % 100;
	temp->left = temp->right = NULL;
	return temp;
}

Node* insertNode(Node* root,int x, int y)
{
	
	// If root is NULL, create a new node and return it
	if (!root)
		return newNode(x,y);

	// If key is smaller than root
	if (y <= root->y)
	{
		// Insert in left subtree
		root->left = insertNode(root->left, x, y);

		// Fix Heap property if it is violated
		if (root->left->priority > root->priority)
			root = rightRotate(root);
	}
	else  // If key is greater
	{
		// Insert in right subtree
		root->right = insertNode(root->right, x, y);

		// Fix Heap property if it is violated
		if (root->right->priority > root->priority)
			root = leftRotate(root);
	}
	return root;
}

Node* deleteNode(Node* root, int x, int y)
{
	

	if (root == NULL)
		return root;

	if (y == root->y&& x == root->x)
	{
		// If left is NULL
	if (root->left == NULL)
	{
		Node *temp = root->right;
		delete(root);
		root = temp;  // Make right child as root
	}

	// If Right is NULL
	else if (root->right == NULL)
	{
		Node *temp = root->left;
		delete(root);
		root = temp;  // Make left child as root
	}

	// If key is at root and both left and right are not NULL
	else if (root->left->priority < root->right->priority)
	{
		root = leftRotate(root);
		root->left = deleteNode(root->left, x, y);
	}
	else
	{
		root = rightRotate(root);
		root->right = deleteNode(root->right,x, y);
	}

	}


	else if (y <= root->y)
		root->left = deleteNode(root->left,x, y);
	else
		root->right = deleteNode(root->right,x, y);

	
	return root;
}

void treapsTraversalUpdater(Node* root ,int dist,int x,int y)
{
	if (root)
	{
		treapsTraversalUpdater(root->left, dist, x, y);
		if (root->x >= (x - dist) && root->y >= (y - dist) && root->y <= (y + dist))
		{ 
			 int temp = distance(root->x, root->y, x, y);
			
			 if (MinDistInRect > temp || MinDistInRect == 0)
				 {
					 MinDistInRect = temp;

				 }
			 

		}
		else
		{
			deleteNodeList[deleteIndex][0] = root->x;  // DD array to store X and Y coordinated of points that are to be deleted
			deleteNodeList[deleteIndex][1] = root->y;
			deleteIndex++;
		}


		treapsTraversalUpdater(root->right, dist, x, y);
	}
}



void bruteForce(int x[size], int y[size], int numberOfElements)
{
	int minDistance = INT_MAX;
	for (int i = 0; i < numberOfElements; i++)
	{  
		for (int j = 0; j < numberOfElements; j++)
		{
			int temp = distance(x[i],y[i],x[j],y[j]);
			if (temp < minDistance && i != j)
			{
				minDistance = temp;
				bruteClosestPair[0][0] = x[i];
				bruteClosestPair[0][1] = y[i];
				bruteClosestPair[1][0] = x[j];
				bruteClosestPair[1][1] = y[j];

				
			}
		}
	}
	bruteForceDistance = minDistance;
}


int main()
{
	srand(time(NULL));
	int numberOfElements, i, nd_numberOfElements = 0, j;			// nd -> non duplicate
	int arrayOfX[size];												//array of X points
	int arrayOfY[size];												//array of Y points
	int nd_arrayOfX[size];											//array of non duplicate X points
	int nd_arrayOfY[size];											//array of non duplicate Y points
	cout << "\nPlease enter the number of points followed \nby the points on each line seperated by a space \n\n";
	cin >> numberOfElements;
	
	Rt:
	for (i = 0; i < numberOfElements; i++)
	{
		cin >> arrayOfX[i] >> arrayOfY[i];
		if (arrayOfX[i] > 16000 || arrayOfX[i] < -16000 || arrayOfY[i] > 16000 || arrayOfX[i] < -16000)
		{		cout << "\n\n Number above 16000 or below - 16000 entered. \n Please re enter the stream of points\n\n";
		goto Rt;
		}
	}
	
//Quick Sort is Performed
	 clock_t begin = clock();
	 quickSort(arrayOfX, arrayOfY, 0, numberOfElements - 1);
	clock_t end = clock();
	double qsort_time = double(end - begin) / CLOCKS_PER_SEC;



//Duplicaes are removed
	nd_arrayOfX[0] = arrayOfX[0];
	nd_arrayOfY[0] = arrayOfY[0];
	for (i = 1; i <= numberOfElements; i++)
	{
		if (arrayOfX[i] == nd_arrayOfX[nd_numberOfElements] && arrayOfY[i] == nd_arrayOfY[nd_numberOfElements])
		{
			continue;
		}
		nd_numberOfElements++;
		nd_arrayOfX[nd_numberOfElements] = arrayOfX[i];
		nd_arrayOfY[nd_numberOfElements] = arrayOfY[i];
		
	}

// Sweep Line Algorithm
	struct Node *root = NULL;
	 clock_t begin2 = clock();
	 for (i = 0; i < nd_numberOfElements; i++)
	{
		if (!root)																						// Initial Case to enter first element
		{
			root = insertNode(root, nd_arrayOfX[i], nd_arrayOfY[i]);

		}
		else if (root->left == NULL && root->right == NULL && sweepLineDistance == -1)					// Second Case; Calculating first minimum Distance
		{
			sweepLineDistance = distance(root->x, root->y, nd_arrayOfX[i], nd_arrayOfY[i]);
			root = insertNode(root, nd_arrayOfX[i], nd_arrayOfY[i]);

		}
		else
		{																								// General Case; Where a rectangle is formed and all points are traversed		
			deleteIndex = 0; MinDistInRect = INT_MAX;
			treapsTraversalUpdater(root, sweepLineDistance, nd_arrayOfX[i], nd_arrayOfY[i]);
			root = insertNode(root, nd_arrayOfX[i], nd_arrayOfY[i]);

			for (j = 0; j < deleteIndex; j++)
			{
				root = deleteNode(root, deleteNodeList[j][0], deleteNodeList[j][1]);
				finalCountOfNodes--;
			}
			if (sweepLineDistance > MinDistInRect)											
			{
				sweepClosestPair[0][0] = nd_arrayOfX[i];
				sweepClosestPair[0][1] = nd_arrayOfY[i];
				sweepLineDistance =  MinDistInRect; // renamed 
			}
		}


		finalCountOfNodes++;
		if (finalCountOfNodes > maxCountOfNodes)
		{
			maxCountOfNodes = finalCountOfNodes;
		}


	}
	clock_t  end2 = clock();
	double sweep_time = double(end2 - begin2) / CLOCKS_PER_SEC;
	

	// brute force technique
	clock_t  begin3 = clock();
	bruteForce(nd_arrayOfX, nd_arrayOfY, nd_numberOfElements);
	clock_t  end3 = clock();
	double brute_time = double(end3 - begin3) / CLOCKS_PER_SEC;


	cout<< "\n :::::::::: \n";
	cout << "Sorting " << numberOfElements<<"\n";
	cout << "Qsort time "<< qsort_time <<"\n";
	cout << "Duplicates removal " << "\n";
	cout << "Closest pair  ( " << sweepClosestPair[0][0] << " " << sweepClosestPair[0][1] << " ) " << "  ( " << bruteClosestPair[1][0] << " " << bruteClosestPair[1][1] << " )" << "\n";
	cout << "Sweep line distance " << sweepLineDistance << "\n";
	cout << "Sweep time " << sweep_time << "\n";
	cout << "Max BST nodes " <<maxCountOfNodes <<"\n";
	cout << "Rotations " << left_rotations_counter << " with left " << rightRotationsCounter << " with right\n";
	cout << "closest pair ( " << bruteClosestPair[0][0] << " " << bruteClosestPair[0][1] << " ) " << "  ( " << bruteClosestPair[1][0] << " " << bruteClosestPair[1][1] << " )" << "\n";
	cout << "Brute force distance "<< bruteForceDistance<<"\n";
	cout << "Brute force time "  <<brute_time<<"\n";

	
	return 0;

}
