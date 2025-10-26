# ♞ Knight's Tour – Advanced C Final Project

This project solves the **Knight's Tour problem** on a 5×5 chessboard.  
It finds a complete path that allows a knight to visit every square **exactly once**, starting from any valid position (`A1`–`E5`).

---

## ✨ Features
- ✅ **Recursive backtracking** to find a full knight’s tour  
- ✅ **Tree structure** for all possible moves  
- ✅ **Colored console output** (Windows)  
- ✅ **Board visualization** with row/column labels  
- ✅ **Input validation** for A–E / 1–5  
- ✅ **Execution timer** (shows how long it took to find a tour)  
- ✅ **Saves output to file** → `knight_tour.txt`

---

## 📂 Project Structure
CheckerBoard-C/

│

├── include/

│ └── Mergedheader.h

│

├── src/

│ ├── main.c

│ ├── display.c

│ ├── ValidKnightMoves.c

│ ├── FindAllPossibleKnightPaths.c

│ └── FindKnightPathCoveringAllBoard.c

│

├── .gitignore

└── README.md

---

## 🧠 Concepts Used
- Dynamic memory allocation (`malloc`, `free`)
- Recursion and backtracking
- Linked lists and trees
- Input validation and buffer handling
- Console-based UI design
- File I/O for saving results

---

  ## 🖥 Example Output
Enter starting position (e.g., A1): A1
Knight's Tour on a 5x5 Board
   1  2  3  4  5
   
A| 1|20|17|12| 3|

B|16|11| 2| 7|18|

C|21|24|19| 4|13|

D|10|15| 6|23| 8|

E|25|22| 9|14| 5|


Saved to knight_tour.txt
Execution time: 0.383 s
