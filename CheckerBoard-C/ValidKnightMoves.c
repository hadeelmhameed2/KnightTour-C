#include "Mergedheader.h"

int IsValidPosition(int row, int col) {
    return (row >= 0 && row < N && col >= 0 && col < N);
}

chessPosArray*** ValidKnightMoves(void) {
    /* Knight deltas (start with “two up, one right”, clockwise) */
    const int drow[8] = { -2, -1, +1, +2, +2, +1, -1, -2 };
    const int dcol[8] = { +1, +2, +2, +1, -1, -2, -2, -1 };

    chessPosArray*** moves = (chessPosArray***)malloc(N * sizeof(*moves));
    if (!moves) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }

    for (int r = 0; r < N; ++r) {
        moves[r] = (chessPosArray**)malloc(N * sizeof(*moves[r]));
        if (!moves[r]) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }

        for (int c = 0; c < N; ++c) {
            chessPosArray* cell = (chessPosArray*)calloc(1, sizeof(*cell));
            if (!cell) { fprintf(stderr, "calloc failed\n"); exit(EXIT_FAILURE); }

            /* count possible moves */
            unsigned cnt = 0;
            for (int k = 0; k < 8; ++k) {
                int nr = r + drow[k], nc = c + dcol[k];
                if (IsValidPosition(nr, nc)) ++cnt;
            }

            cell->size = cnt;
            if (cnt) {
                cell->position = (chessPos*)malloc(cnt * sizeof(chessPos));
                if (!cell->position) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }

                unsigned idx = 0;
                for (int k = 0; k < 8; ++k) {
                    int nr = r + drow[k], nc = c + dcol[k];
                    if (IsValidPosition(nr, nc)) {
                        cell->position[idx][0] = (char)('A' + nr);
                        cell->position[idx][1] = (char)('1' + nc);
                        ++idx;
                    }
                }
            }
            moves[r][c] = cell;
        }
    }
    return moves;
}

void FreeKnightMoves(chessPosArray*** matrix) {
    if (!matrix) return;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (matrix[r][c]) {
                free(matrix[r][c]->position);
                free(matrix[r][c]);
            }
        }
        free(matrix[r]);
    }
    free(matrix);
}
