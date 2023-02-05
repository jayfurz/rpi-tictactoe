# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/pico-sdk/tools/elf2uf2"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/elf2uf2"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/elf2uf2"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/elf2uf2/tmp"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/elf2uf2/src/ELF2UF2Build-stamp"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/elf2uf2/src"
  "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/elf2uf2/src/ELF2UF2Build-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/elf2uf2/src/ELF2UF2Build-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/justi/OneDrive/Documents/masters_courses/ece_520/sp23-e520-lab3-rpi-tic-tac-toe-jayfurz/src/elf2uf2/src/ELF2UF2Build-stamp${cfgdir}") # cfgdir has leading slash
endif()
