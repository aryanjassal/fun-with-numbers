#define OOF_IMPL
#include "../include/oof.h"

#include <iostream>
#include <string>

int main() {
    std::cout << oof::fg_color({255, 100, 100}) << "This is red\n";
    
    return 0;
}
