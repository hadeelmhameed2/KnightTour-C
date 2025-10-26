#include "Mergedheader.h"

/* Helpers for debugging (optional) */
void PrintPath(chessPos path[], int length) {
    for (int i = 0; i < length; ++i) {
        printf("%c%c%s", path[i][0], path[i][1], (i + 1 < length) ? " -> " : "\n");
    }
}

treeNode* createTreeNode(chessPos* position) {
    treeNode* n = (treeNode*)malloc(sizeof(*n));
    if (!n) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }
    n->position[0] = (*position)[0];
    n->position[1] = (*position)[1];
    n->next_possible_position.head = n->next_possible_position.tail = NULL;
    return n;
}

void addTreeNodeToList(treeNodeList* list, treeNode* node) {
    treeNodeListCell* cell = (treeNodeListCell*)malloc(sizeof(*cell));
    if (!cell) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }
    cell->node = node;
    cell->next = NULL;
    if (!list->head) list->head = list->tail = cell;
    else { list->tail->next = cell; list->tail = cell; }
}

int allVisited(int visited[N][N]) {
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            if (!visited[r][c]) return 0;
    return 1;
}

chessPosArray*** findPaths(treeNode* cur, int visited[N][N], chessPosArray*** valid_moves) {
    if (!cur) return valid_moves;

    int r = cur->position[0] - 'A';
    int c = cur->position[1] - '1';

    if (allVisited(visited)) return valid_moves;

    visited[r][c] = 1;

    chessPosArray* moves = valid_moves[r][c];
    for (unsigned i = 0; i < moves->size; ++i) {
        int nr = moves->position[i][0] - 'A';
        int nc = moves->position[i][1] - '1';
        if (IsValidPosition(nr, nc) && !visited[nr][nc]) {
            treeNode* child = createTreeNode(&moves->position[i]);
            addTreeNodeToList(&cur->next_possible_position, child);
            findPaths(child, visited, valid_moves);
        }
    }

    visited[r][c] = 0;
    return valid_moves;
}

pathTree FindAllPossibleKnightPaths(chessPos* startingPosition, chessPosArray*** valid_moves) {
    pathTree tree;
    int visited[N][N] = { 0 };

    tree.root = createTreeNode(startingPosition);
    valid_moves = findPaths(tree.root, visited, valid_moves);

    /* We used valid_moves only to build the tree; can free now. */
    FreeKnightMoves(valid_moves);
    return tree;
}

/* Free tree */
void FreeTreeNodeList(treeNodeListCell* cell) {
    while (cell) {
        treeNodeListCell* next = cell->next;
        FreeTreeNode(cell->node);
        free(cell);
        cell = next;
    }
}
void FreeTreeNode(treeNode* node) {
    if (!node) return;
    FreeTreeNodeList(node->next_possible_position.head);
    free(node);
}
void FreeTree(pathTree* tree) {
    if (tree && tree->root) FreeTreeNode(tree->root);
}
