#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
  for (const fs::directory_entry& entry :
       fs::recursive_directory_iterator(fs::current_path() / "tst")) {
    std::cout << entry.path() << std::endl;
  }
}