#define NULL '\0'
#define DELIMITER_CHAR ' '
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

enum Result{OK, ERROR};
enum CompResult{DIFFERENT, EQUAL};

typedef enum TokenType {KEYWORD, NUMBER, STRING};
typedef enum KeywordCode {LD, ST, RST};

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
unsigned char ucFindTokensInString (char *pcString);
enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);







//------------ zmienne pomocnicze --------------
char cSourceStr[] = "store load reset";
char cDestinationStr[254] = "tekst_2";
unsigned int uiTest = 0;






struct Keyword asKeywordList[MAX_KEYWORD_NR] = 
{
	{RST,"reset"},
	{LD, "load" },
	{ST, "store"}
};

struct Token asToken[MAX_TOKEN_NR];         // TABLICA Z TOKENAMI
unsigned char ucTokenNr;										// LICZNIK TOKENOW

//********************************** MAIN ****************************************
int main()
{
	DecodeMsg(cSourceStr);

	return 0;
}
//*********************************************************************************










//---------------------------- LANCUCHY ZNAKOWE - OPERACJE PROSTE ----------------------------
void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucCharacterCounter;
	
	for(ucCharacterCounter = 0; pcSource[ucCharacterCounter] != NULL; ucCharacterCounter++)
	{
		pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter];
	}
	pcDestination[ucCharacterCounter] = NULL;
}


enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
	unsigned char ucCharacterCounter;
	
	for(ucCharacterCounter = 0; pcStr1[ucCharacterCounter] != NULL; ucCharacterCounter++)
	{
		if(pcStr1[ucCharacterCounter] != pcStr2[ucCharacterCounter])
		{
			return DIFFERENT;
		}
	}
	
	if(NULL == pcStr2[ucCharacterCounter])
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
	unsigned char ucCharacterCounter;
	
	for(ucCharacterCounter = 0; pcString[ucCharacterCounter] != NULL; ucCharacterCounter++)
	{
		if(pcString[ucCharacterCounter] == cOldChar)
		{
			pcString[ucCharacterCounter] = cNewChar;
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



//--------------------------------- DEKODOWANIE KOMUNIKATÓW ----------------------------------
unsigned char ucFindTokensInString(char *pcString)
{
	unsigned char ucCharacterNumber;
	unsigned char ucCurrrentCharacter;
	enum MsgState eState = DELIMITER;
	unsigned char ucTokenNumber = 0;
	
	for(ucCharacterNumber = 0 ;; ucCharacterNumber++)
	{
		ucCurrrentCharacter = pcString[ucCharacterNumber];
		
		switch(eState)
		{
			case TOKEN:
			{
				if(ucCurrrentCharacter == NULL)
				{
					return ucTokenNumber;
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
					return ucTokenNumber;
				}
				else if(ucCurrrentCharacter != DELIMITER_CHAR)
				{
					eState = TOKEN;
					asToken[ucTokenNumber].uValue.pcString = &pcString[ucCharacterNumber];
					ucTokenNumber++;
				}
				break;
			}
		}
	}
}


enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode)
{
	unsigned char ucKeywordCounter;
	
	for(ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++)
	{
		if(EQUAL == eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString))
		{
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}


void DecodeTokens(void)
{
	unsigned char ucTokenCounter;
	struct Token * psCurrentToken;
	unsigned int uiTokenValue;
	enum KeywordCode eTokenCode;
	
	for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++)
	{
		psCurrentToken = &asToken[ucTokenCounter];
		
		if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode))
		{
			psCurrentToken->eType = KEYWORD;
			psCurrentToken->uValue.eKeyword = eTokenCode;
		}
		else if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue))
		{
			psCurrentToken->eType = NUMBER;
			psCurrentToken->uValue.uiNumber = uiTokenValue;
		}
		else
		{
			psCurrentToken->eType = STRING;
		}
	}
}


void DecodeMsg(char *pcString)
{
	ucTokenNr = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, DELIMITER_CHAR, NULL);
	DecodeTokens();
}

