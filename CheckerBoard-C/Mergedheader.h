#pragma once
#ifndef MERGED_HEADER_H
#define MERGED_HEADER_H

/* Silence MSVC “unsafe” CRT warnings (strncpy etc.) */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* ========= Board / constants ========= */
#define N              5                  /* 5x5 board */
#define BOARD_SIZE     (N * N)
#define TRUE           1
#define FALSE          0
#define SUCCESS        1
#define FAIL           0

typedef char chessPos[2];

/* ========= Data structures ========= */
typedef struct _chessPosArray {
    unsigned int size;
    chessPos* position; /* dynamic array of size 'size' */
} chessPosArray;

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNodeList {
    treeNodeListCell* head;
    treeNodeListCell* tail;
} treeNodeList;

typedef struct _treeNode {
    chessPos position;
    treeNodeList next_possible_position;
} treeNode;

struct _treeNodeListCell {
    treeNode* node;
    treeNodeListCell* next;
};

typedef struct _pathTree {
    treeNode* root;
} pathTree;

typedef struct _chessPosNode {
    chessPos position;
    struct _chessPosNode* next;
} chessPosNode;

typedef struct _chessPosList {
    chessPosNode* head;
    chessPosNode* tail;
} chessPosList;

/* ========= API ========= */
/* board / moves */
int                IsValidPosition(int row, int col);
chessPosArray*** ValidKnightMoves(void);
void               FreeKnightMoves(chessPosArray*** matrix);

/* tree building */
treeNode* createTreeNode(chessPos* position);
void               addTreeNodeToList(treeNodeList* list, treeNode* node);
int                allVisited(int visited[N][N]);
chessPosArray*** findPaths(treeNode* currentNode, int visited[N][N], chessPosArray*** valid_moves);
pathTree           FindAllPossibleKnightPaths(chessPos* startingPosition, chessPosArray*** valid_moves);

/* tree traversal / solution */
int                ComparePositions(chessPos pos1, chessPos pos2);
int                IsVisited(chessPos pos, chessPos visited[], int size);
void               PrintFullPath(chessPos path[], int pathLen);
void               AddVisited(chessPos pos, chessPos visited[], int* size);

void               AppendToList(chessPosList** list, chessPos position);
void               RemoveLastFromList(chessPosList** list);

int                TraverseTreePaths(treeNode* node,
    chessPos path[], int pathLen,
    chessPos visited[], int* visitedSize,
    int totalCells,
    chessPosList** ppList);

chessPosList* FindFullPath(pathTree* tree);

/* display & utilities */
void               HandleDup(chessPosList* list);
void               PrintList(chessPosList* list);
void               FreeList(chessPosList* list);
void               Display(chessPosList* list);
void               PrintChessBoard(chessPosList* list);
void               SaveBoardToFile(const char* filename, chessPosList* list);

/* free tree */
void               FreeTreeNodeList(treeNodeListCell* cell);
void               FreeTreeNode(treeNode* node);
void               FreeTree(pathTree* tree);

#endif /* MERGED_HEADER_H */
