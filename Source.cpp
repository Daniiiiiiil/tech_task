#include <iostream>
using namespace std;

class PathFind {
private:
    int *nodes;
public:
    PathFind(int N) {
        nodes = new int[N];
        for (int n = 0; n < N; n++) {
            nodes[n] = n;
        }
    }
    void n_union(int p, int q) {
        int pNode = nodes[p];
        int qNode = nodes[q];
        for (int n = 0; n < sizeof(nodes); n++) {
            if (nodes[n] == qNode) {
                nodes[n] = pNode;
            }
        }
    }
    bool connected(int p, int q) {
        return nodes[p] == nodes[q];
    }
};

class Matrix {
private:
    int i, j;
    int** matrix;

    int check_size(int l) {
        while (l <= 2 && l >= 50) {
            cout << "Incorrect input, try again (from 2 to 50): ";
            cin >> l;
        }
        return l;
    }
    void get_unions(PathFind p) {
        for (int n = 0; n < i; n++) {
            for (int m = 0; m < j - 1; m++) {
                if (matrix[n][m] == matrix[n][m + 1]) {
                    p.n_union(matrix[n][m], matrix[n][m + 1]);
                }
            }
        }
        for (int n = 0; n < i - 1; n++) {
            for (int m = 0; m < j; m++) {
                if (matrix[n][m] == matrix[n + 1][m]) {
                    p.n_union(matrix[n][m], matrix[n + 1][m]);
                }
            }
        }
    }
public:
    Matrix(int rows, int columns){
        i = check_size(rows);
        j = check_size(columns);
        matrix = new int* [i];
        for (int n = 0; n < i; n++)
            matrix[n] = new int[j];
    }
    void fill_manual() {
        for (int n = 0; n < i; n++) {
            for (int m = 0; m < j; m++) {
                cout << n + 1 << "." << m + 1 << ": ";
                cin >> matrix[n][m];
                while (matrix[n][m] != 0 && matrix[n][m] != 1) {
                    cout << "Incorret input, try again (0 or 1): ";
                    cin >> matrix[n][m];
                }
            }
        }
    }
    void give_matrix(int **mtr, int r, int c) {
        for (int n = 0; n < i; n++) {
            for (int m = 0; m < j; m++) {
                matrix[n][m] = mtr[n][m];
            }
        }
    }
    void fill_random() {
        for (int n = 0; n < i; n++) {
            for (int m = 0; m < j; m++) {
                matrix[n][m] = rand() % 2;
            }
        }
    }
    void print() {
        for (int n = 0; n < i; n++) {
            for (int m = 0; m < j; m++) {
                cout << matrix[n][m] << "\t";
            }
            cout << "\n" << endl;
        }
    }
    bool boolean() {
        PathFind q1(i * j);
        get_unions(q1);
        return q1.connected(matrix[0][0], matrix[i - 1][j - 1]);
    }
};

int main() {
    Matrix m1(10,10);
    m1.fill_random();
    cout << "Does random maze 10x10 have a path: " << m1.boolean() << "\n" << endl;
    Matrix m2(2, 2);
    m2.fill_random();
    cout << "Does random maze 2x2 have a path: " << m2.boolean() << "\n" << endl;
    Matrix m3(50, 50);
    m3.fill_random();
    cout << "Does random maze 50x50 have a path: " << m3.boolean() << "\n" << endl;
    Matrix m4(5, 10);
    m4.fill_random();
    cout << "Does random maze 5x10 have a path: " << m4.boolean() << "\n" << endl;

    cout << "\n";
    Matrix m5(5, 5);
    int arr1[25] = { 1,1,0,0,0, 0,1,0,0,0, 1,1,0,0,0, 1,1,1,1,1, 0,0,0,0,1 };
    int **mtrx1 = new int* [5];
    int a = 0;
    for (int i = 0; i < 5; i++){
        mtrx1[i] = new int[5];
        for (int j = 0; j < 5; j++){
            mtrx1[i][j] = arr1[a];
            a++;
        }
    }
    m5.give_matrix(mtrx1,5,5);
    cout << "Does given maze 5x5 have a path: " << m5.boolean() << "\n" << endl;
    Matrix m6(2, 2);
    int arr[4] = { 0,0,0,0 };
    int** mtrx = new int* [2];
    a = 0;
    for (int i = 0; i < 2; i++) {
        mtrx[i] = new int[2];
        for (int j = 0; j < 2; j++) {
            mtrx[i][j] = arr[a];
            a++;
        }
    }
    m6.give_matrix(mtrx, 2, 2);
    cout << "Does given maze 2x2 have a path: " << m6.boolean() << "\n" << endl;

    return 0;
}