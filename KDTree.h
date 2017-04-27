/*
 * KDTree.h
 *
 *  Created on: Apr 27, 2017
 *      Author: gleit
 */

#ifndef KDTREE_H_
#define KDTREE_H_

#include "SPPoint.h"

typedef struct sp_kd_tree_node KDTreeNode;

void Init(SPPoint** arr, int size);

void KNearestNeighborSearch(KDTreeNode curr, SPBPQueue* bpq, SPPoint* testPoint);

#endif /* KDTREE_H_ */
