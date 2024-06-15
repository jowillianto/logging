#include <chrono>
#include <concepts>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <source_location>
import moderna.logging;

int main() {
  // std::fstream file ("default.log", std::ios_base::out);
  // for (int i = 0; i < 1000000; i += 1) {
  //   file << std::format("[WARN ][2024-05-24T16:07+0900][int main():26	] Hello Logger {}", i) <<
  //   std::endl;
  // }
  auto beg = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < 1000000; i += 1) {
    std::cout<<std::format("{} {} Hello\n", i, i);
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - beg) << "\n";
}