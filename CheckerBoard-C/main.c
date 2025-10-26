#include "Mergedheader.h"

int main(void) {
    chessPos cell;
    pathTree tree;
    chessPosArray*** valid_moves = NULL;
    char buffer[32];

    /* Prompt & read */
    printf("Enter starting position (e.g., A1): ");
    if (!fgets(buffer, sizeof(buffer), stdin) || buffer[0] == '\n') {
        printf("Invalid input\n");
        return 1;
    }
    /* Normalize: two chars: letter+digit */
    cell[0] = (char)toupper((unsigned char)buffer[0]);
    cell[1] = buffer[1];

    if (!isalpha((unsigned char)cell[0]) || !isdigit((unsigned char)cell[1])) {
        printf("Invalid input\n");
        return 1;
    }

    if (!IsValidPosition(cell[0] - 'A', cell[1] - '1')) {
        printf("Invalid input\n");
        return 1;
    }

    /* Build moves -> tree */
    valid_moves = ValidKnightMoves();

    clock_t t0 = clock();
    tree = FindAllPossibleKnightPaths(&cell, valid_moves); /* frees valid_moves internally */

    chessPosList* full = FindFullPath(&tree);
    clock_t t1 = clock();

    if (full) {
        Display(full);
        SaveBoardToFile("knight_tour.txt", full);
        FreeList(full);
        printf("\nSaved to knight_tour.txt\n");
    }

    FreeTree(&tree);

    double secs = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("\nExecution time: %.3f s\n", secs);

#ifdef _WIN32
    printf("\n");
    system("pause");
#endif
    return 0;
}
