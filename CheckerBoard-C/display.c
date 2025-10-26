#include "Mergedheader.h"

/* Remove duplicates after first occurrence (stable) */
static int Cmp(chessPos a, chessPos b) {
    return (a[0] == b[0]) && (a[1] == b[1]);
}

void HandleDup(chessPosList* list) {
    if (!list || !list->head) return;
    for (chessPosNode* i = list->head; i; i = i->next) {
        chessPosNode* prev = i, * j = i->next;
        while (j) {
            if (Cmp(i->position, j->position)) {
                /* Remove j */
                prev->next = j->next;
                if (list->tail == j) list->tail = prev;
                free(j);
                j = prev->next;
            }
            else {
                prev = j;
                j = j->next;
            }
        }
    }
}

void PrintList(chessPosList* list) {
    for (chessPosNode* c = list ? list->head : NULL; c; c = c->next)
        printf("%c%c -> ", c->position[0], c->position[1]);
    printf("NULL\n");
}

void FreeList(chessPosList* list) {
    if (!list) return;
    chessPosNode* cur = list->head;
    while (cur) {
        chessPosNode* n = cur->next;
        free(cur);
        cur = n;
    }
    free(list);
}

/* Save current board view to a file */
void SaveBoardToFile(const char* filename, chessPosList* list) {
    if (!list || !filename) return;

    int board[N][N] = { 0 };
    int idx = 1;
    for (chessPosNode* c = list->head; c; c = c->next) {
        int r = c->position[0] - 'A';
        int d = c->position[1] - '1';
        if (IsValidPosition(r, d) && board[r][d] == 0) {
            board[r][d] = idx++;
        }
    }

    FILE* f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "Knight's Tour on a %dx%d Board\n\n", N, N);
    fprintf(f, "   ");
    for (int x = 1; x <= N; ++x) fprintf(f, "%2d ", x);
    fprintf(f, "\n");

    for (int r = 0; r < N; ++r) {
        fprintf(f, "%c|", 'A' + r);
        for (int c = 0; c < N; ++c) {
            if (board[r][c]) fprintf(f, "%2d|", board[r][c]);
            else             fprintf(f, "  |");
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

/* Pretty, colored board output for Windows (falls back to plain text elsewhere) */
void PrintChessBoard(chessPosList* list) {
    if (!list) return;

    /* Build numeric board */
    int board[N][N] = { 0 };
    int idx = 1;
    for (chessPosNode* c = list->head; c; c = c->next) {
        int r = c->position[0] - 'A';
        int d = c->position[1] - '1';
        if (IsValidPosition(r, d) && board[r][d] == 0) {
            board[r][d] = idx++;
        }
    }

#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD normal = 7, title = 10, axis = 11, cells = 14, border = 8;

    SetConsoleTextAttribute(h, title);
    printf("\nKnight's Tour on a %dx%d Board\n", N, N);

    SetConsoleTextAttribute(h, axis);
    printf("\n   ");
    for (int x = 1; x <= N; ++x) printf("%2d ", x);
    printf("\n");

    for (int r = 0; r < N; ++r) {
        SetConsoleTextAttribute(h, axis);
        printf("%c", 'A' + r);

        for (int c = 0; c < N; ++c) {
            SetConsoleTextAttribute(h, border);
            printf("|");
            if (board[r][c]) {
                SetConsoleTextAttribute(h, cells);
                printf("%2d", board[r][c]);
            }
            else {
                printf("  ");
            }
        }
        SetConsoleTextAttribute(h, border);
        printf("|");
        SetConsoleTextAttribute(h, normal);
        printf("\n");
    }
    SetConsoleTextAttribute(h, normal);
#else
    /* Non-Windows: plain output */
    printf("\nKnight's Tour on a %dx%d Board\n", N, N);
    printf("\n   ");
    for (int x = 1; x <= N; ++x) printf("%2d ", x);
    printf("\n");
    for (int r = 0; r < N; ++r) {
        printf("%c|", 'A' + r);
        for (int c = 0; c < N; ++c) {
            if (board[r][c]) printf("%2d|", board[r][c]);
            else             printf("  |");
        }
        printf("\n");
    }
#endif
}

/* High-level: show list before/after dedup, board, and free */
void Display(chessPosList* list) {
    if (!list) return;
    printf("\nPath (raw): ");
    PrintList(list);

    HandleDup(list);

    printf("Path (dedup): ");
    PrintList(list);

    PrintChessBoard(list);
}
