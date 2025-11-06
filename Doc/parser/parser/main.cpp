#include <iostream>
#include <fstream>
#include <sstream>

#include "Database.h"
#include "Tokenizer.h"

int main() {

    Database d;

    std::vector<std::string> value = d.GetData("propriety02");
    for (auto v: value) {
        std::cout << "Value: " << v << std::endl;
    }
    return 0;
}
