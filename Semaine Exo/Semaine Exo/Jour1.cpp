#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Tokenizer.h"

static std::string readFileOrEmpty(const std::string& path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in) return {};
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

static const char* tokenTypeName(Tokenizer::TokenType t) {
    switch (t) {
    case Tokenizer::Invalid:     return "Invalid";
    case Tokenizer::Colon:       return "Colon";
    case Tokenizer::ParenOpen:   return "ParenOpen";
    case Tokenizer::ParenClose:  return "ParenClose";
    case Tokenizer::BrackOpen:   return "BrackOpen";
    case Tokenizer::BrackClose:  return "BrackClose";
    case Tokenizer::Slash:       return "Slash";
    case Tokenizer::UnSlash:     return "UnSlash";
    case Tokenizer::Comma:       return "Comma";
    default:                     return "Unknown";
    }
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);

    std::string source;
    if (argc >= 2) {
        source = readFileOrEmpty(argv[1]);
        if (source.empty()) {
            std::cerr << "[Erreur] Impossible de lire le fichier: " << argv[1] << "\n";
            return 1;
        }
        std::cout << "=== Lecture depuis le fichier: " << argv[1] << " ===\n";
    }
    else {
        source = R"( 
        { fiou: bar, / test }
        blob: /, {hello}, \truc\, (je cite "supercalifragilistique")
    )";
        std::cout << "=== Demo (aucun fichier) ===\n";
    }

    Tokenizer tz;
    std::vector<Tokenizer::Token> tokens = tz.tokenize(source);

    std::cout << "=== Resultat du lexing ===\n";
    for (const auto& tok : tokens) {
        std::cout << "Value: \"" << tok.value << "\""
            << "   Type: " << tokenTypeName(tok.type) << "\n";
    }
    std::cout << "==========================\n";

    return 0;
}
