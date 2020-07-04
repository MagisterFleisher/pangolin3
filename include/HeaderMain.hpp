#ifndef PANGOLIN_HEADERMAIN_HPP
#define PANGOLIN_HEADERMAIN_HPP

#include <algorithm>
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Types.hpp"

bool CheckFile(const std::string& full_name) { std::cout << "Called CheckFile" << "\n";
    if(std::filesystem::is_character_file(full_name) && std::filesystem::exists(full_name)) {
        return true; } else {
        if(!std::filesystem::is_character_file(full_name)) {
            std::cerr << "CheckFile: Not character file: "  << full_name; }
        if(!std::filesystem::exists(full_name)) { 
            std::cerr << "CheckFile: Does not exist:     " << full_name; }
        return false; } }

#endif//PANGOLIN_HEADERMAIN_HPP