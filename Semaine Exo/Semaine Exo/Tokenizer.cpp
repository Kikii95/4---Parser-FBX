#include "Tokenizer.h"


std::vector<Tokenizer::Token> Tokenizer::tokenize(std::string source)
{
	std::vector<Token> tokens;

	const char* s = source.c_str();
	size_t i = 0, n = source.size();

	auto addToken = [&](const std::string v, TokenType t) {
		tokens.push_back(Token{ v, t });
		};

	while (i < n)
	{
		char c = s[i];

		if (isWhitespace(c)) {
			if (c == '\r' && i + 1 < n && s[i + 1] == '\n') {
				i += 2; continue;
			} 

			i++;
			continue;
		}

		switch (c) {
			case ':': addToken(":", TokenType::Colon); i++; continue;

			case '(': addToken("(", TokenType::ParenOpen); i++; continue;
			case ')': addToken(")", TokenType::ParenClose); i++; continue;

			case '{': addToken("{", TokenType::BrackOpen); i++; continue;
			case '}': addToken("}", TokenType::BrackClose); i++; continue;

			case '/': addToken("/", TokenType::Slash); i++; continue;
			case '\\': addToken("\\", TokenType::UnSlash); i++; continue;

			case '"': addToken("\"", TokenType::Quote); i++; continue;
			case ',': addToken(",", TokenType::Comma); i++; continue;
		}

		size_t start = i;
		auto isStop = [&](char ch) {
			return isWhitespace(ch) || ch == ':' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '/' || ch == '\\' || ch == '\"' || ch == ',';
			};

		while (i < n && !isStop(s[i])) ++i;

		addToken(source.substr(start, i - start), TokenType::String);
	}

	return tokens;
}

bool Tokenizer::isWhitespace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

std::vector<Tokenizer::Segment> Tokenizer::segmentize(const std::vector<Tokenizer::Token>& T) {
    std::unordered_map<Tokenizer::TokenType, Tokenizer::TokenType> PAIRS = {
        { Tokenizer::ParenOpen, Tokenizer::ParenClose },
        { Tokenizer::BrackOpen, Tokenizer::BrackClose },
        { Tokenizer::Quote,     Tokenizer::Quote }
    };

    std::vector<Segment> topLevel;
    std::vector<Frame> stack;

    auto isOpen = [&](auto tt) { return PAIRS.find(tt) != PAIRS.end(); };
    auto expectedClose = [&](auto tt) { return PAIRS.at(tt); };

    for (size_t i = 0; i < T.size(); ++i) {
        auto tt = T[i].type;

        bool inString = (!stack.empty() && stack.back().open == Tokenizer::Quote);

        if (inString) {
            if (tt == Tokenizer::Quote) {
                bool escaped = (i > 0 && T[i - 1].type == Tokenizer::UnSlash);
                if (!escaped) {
                    size_t start = stack.back().startTok;
                    Segment seg{ stack.back().open, stack.back().expectedClose, start, i, /*text=*/"", {} };
                    stack.pop_back();
                    if (stack.empty()) topLevel.push_back(std::move(seg));
                    else stack.back().children.push_back(std::move(seg));
                    continue;
                }
            }
            continue;
        }

        if (isOpen(tt)) {
            stack.push_back(Frame{ tt, expectedClose(tt), i, {} });
            continue;
        }

        if (!stack.empty() && tt == stack.back().expectedClose) {
            size_t start = stack.back().startTok;
            Segment seg{ stack.back().open, stack.back().expectedClose, start, i, /*text=*/"", std::move(stack.back().children) };
            stack.pop_back();
            if (stack.empty()) topLevel.push_back(std::move(seg));
            else stack.back().children.push_back(std::move(seg));
            continue;
        }

    }

    return topLevel;
}
