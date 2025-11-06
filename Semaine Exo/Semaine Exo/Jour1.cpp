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
    case Tokenizer::String:      return "String";
    case Tokenizer::Colon:       return "Colon";
    case Tokenizer::ParenOpen:   return "ParenOpen";
    case Tokenizer::ParenClose:  return "ParenClose";
    case Tokenizer::BrackOpen:   return "BrackOpen";
    case Tokenizer::BrackClose:  return "BrackClose";
    case Tokenizer::Slash:       return "Slash";
    case Tokenizer::UnSlash:     return "UnSlash";
    case Tokenizer::Quote:       return "Quote";
    case Tokenizer::Comma:       return "Comma";
    default:                     return "Unknown";
    }
}

static void printSegment(const Tokenizer::Segment& seg, const std::vector<Tokenizer::Token>& tokens, int depth = 0) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << "- Segment (";
    std::cout << tokenTypeName(seg.kindOpen) << " -> " << tokenTypeName(seg.kindClose) << ")";
    std::cout << " [tokens " << seg.startIndexTok << " a " << seg.endIndexTok << "]\n";

    std::string text;
    for (size_t i = seg.startIndexTok; i <= seg.endIndexTok && i < tokens.size(); ++i) {
        text += tokens[i].value + " ";
    }
    std::cout << indent << "  Contenu : \"" << text << "\"\n";

    for (const auto& child : seg.children) {
        printSegment(child, tokens, depth + 1);
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
        std::cout << "=== Demo integree (aucun fichier passe en argument) ===\n";
    }

    Tokenizer tz;

    auto tokens = tz.tokenize(source);

    std::cout << "\n=== TOKENS ===\n";
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << i << ": \"" << tokens[i].value << "\""
            << "  -> " << tokenTypeName(tokens[i].type) << "\n";
    }

    auto segments = tz.segmentize(tokens);

    std::cout << "\n=== SEGMENTS ===\n";
    if (segments.empty()) {
        std::cout << "(aucun segment trouve)\n";
    }
    else {
        for (const auto& seg : segments) {
            printSegment(seg, tokens);
        }
    }

    std::cout << "\n==========================\n";
    return 0;
}
