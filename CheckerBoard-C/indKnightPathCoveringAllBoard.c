#include "Mergedheader.h"

/* Simple helpers */
int ComparePositions(chessPos p1, chessPos p2) {
    return p1[0] == p2[0] && p1[1] == p2[1];
}
int IsVisited(chessPos pos, chessPos visited[], int size) {
    for (int i = 0; i < size; ++i) if (ComparePositions(pos, visited[i])) return 1;
    return 0;
}
void AddVisited(chessPos pos, chessPos visited[], int* size) {
    visited[*size][0] = pos[0];
    visited[*size][1] = pos[1];
    (*size)++;
}

void PrintFullPath(chessPos path[], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%c%c%s", path[i][0], path[i][1], (i + 1 < len) ? " -> " : "\n");
    }
}

/* Linked-list ops (append/remove from tail) */
void AppendToList(chessPosList** list, chessPos position) {
    if (!*list) {
        *list = (chessPosList*)malloc(sizeof(**list));
        if (!*list) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }
        (*list)->head = (*list)->tail = NULL;
    }
    chessPosNode* node = (chessPosNode*)malloc(sizeof(*node));
    if (!node) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }
    node->position[0] = position[0];
    node->position[1] = position[1];
    node->next = NULL;

    if ((*list)->tail) (*list)->tail->next = node;
    else (*list)->head = node;
    (*list)->tail = node;
}

void RemoveLastFromList(chessPosList** list) {
    if (!list || !*list || !(*list)->head) return;
    if ((*list)->head == (*list)->tail) {
        free((*list)->head);
        (*list)->head = (*list)->tail = NULL;
        return;
    }
    chessPosNode* cur = (*list)->head;
    while (cur->next != (*list)->tail) cur = cur->next;
    free((*list)->tail);
    (*list)->tail = cur;
    cur->next = NULL;
}

int TraverseTreePaths(treeNode* node,
    chessPos path[], int pathLen,
    chessPos visited[], int* visitedSize,
    int totalCells,
    chessPosList** ppList)
{
    if (!node) return FAIL;

    /* Add current */
    path[pathLen][0] = node->position[0];
    path[pathLen][1] = node->position[1];
    AddVisited(node->position, visited, visitedSize);
    AppendToList(ppList, node->position);
    ++pathLen;

    if (pathLen == totalCells) {
        /* Show final board & also save to file */
        PrintFullPath(path, pathLen);
        PrintChessBoard(*ppList);
        SaveBoardToFile("knight_tour.txt", *ppList);
        return SUCCESS;
    }

    /* Go deeper */
    for (treeNodeListCell* cur = node->next_possible_position.head; cur; cur = cur->next) {
        if (!IsVisited(cur->node->position, visited, *visitedSize)) {
            if (TraverseTreePaths(cur->node, path, pathLen, visited, visitedSize, totalCells, ppList))
                return SUCCESS;
        }
    }

    /* Backtrack */
    (*visitedSize)--;
    RemoveLastFromList(ppList);
    return FAIL;
}

chessPosList* FindFullPath(pathTree* tree) {
    if (!tree || !tree->root) return NULL;

    chessPos path[BOARD_SIZE];
    chessPos visited[BOARD_SIZE];
    int visitedSize = 0;
    chessPosList* pathList = NULL;

    if (!TraverseTreePaths(tree->root, path, 0, visited, &visitedSize, BOARD_SIZE, &pathList)) {
        printf("No knight's tour\n");
        FreeList(pathList);
        return NULL;
    }
    return pathList;
}
