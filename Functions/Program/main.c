#define NULL '\0'
#define DELIMITER_CHAR ' '
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

char cSourceStr[] = "tekst token 0x22";
char cDestinationStr[254] = "tekst_2";
unsigned int uiTest = 0;



//---------------------------------------------------------------------------------
enum CompResult{DIFFERENT, EQUAL};

void CopyString(char pcSource[], char pcDestination[]);
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
void AppendString(char pcSourceStr[], char pcDestinationStr[]);
void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar);
//---------------------------------------------------------------------------------
enum Result{OK, ERROR};

void UIntToString(unsigned int uiValue, char pcStr[]);
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue);
void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]);
//---------------------------------------------------------------------------------
unsigned char ucFindTokensInString (char *pcString);
//---------------------------------------------------------------------------------



typedef enum TokenType {KEYWORD, NUMBER, STRING};
typedef enum KeywordCode { LD, ST, RST};

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

typedef struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};

typedef enum MsgState{TOKEN, DELIMITER};


struct Keyword asKeywordList[MAX_KEYWORD_NR] = 
{
	{RST,"reset"},
	{LD, "load" },
	{ST, "store"}
};

struct Token asToken[MAX_TOKEN_NR];         // TABLICA Z TOKENAMI
unsigned char ucTokenNr;										// LICZNIK TOKENOW





//*********************************************************************************
int main()
{
	unsigned char test1 = ucFindTokensInString("tekst token 0x22");
	unsigned char test2 = ucFindTokensInString(" token 0x22");
	unsigned char test3 = ucFindTokensInString("      ");
	unsigned char test4 = ucFindTokensInString("teks   token 0x22");
	
	return 0;
}
//*********************************************************************************


//--------------------------------- DEKODOWANIE KOMUNIKATÓW ----------------------------------
unsigned char ucFindTokensInString(char *pcString)
{
	unsigned char ucCharacterNumber;
	unsigned char ucCurrrentCharacter;
	enum MsgState eState = DELIMITER;
	ucTokenNr = 0;
	
	for(ucCharacterNumber = 0 ;; ucCharacterNumber++)
	{
		ucCurrrentCharacter = pcString[ucCharacterNumber];
		
		switch(eState)
		{
			case TOKEN:
			{
				if(ucCurrrentCharacter == NULL)
				{
					return ucTokenNr;
				}
				else if(ucCurrrentCharacter == DELIMITER_CHAR)
				{
					eState = DELIMITER;
				}
				break;
			}
				
			case DELIMITER:
			{
				if(ucCurrrentCharacter == NULL)
				{
					return ucTokenNr;
				}
				else if(ucCurrrentCharacter != DELIMITER_CHAR)
				{
					eState = TOKEN;
					asToken[ucTokenNr].uValue.pcString = &pcString[ucCharacterNumber];
					ucTokenNr++;
				}
				break;
			}
		}
	}
}



//---------------------------- LANCUCHY ZNAKOWE - OPERACJE PROSTE ----------------------------
void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucStringIndex;
	
	for(ucStringIndex = 0; pcSource[ucStringIndex] != NULL; ucStringIndex++)
	{
		pcDestination[ucStringIndex] = pcSource[ucStringIndex];
	}
	pcDestination[ucStringIndex] = NULL;
}


enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
	unsigned char ucStringIndex;
	
	for(ucStringIndex = 0; pcStr1[ucStringIndex] != NULL; ucStringIndex++)
	{
		if(pcStr1[ucStringIndex] != pcStr2[ucStringIndex])
		{
			return DIFFERENT;
		}
	}
	
	if(NULL == pcStr2[ucStringIndex])
	{
		return EQUAL;
	}
	return DIFFERENT;
}


void AppendString(char pcSourceStr[], char pcDestinationStr[])
{
	unsigned char ucLastCharacter;
	
	for(ucLastCharacter = 0; pcDestinationStr[ucLastCharacter] != NULL; ucLastCharacter++){}
	CopyString(pcSourceStr, &pcDestinationStr[ucLastCharacter]);
}


void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar)
{
	unsigned char ucStringIndex;
	
	for(ucStringIndex = 0; pcString[ucStringIndex] != NULL; ucStringIndex++)
	{
		if(pcString[ucStringIndex] == cOldChar)
		{
			pcString[ucStringIndex] = cNewChar;
		}
	}
}


//---------------------------- LANCUCHY ZNAKOWE - KONWERSJE ----------------------------
void UIntToString(unsigned int uiValue, char pcStr[])
{
	signed char ucTetradeIndex;
	unsigned char ucTetradeValue;
	
	pcStr[0] = '0';
	pcStr[1] = 'x';
	
	for(ucTetradeIndex = 0; ucTetradeIndex < 4; ucTetradeIndex++)
	{
		ucTetradeValue = (uiValue >> (4 * ucTetradeIndex)) & 0x0F;
		if(ucTetradeValue < 10)
		{
			pcStr[5 - ucTetradeIndex] = '0' + ucTetradeValue;
		}
		else
		{
			pcStr[5 - ucTetradeIndex] = 'A' + ucTetradeValue - 10;
		}
	}
	
	pcStr[6] = NULL;
}


enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue)
{
	unsigned char ucStringIndex;
	unsigned char ucTetradeCharacter;
	
	*puiValue = 0;
	
	if((pcStr[0] != '0') || (pcStr[1] != 'x') || (NULL == pcStr[2]))
	{
		return ERROR;
	}
	
	for(ucStringIndex = 2; ucStringIndex < 7; ucStringIndex++)
	{
		ucTetradeCharacter = pcStr[ucStringIndex];
		
		if(NULL == ucTetradeCharacter)
		{
			return OK;
		}
		else if(6 == ucStringIndex)
		{
			return ERROR;
		}
		
		*puiValue = (*puiValue) << 4;
		
		if((ucTetradeCharacter >= 'A') && (ucTetradeCharacter <= 'F'))
		{
			*puiValue = (*puiValue) | (ucTetradeCharacter - 'A' + 10);
		}
		else if((ucTetradeCharacter >= '0') && (ucTetradeCharacter <= '9'))
		{
			*puiValue = (*puiValue) | (ucTetradeCharacter - '0');
		}
		else
		{
			return ERROR;
		}
	}
	return OK;
}


void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucLastCharacter;
	
	for(ucLastCharacter = 0; pcDestinationStr[ucLastCharacter] != NULL; ucLastCharacter++){}
	UIntToString(uiValue, &pcDestinationStr[ucLastCharacter]);
}

