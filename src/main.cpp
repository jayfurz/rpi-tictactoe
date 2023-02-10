#include "pico/stdlib.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <vector>

#define LED_GREEN 15
#define LED_RED 14
#define BUTTON_1 16
#define BUTTON_2 17
#define BUTTON_3 18
#define GPIO_FALLING 0x04
#define FLASH_DELAY 500

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
  void SwitchPlayer(bool reset = false) {
    if (reset) {
      player_ = 2;
      TurnOffGreenLed();
      TurnOffRedLed();
    }
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
  int GetLed() const { return led_; }

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
    return;
  }

  // Function for printing the selected square
  void PrintSelectedSquare() {
    printf("Player %d is currently on square (%d, %d).\n", player_, row_, col_);
    return;
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
  void MoveSelector() {
    if (!isGameOver) {
      current_player_.Move();
      PrintSelectedSquare();
    }
  }

  void MakeMove() {
    if (!isGameOver) {
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
      if (!CheckWinCondition()) {
        current_player_.SwitchPlayer();
      }
      return;
    }
  }

  void Reset() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board_[i][j] = ' ';
      }
    }
    current_player_.SwitchPlayer(true);
    isGameOver = false;
    printf("Game reset!");
  }

private:
  bool CheckWinCondition() {
    for (int i = 0; i < 3; i++) {
      if ((board_[i][0] == board_[i][1] && board_[i][1] == board_[i][2] &&
           board_[i][2] == current_player_.GetSymbol()) ||
          (board_[0][i] == board_[1][i] && board_[1][i] == board_[2][i] &&
           board_[2][i] == current_player_.GetSymbol()) ||
          (board_[0][0] == board_[1][1] && board_[1][1] == board_[2][2] &&
           board_[2][2] == current_player_.GetSymbol()) ||
          (board_[0][2] == board_[1][1] && board_[1][1] == board_[2][0] &&
           board_[2][0] == current_player_.GetSymbol())) {
        WinGame();
        isGameOver = true;
        return isGameOver;
      } else if (isTieGame()) {
        TieGame();
        isGameOver = true;
        return isGameOver;
      }
    }
    return false;
  }

  bool isTieGame() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board_[i][j] == ' ') {
          return false;
        }
      }
    }
    return true;
  }

  void TieGame() {
    printf("Tie game!");
    FlashBothPlayersLeds();
  }

  void WinGame() {
    printf("Player %d won!", current_player_.GetPlayer());
    FlashCurrentPlayerLed();
    return;
  }

  void FlashBothPlayersLeds() {
    int i = 0;
    while (true) {
      if (!gpio_get(BUTTON_3)) {
        gpio_put(LED_GREEN, false);
        gpio_put(LED_RED, false);
        busy_wait_ms(FLASH_DELAY);
        gpio_put(LED_GREEN, true);
        gpio_put(LED_RED, true);
        busy_wait_ms(FLASH_DELAY);
        i++;
      }
      else return;
    }
  }

  void FlashCurrentPlayerLed() {
    int current_led = current_player_.GetLed();
    int i = 0;
    while (true) {
      if (!gpio_get(BUTTON_3)) {
      gpio_put(current_led, false);
      busy_wait_ms(FLASH_DELAY);
      gpio_put(current_led, true);
      busy_wait_ms(FLASH_DELAY);
      i++;
      } else return;
    }
    return;
  }

  void PrintGameBoard() {
    std::cout << std::endl << "\t \t|\t \t|\t \t\n";
    std::cout << "\t" << board_[0][0] << "\t|\t" << board_[0][1] << "\t|\t"
              << board_[0][2] << "\t\n";
    std::cout << "________________|_______________|_______________\n";
    std::cout << "\t \t|\t \t|\t \t\n";
    std::cout << "\t" << board_[1][0] << "\t|\t" << board_[1][1] << "\t|\t"
              << board_[1][2] << "\t\n";
    std::cout << "________________|_______________|_______________\n";
    std::cout << "\t \t|\t \t|\t \t\n";
    std::cout << "\t" << board_[2][0] << "\t|\t" << board_[2][1] << "\t|\t"
              << board_[2][2] << "\t\n";
  }
  
  void PrintSelectedSquare() {
    std::cout << "\033[2J\033[1;1H";  // clear the console
    printf("Player %d is currently on square (%d, %d).\n", current_player_.GetPlayer(), current_player_.row(), current_player_.col());
    for (int i = 0; i < 3; ++i) {
        std::cout << std::endl << "\t \t|\t \t|\t \t\n";
        for (int j = 0; j < 3; ++j) {
            if (i == row_ && j == col_) {
                std::cout << "\t[" << board_[i][j] << "]\t";
            } else {
                std::cout << "\t" << board_[i][j] << "\t";
            }
            if (j != 2) {
                std::cout << "|";
            }
        }
        if (i != 2) {
            std::cout << "\n________________|_______________|_______________\n";
        }
    }
    std::cout << std::endl;
    busy_wait_ms(500000);  // wait for 0.5 second
}

  std::vector<std::vector<char>> board_;
  CurrentPlayer current_player_;
  bool isGameOver = false;
};

// Make global instances of tic-tac-toe board

TicTacToe tic_tac_toe;

void SetupHardware() {
  stdio_init_all();
  gpio_init(LED_RED);
  gpio_init(LED_GREEN);
  gpio_init(BUTTON_1);
  gpio_init(BUTTON_2);
  gpio_init(BUTTON_3);
  gpio_set_dir(LED_RED, GPIO_OUT);
  gpio_set_dir(LED_GREEN, GPIO_OUT);
  gpio_set_dir(BUTTON_1, GPIO_IN);
  gpio_set_dir(BUTTON_2, GPIO_IN);
  gpio_set_dir(BUTTON_3, GPIO_IN);
  gpio_pull_down(BUTTON_1);
  gpio_pull_down(BUTTON_2);
  gpio_pull_down(BUTTON_3);
}

// Debounce control
uint32_t time_current = to_ms_since_boot(get_absolute_time());
const int debounce_delay = 80;

void HandleButtonPress(uint gpio) {
  if (gpio == BUTTON_1) {
    return tic_tac_toe.MoveSelector();
  } else if (gpio == BUTTON_2) {
    return tic_tac_toe.MakeMove();
  } else { // Reset
    return tic_tac_toe.Reset();
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

void button_1_irq_handler(void) {
gpio_acknowledge_irq(BUTTON_1, GPIO_FALLING);
button_debouncer(BUTTON_1, GPIO_FALLING);
}

void button_2_irq_handler(void) {
gpio_acknowledge_irq(BUTTON_2, GPIO_FALLING);
button_debouncer(BUTTON_2, GPIO_FALLING);
}

void button_3_irq_handler(void) {
gpio_acknowledge_irq(BUTTON_3, GPIO_FALLING);
button_debouncer(BUTTON_3, GPIO_FALLING);
}

void initialize_buttons() {
// set up button 1 with a higher priority
gpio_add_raw_irq_handler_with_order_priority(BUTTON_1, button_1_irq_handler,
0x80);
// set up button 2 with a medium priority
gpio_add_raw_irq_handler_with_order_priority(BUTTON_2, button_2_irq_handler,
0x7F);
// set up button 3 with a lower priority
gpio_add_raw_irq_handler_with_order_priority(BUTTON_3, button_3_irq_handler,
0x70);
}

int main() {
  SetupHardware();
  initialize_buttons();
  gpio_put(LED_GREEN, true);
  while (true) {
    // Do game logic here
    // Switch players after each turn
  }
  return 0;
}
