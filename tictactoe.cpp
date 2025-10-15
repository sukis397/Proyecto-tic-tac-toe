#include <iostream>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];
char player1 = 'X';
char player2 = 'O';


void logic_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}


void show_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << endl;
        if (i < SIZE - 1) cout << "---+----+---" << endl;
    }
}


void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void clear_buff() {
    cin.clear();
    cin.ignore(10000, '\n');
}


bool win(char turn) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == turn && board[i][1] == turn && board[i][2] == turn) return true;
        if (board[0][i] == turn && board[1][i] == turn && board[2][i] == turn) return true;
    }
    if ((board[0][0] == turn && board[1][1] == turn && board[2][2] == turn) ||
        (board[0][2] == turn && board[1][1] == turn && board[2][0] == turn)) return true;
    return false;
}


bool tie() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}


void playing(char turn) {
    int position;
    bool valid = false;

    while (!valid) {
        clear();
        cout << "Jugador " << turn << " seleccione una posicion (1-9):" << endl;
        cout << "Posiciones:" << endl
             << " 1 2 3 " << endl
             << " 4 5 6 " << endl
             << " 7 8 9 " << endl;
        show_board();

        cin >> position;

        if (cin.fail()) { 
            clear_buff();
            cout << "Entrada invalida. Ingresa un numero entre 1 y 9." << endl;
            cin.get();
            continue;
        }

        if (position < 1 || position > 9) { 
            cout << "Posicion fuera de rango. Intenta de nuevo." << endl;
            clear_buff();
            cin.get();
            continue;
        }

        int row = (position - 1) / SIZE;
        int col = (position - 1) % SIZE;

        if (board[row][col] != ' ') { 
            cout << "Posicion ocupada. Intenta de nuevo." << endl;
            clear_buff();
            cin.get();
            continue;
        }

        
        board[row][col] = turn;
        valid = true;
    }
}


bool again() {
    char response;
    while (true) {
        cout << "¿Jugar de nuevo? (s/n): ";
        cin >> response;

        if (cin.fail()) {
            clear_buff();
            continue;
        }

        if (response == 's' || response == 'S') {
            return true;
        } else if (response == 'n' || response == 'N') {
            cout << "¡Gracias por jugar!" << endl;
            return false;
        } else {
            cout << "Entrada invalida. Ingresa 's' o 'n'." << endl;
            clear_buff();
        }
    }
}


int main() {
    bool repetir = false;
    do {
        logic_board();        
        char turn = player1; 
        bool end = false;

        do {
            playing(turn);
            if (win(turn)) {
                end = true;
                clear();
                show_board();
                cout << "Jugador " << turn << " ¡gana!" << endl;
            } else if (tie()) {
                end = true;
                clear();
                show_board();
                cout << "¡Empate!" << endl;
            } else {
                turn = (turn == player1) ? player2 : player1;
            }
        } while (!end);

        repetir = again(); 

    } while (repetir);

    return 0;

}
