#include "command_decoder.h"
#include "string.h"

//--------------------------------- DEKODOWANIE KOMUNIKATÓW ----------------------------------

unsigned char ucTokenNr;										// LICZNIK TOKENOW
struct Token asToken[MAX_TOKEN_NR];								// TABLICA Z TOKENAMI

struct Keyword asKeywordList[MAX_KEYWORD_NR] = 
{
	{CALC, "calc"}
};

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
				if(ucTokenNumber == MAX_TOKEN_NR)
				{
					return ucTokenNumber;
				}
				else if(ucCurrrentCharacter == NULL)
				{
					return ucTokenNumber;
				}
				else if(ucCurrrentCharacter == DELIMITER_CHAR)
				{
					eState = DELIMITER;
				}
				else
				{
					eState = TOKEN;
				}
				
				break;
			}
				
			case DELIMITER:
			{
				if(ucTokenNumber == MAX_TOKEN_NR)
				{
					return ucTokenNumber;
				}
				else if(ucCurrrentCharacter == NULL)
				{
					return ucTokenNumber;
				}
				else if(ucCurrrentCharacter != DELIMITER_CHAR)
				{
					eState = TOKEN;
					asToken[ucTokenNumber].uValue.pcString = &pcString[ucCharacterNumber];
					ucTokenNumber++;
				}
				else
				{
					eState = DELIMITER;
				}
				
				break;
			}
			
			default:
				break;
		}
	}
}


enum Result eStringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode)
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
