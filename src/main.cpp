#include <iostream>
#include <vector>
#include "pico/stdlib.h"
#define LED_GREEN 15
#define LED_RED 14
#define BUTTON_1 12
#define BUTTON_2 13

std::vector<std::vector<char>> board(3,std::vector<char>(3, ' '));

class CurrentPlayer {
    public:
    CurrentPlayer() : current_player_(1),
    player_symbol_('X'){}

    void SwitchPlayer(){
        if (current_player_ == 1) {
            current_player_ = 2;
            player_symbol_ = 'O';
        } else {
            current_player_ = 1;
            player_symbol_ = 'X';
        }
    }
    int current_player() const { return current_player_; }
    char player_symbol() const { return player_symbol_; }

    private:
    int current_player_;
    char player_symbol_;
};

class TicTacToe {
    public:
    TicTacToe()
    : board_(3, std::vector<char>(3, ' ')),
    current_player_() {}

    void MakeMove(int row, int col)
    {
        if (board[row][col] != ' '){
        std::cout << "this cell is already occupied. please choose a different cell." << std::endl;
        return;
    }
    // place the player's symbolin the cell
    board_[row][col] = current_player_.player_symbol();
    current_player_.SwitchPlayer();
    }

    private:
    std::vector<std::vector<char>> board_;
    CurrentPlayer current_player_;
};


void SetupHardware(){
    stdio_init_all();
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(BUTTON_1);
    gpio_init(BUTTON_2);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(BUTTON_1, GPIO_IN);
    gpio_set_dir(BUTTON_2, GPIO_IN);
    gpio_pull_down(BUTTON_1);
    gpio_pull_down(BUTTON_2);
}

int main() {
    TicTacToe tic_tac_toe;
    SetupHardware();
    tic_tac_toe.MakeMove(0, 0);
    while (true) {
    // Do game logic here
    
    // Switch players after each turn
    }
    return 0;
}