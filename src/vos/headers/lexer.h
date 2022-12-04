#ifndef _VOS_LEXER_H
#define _VOS_LEXER_H 1

#include <stdint.h>
#include <stddef.h>

typedef enum {
    TOKEN_NULL = 0,
    TOKEN_STRING,
    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,

    TOKEN_KEYWORD_FUNC,
    TOKEN_KEYWORD_CLASS,
    TOKEN_KEYWORD_ENUM,
    TOKEN_KEYWORD_IMPORT,
    TOKEN_KEYWORD_VAR,
    TOKEN_KEYWORD_PRIVATE,
    TOKEN_KEYWORD_STATIC,
    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_ELSEIF,
    TOKEN_KEYWORD_ELSE,
    TOKEN_KEYWORD_MATCH,
    TOKEN_KEYWORD_FOR,
    TOKEN_KEYWORD_BREAK,
    TOKEN_KEYWORD_CONTINUE,
    TOKEN_KEYWORD_RETURN,
    TOKEN_KEYWORD_TRUE,
    TOKEN_KEYWORD_FALSE,
    TOKEN_KEYWORD_SUPER,

    TOKEN_OPERATOR_PLUS,
    TOKEN_OPERATOR_MINUS,
    TOKEN_OPERATOR_MULTIPLY,
    TOKEN_OPERATOR_DIVIDE,
    TOKEN_OPERATOR_MODULO,
    TOKEN_OPERATOR_UNARY_NOT,
    TOKEN_OPERATOR_UNARY_XOR,
    TOKEN_OPERATOR_UNARY_OR,
    TOKEN_OPERATOR_UNARY_AND,
    TOKEN_OPERATOR_LSHIFT,
    TOKEN_OPERATOR_RSHIFT,
    TOKEN_OPERATOR_BOOL_NOT,
    TOKEN_OPERATOR_BOOL_OR,
    TOKEN_OPERATOR_BOOL_AND,
    TOKEN_OPERATOR_EQUAL,
    TOKEN_OPERATOR_NOTEQUAL,
    TOKEN_OPERATOR_LESS,
    TOKEN_OPERATOR_MORE,
    TOKEN_OPERATOR_LESSEQUAL,
    TOKEN_OPERATOR_MOREEQUAL,
    TOKEN_OPERATOR_ASSIGN,
    TOKEN_OPERATOR_IMPLY_ASSIGN,
    TOKEN_OPERATOR_COLON,
    TOKEN_OPERATOR_COMMA,
    TOKEN_OPERATOR_LPAREN,
    TOKEN_OPERATOR_RPAREN,
    TOKEN_OPERATOR_LBRACKET,
    TOKEN_OPERATOR_RBRACKET,
    TOKEN_OPERATOR_LBRACE,
    TOKEN_OPERATOR_RBRACE,
} TokenType;

typedef struct {
	TokenType type;
	const char* start;
    int length;
} Token;

typedef struct {
    void* delegate;

    const char* filename;
    const char* buffer;
    const char* start;
    const char* pos;
    uint32_t lineno;
    uint32_t colno;
    uint32_t length;
} Lexer;

Lexer lexer_new(void* delegate, const char* filename, const char* buffer);
Token lexer_next(Lexer* lex);

#endif