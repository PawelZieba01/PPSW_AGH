#define DELIMITER_CHAR ' '
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

enum Result{OK, ERROR};
enum CompResult{DIFFERENT, EQUAL};


typedef enum TokenType {KEYWORD, NUMBER, STRING};
typedef enum KeywordCode {LD, ST, RST};
typedef enum MsgState{TOKEN, DELIMITER};

typedef struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};

typedef union TokenValue
{
	enum KeywordCode eKeyword;
	unsigned int uiNumber;
	char * pcString;
};

typedef struct Token
{
	enum TokenType eType;
	union TokenValue uValue;
};


extern struct Token asToken[MAX_TOKEN_NR];


//---------------------------- LANCUCHY ZNAKOWE - OPERACJE PROSTE ----------------------------
void CopyString(char pcSource[], char pcDestination[]);
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
void AppendString(char pcSourceStr[], char pcDestinationStr[]);
void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar);

//------------------------------- LANCUCHY ZNAKOWE - KONWERSJE -------------------------------
void UIntToString(unsigned int uiValue, char pcStr[]);
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue);
void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]);

//--------------------------------- DEKODOWANIE KOMUNIKATÓW ----------------------------------
void DecodeMsg(char *pcString);
