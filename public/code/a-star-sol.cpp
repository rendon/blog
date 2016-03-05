#include <bits/stdc++.h>
using namespace std;

/**
 * Struct that stores the state of the board at some point in the solution tree.
 */
struct Node {
    int g; // Backward cost or moves to get to this state: g(n).
    int f; // Forward cost or approx. number of moves to reach the goal: f(n).
    int r, c; // Position of the empty tile in the board.
    int board[3][3];
    Node() : g(0) {}

    /** Determines if the current board is the goal board.*/
    bool isGoal() const {
        if (board[2][2] != 0) { return false; }

        int v = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if ((i != 2 || j != 2) && (board[i][j] != v)) {
                    return false;
                }
                v++;
            }
        }

        return true;
    }

    /** Priority function. NOTE: f > that.f is not enough.*/
    bool operator<(const Node &that) const {
        return f > that.f || (f == that.f && g > that.g);
    }

    /** Returns a unique integer key that identifies this particular node.*/
    long long getKey() const {
        long long key = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                key = key * 10 + board[i][j];
            }
        }

        return key;
    }

};

/**
 *  Determines if the given board is solvable, for the particular case of the 
 *  8 puzzle, a board is solvable if the number of inversions is even. An
 *  inversion is a pair of tiles (non-empty tiles) A and B such that A > B
 *  and A comes before B in the board.
 */
bool isSolvable(int board[3][3]) {
    int inversions = 0;
    for (int i = 0; i < 9; i++) {
        int r = i / 3, c = i % 3;
        if (board[r][c] != 0) {
            for (int j = 0; j < i; j++) {
                int p = j / 3, q = j % 3;
                if (board[p][q] != 0 && board[p][q] > board[r][c]) {
                    inversions++;
                }
            }
        }
    }
    return inversions % 2 == 0;
}

/**
 *  Computes the Manhattan distance for each tile in the board (except the empty
 *  tile) and returns the sum of those distances, the heuristic function.
 */
int manhattan(int board[3][3]) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0) {
                int r = (board[i][j] - 1) / 3;
                int c = (board[i][j] - 1) % 3;
                sum += abs(r - i) + abs(c - j);
            }
        }
    }
    return sum;
}

/**
 * A* Algorithm.
 */
int solve(Node &initial) {
    map<long long, bool> visited; // Used to avoid visiting a node twice.
    priority_queue<Node> Q;
    Q.push(initial);
    visited[initial.getKey()] = true;

    initial.f = manhattan(initial.board);
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    while (!Q.empty()) {
        Node node = Q.top();
        Q.pop();
        if (node.isGoal()) {
            return node.g;
        }

        // Try all the possible moves from this node.
        for (int i = 0; i < 4; i++) {
            Node neighbor = node;
            int r = node.r + dr[i];
            int c = node.c + dc[i];
            if (r >= 0 && r < 3 && c >= 0 && c < 3) {
                swap(neighbor.board[node.r][node.c], neighbor.board[r][c]);

                // Recompute function g(n) and f(n)
                neighbor.g = node.g + 1;
                neighbor.f = node.g + manhattan(neighbor.board);

                neighbor.r = r;
                neighbor.c = c;
                long long key = neighbor.getKey();
                if (visited.count(key) == 0) {
                    visited[key] = true;
                    Q.push(neighbor);
                }
            }
        }
    }

    return -1;
}

int main(int argc, char **argv) {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        Node init;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%d", &init.board[i][j]);
                if (init.board[i][j] == 0) {
                    init.r = i;
                    init.c = j;
                }
            }
        }

        printf("Case %d: ", tc);
        if (!isSolvable(init.board)) {
            printf("impossible\n");
        } else {
            printf("%d\n", solve(init));
        }
    }
    return EXIT_SUCCESS;
}
