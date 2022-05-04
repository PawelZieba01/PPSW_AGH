#define DELIMITER_CHAR ' '
#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 2

enum TokenType {KEYWORD, NUMBER, STRING};
enum KeywordCode {CAL, GT};
enum MsgState{TOKEN, DELIMITER};

struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};

union TokenValue
{
	enum KeywordCode eKeyword;
	unsigned int uiNumber;
	char * pcString;
};

struct Token
{
	enum TokenType eType;
	union TokenValue uValue;
};

extern unsigned char ucTokenNr;
extern struct Token asToken[MAX_TOKEN_NR];

void DecodeMsg(char *pcString);
