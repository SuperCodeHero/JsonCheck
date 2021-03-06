#ifndef __DEFINE_H__
#define __DEFINE_H__

#define QUOTATION   '\"'
#define LBRACE      '{'
#define RBRACE      '}'
#define LBRACKET    '['
#define RBRACKET    ']'
#define COMMA       ','
#define COLON       ':'

enum
{
    NOT_START = 1,
    AFTER_MATCHED,
    AFTER_LBRACE,
    AFTER_LBRACKET,
    AFTER_QUOTATION,
    BEFORE_VALUE_COLON,
    JSON_VALUE,
    AFTER_JSON_VALUE,
    AFTER_RBRACE,
    AFTER_RBRACKET,
    AFTER_BRACE_MATCHED,
    AFTER_BRACKET_MATCHED,
    AFTER_QUOTATION_MATCHED,
    AFTER_COMMA,
    AFTER_COLON,
    END
};

#endif