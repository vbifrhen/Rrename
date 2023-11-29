#include <filesystem>
#include <regex>
#include <iostream>

void rename_files(const std::filesystem::path& dir, const std::string& pattern, const std::string& new_name, bool is_regex) {
 std::regex regex_pattern(pattern);
 for (const auto& entry : std::filesystem::recursive_directory_iterator(dir)) {
     if (entry.is_regular_file()) {
         std::string filename = entry.path().filename().string();
         if (is_regex ? std::regex_search(filename, regex_pattern) : filename == pattern) {
             std::string new_filename = std::regex_replace(filename, regex_pattern, new_name);
             std::filesystem::rename(entry.path(), dir / new_filename);
         }
     }
 }
}

int main(int argc, char* argv[]) {
 if (argc != 4 && argc != 5) {
     std::cerr << "Usage: " << argv[0] << " <directory> <pattern> <new_name> [-r]" << std::endl;
     return 1;
 }
 bool is_regex = argc == 5 && std::string(argv[4]) == "-r";
 rename_files(argv[1], argv[2], argv[3], is_regex);
 return 0;
}
