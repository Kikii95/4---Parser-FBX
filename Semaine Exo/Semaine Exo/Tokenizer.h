#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Tokenizer
{
public :
	enum TokenType {
		Invalid,		// Unknown
		String,			// String
		
		Colon,			// :

		ParenOpen,		// (
		ParenClose,		// )

		BrackOpen,		// {
		BrackClose,		// }
		
		Slash,			// /
		UnSlash,		// \
		
		Quote,			// "
		Comma			// ,
	};

	struct Token {
		std::string value;
		TokenType type;
	};

	struct Segment {
		Tokenizer::TokenType kindOpen;   
		Tokenizer::TokenType kindClose;  
		size_t startIndexTok;            
		size_t endIndexTok;               
		std::string text;              
		std::vector<Segment> children;   
	};

	struct Frame {
		Tokenizer::TokenType open;
		Tokenizer::TokenType expectedClose;
		size_t startTok;
		std::vector<Segment> children;
	};


	std::vector<Token> tokenize(std::string source);
	std::vector<Segment>segmentize(const std::vector<Tokenizer::Token>& T);

private :
	static bool isWhitespace(char c);
};

