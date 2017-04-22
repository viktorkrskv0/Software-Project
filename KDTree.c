/*
 * KDTree.c
 *
 *  Created on: Apr 20, 2017
 *      Author: gleit
 */

#include "SPPoint.h"
#include "SPConfig.h"
#include <stdlib.h>

typedef struct SPDKArray{
	SPPoint* arr;
	int size;
}KD_ARRAY;

typedef struct sp_kd_tree_node{
	int dim;
	float val;
	sp_kd_tree_node* l;
	sp_kd_tree_node* r;
	SPPoint* data; //initialized as NULL
}KDTreeNode;

typedef struct sp_kd_tree{
	root node
	dimention?
	how manny nodes?
}KDTree;

KDTreeNode createNode(int dim, float val, KDTreeNode* l, KDTreeNode* r, SPPoint* data){
	KDTreeNode node = (KDTreeNode) malloc(sizeof(KDTreeNode));
	node.dim = dim;
	node.val = val;
	node.l = l;
	node.r = r;
	node.data = data;
}

KDTreeNode createLeafNode(SPPoint* data){
	KDTreeNode node = (KDTreeNode) malloc(sizeof(KDTreeNode));
	node.dim = -1;
	node.val = -1;
	node.l = NULL;
	node.r = NULL;
	node.data = data;
}

//Vik
KD_ARRAY InitArray(){

}

//Guy
KDTreeNode InitTree(KD_ARRAY arr){
	KDTreeNode root;
	int dim;
	int val;

	//Recursion stopping condition
	if (arr.size == 1)
		return createLeafNode(arr.arr[0]);

	//Recursion step
	dim = determineCoor();
	val = determineVal();
	KD_ARRAY* sonsArr = Split(arr, dim);
	KDTreeNode l = InitTree(sonsArr[0]);
	KDTreeNode r = InitTree(sonsArr[1]);
	root = createNode(dim, val, l, r, NULL);
}

//Vik
KNearestNeighborSearch(){

}

int determineCoor(){
	int coor;
	publicConfig.spKDTreeSplitMethod//do as get
	//cases max spread random incremental
	return coor
}

int determineValue(){

}

//-------------------------------------------------
//init of KDarray
//O(d x nlog(n))
void Init(SPPoint* arr, int size){
	build initial arr
	build kd tree{split arr recursively (to r & l branches)(stop if 1)}
}

//Guy
//coor - by which coordinate to split
//returns a tupple of the right and left branches' roots
//O(d x n)
// d = spPCADimension
// n = total no of features of all img in the directory
KD_ARRAY* Split(KD_ARRAY kdArr, int coor){
	KD_ARRAY* res;
	PublicConfig...
	KD_ARRAY P copyArr(kdArr);
	matrix m = calloc matrix (d X n);
	initializeMatrix(m){for all i rows: initialize row{sort by dim i}};//sorting row O(nlog(n)) | all init O(d x nlog(n))
	calloc Row(row coor); //for signeing purpose
	signRowForSplitting{sign 0/1 = r/l for each cell in row coor};// we can do it since we dont corrupt to original arr)
	calloc p1 p2 new point arrays (|p1| = n/2 up, |p2|=n/2 down);
	fill_KD_ARRAYS(p1,p2,signed row);//p1 with 0-n/2 points, p2 with n/2+1 - n. they are NOT sorted yet
	calloc 2 arrays |p| longl;
	for map1,map2{
		//mapping the original p so we can sort p1 p2
	}
	calloc 2 matrix (d x |p1|, d x |p2|)//not needed, sice it will be done in the next iteration
	coor = determineCoorByIncremental / max spread / random
	create node();
	node.r = split(p1,coor);
	node l = split(p2,coor);

	build matrix
	sign matrix for split
	split into 2 matrixes (n/2 up, n/2 down)
	res[0]=;
	res[1]=;
	return res;
}
//-----------------------------------------------------
