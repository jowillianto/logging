import moderna.test_lib;
import moderna.logging;
import moderna.thread_plus;
#include <chrono>
#include <format>
#include <fstream>
#include <iostream>

int main() {
  std::fstream new_file{"default.log", std::ios_base::out};
  auto logger = moderna::logging::Logger{
    moderna::logging::SyncLogger{
      moderna::logging::DefaultPipe{
        moderna::logging::StreamEmitter{new_file}, 
        moderna::logging::DefaultFormatter{}
      }
    }
  };
  auto beg = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 1000000; i += 1) {
    logger.info(std::format("Hello {}", i));
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - beg) << "\n";
  // auto pool = moderna::thread_plus::pool::Pool{10};
  // auto log_count = 1000000;
  // auto start_sig = moderna::thread_plus::channel::Channel<void>{};
  // for (int i = 0; i < log_count; i += 1) {
  //   auto _ = pool.add_task([&logger, &start_sig]() {
  //     auto _ = start_sig.recv();
  //     std::this_thread::sleep_for(
  //       std::chrono::microseconds{moderna::test_lib::random_integer(100, 200)}
  //     );
  //     auto random_f = moderna::test_lib::random_integer(0, 4);
  //     if (random_f == 0) {
  //       logger.debug(moderna::test_lib::random_string(20));
  //     } else if (random_f == 1) {
  //       logger.info(moderna::test_lib::random_string(20));
  //     } else if (random_f == 2) {
  //       logger.warning(moderna::test_lib::random_string(20));
  //     } else if (random_f == 3) {
  //       logger.error(moderna::test_lib::random_string(20));
  //     } else if (random_f == 4) {
  //       logger.fatal(moderna::test_lib::random_string(20));
  //     }
  //   });
  // }
  // start_sig.send(log_count);
  // pool.join();
}