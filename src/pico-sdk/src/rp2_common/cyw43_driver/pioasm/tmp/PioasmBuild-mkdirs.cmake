# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/pico-sdk/tools/pioasm"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/pioasm"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/pico-sdk/src/rp2_common/cyw43_driver/pioasm"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/pico-sdk/src/rp2_common/cyw43_driver/pioasm/tmp"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
