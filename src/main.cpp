#include "pico/stdlib.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <vector>

#define LED_GREEN 15
#define LED_RED 14
#define BUTTON_1 16
#define BUTTON_2 17
#define GPIO_FALLING 0x04

class CurrentPlayer {
public:
  CurrentPlayer()
      : player_(1), symbol_('X'), row_(0), col_(0), led_(LED_GREEN) {
    TurnOnGreenLed();
    TurnOffRedLed();
  }
  void TurnOnGreenLed() { gpio_put(LED_GREEN, true); }
  void TurnOnRedLed() { gpio_put(LED_RED, true); }
  void TurnOffGreenLed() { gpio_put(LED_GREEN, false); }
  void TurnOffRedLed() { gpio_put(LED_RED, false); }
  // Function to switch between players
  void SwitchPlayer() {
    if (player_ == 1) {
      player_ = 2;
      symbol_ = 'O';
      led_ = (LED_RED);
      col_ = 0;
      row_ = 0;
      TurnOffGreenLed();
      TurnOnRedLed();
    } else {
      player_ = 1;
      symbol_ = 'X';
      led_ = (LED_GREEN);
      col_ = 0;
      row_ = 0;
      TurnOffRedLed();
      TurnOnGreenLed();
    }
  }
  // Getters for the player and symbol
  int GetPlayer() const { return player_; }
  char GetSymbol() const { return symbol_; }

  // Getters for the current row and column
  int row() const { return row_; }
  int col() const { return col_; }

  // Function for moving the selected square
  void Move() {
    if (col_ < 2) {
      ++col_;
    } else if (row_ < 2) {
      ++row_;
      col_ = 0;
    } else {
      row_ = 0;
      col_ = 0;
    }
    PrintSelectedSquare();
  }

  // Function for printing the selected square
  void PrintSelectedSquare() {
    printf("Player %d is currently on square (%d, %d).\n", player_, row_, col_);
  }

private:
  int player_;
  char symbol_;
  int row_;
  int col_;
  int led_;

  // Function to move to the next cell
};

class TicTacToe {
public:
  TicTacToe() : board_(3, std::vector<char>(3, ' ')), current_player_() {}
  void MoveSelector() { current_player_.Move(); }

  void MakeMove() {
    if (board_[current_player_.row()][current_player_.col()] != ' ') {
      std::cout
          << "this cell is already occupied. please choose a different cell."
          << std::endl;
      return;
    }
    // place the player's symbol in the cell
    board_[current_player_.row()][current_player_.col()] =
        current_player_.GetSymbol();
    PrintGameBoard();
    current_player_.SwitchPlayer();
  }

  void PrintGameBoard() {
    std::cout << std::endl << "\t \t|\t \t|\t \t\n";
    std::cout << "\t" << board_[0][0] <<"\t|\t" << board_[0][1] << "\t|\t" << board_[0][2] << "\t\n";
    std::cout << "________________|_______________|_______________\n";
    std::cout << "\t \t|\t \t|\t \t\n";
    std::cout << "\t" << board_[1][0] <<"\t|\t" << board_[1][1] << "\t|\t" << board_[1][2] << "\t\n";
    std::cout << "________________|_______________|_______________\n";
    std::cout << "\t \t|\t \t|\t \t\n";
    std::cout << "\t" << board_[2][0] <<"\t|\t" << board_[2][1] << "\t|\t" << board_[2][2] << "\t\n";
  }

private:
  std::vector<std::vector<char>> board_;
  CurrentPlayer current_player_;
};

// Make global instances of tic-tac-toe board

TicTacToe tic_tac_toe;

void SetupHardware() {
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

// Debounce control
uint32_t time_current = to_ms_since_boot(get_absolute_time());
const int debounce_delay = 80;

void HandleButtonPress(uint gpio) {
  if (gpio == BUTTON_1) {
    tic_tac_toe.MoveSelector();
  } else {
    tic_tac_toe.MakeMove();
  }
}

void button_debouncer(uint gpio, uint32_t events) {
  // sleep for 20 ms for debouncer
  if (((to_ms_since_boot(get_absolute_time())) - time_current) >
      debounce_delay) {
    time_current = to_ms_since_boot(get_absolute_time());
    HandleButtonPress(gpio);
  }
  return;
}

int main() {
  SetupHardware();
  gpio_set_irq_enabled_with_callback(BUTTON_1, GPIO_FALLING, 1,
                                     button_debouncer);
  gpio_set_irq_enabled_with_callback(BUTTON_2, GPIO_FALLING, 1,
                                     button_debouncer);
  gpio_put(LED_GREEN, true);                                   
  while (true) {
    // Do game logic here
    // Switch players after each turn
  }
  return 0;
}