package emerald;
public enum TokenType
{
	// Single character tokens
	LEFT_PAREN, RIGHT_PAREN,
	LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, SEMICOLON, SLASH,
	QUESTION, COLON, SIGIL,
	LEFT_SQUARE, RIGHT_SQUARE,
	
	// One or two character tokens
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,
	PLUS, MINUS,
	STAR, EXPONENT,
	AND, OR, BIT_XOR,
	BIT_AND, BIT_OR,
	
	// Three character tokens
	SIGN, ELIPSIS,
	
	// Literals
	IDENTIFIER, STRING, NUMBER,
	
	// Keywords
	ELSE, ELSEIF, FALSE, FN, FOR, IF, IN, NIL,
	PRINT, RETURN, TRUE, VAR, WHILE,
	MODULE, IMPORT,
	
	INDENT, DEDENT, NEWLINE,
	
	EOF
}
