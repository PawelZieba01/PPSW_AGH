#define NULL '\0'

enum CompResult{DIFFERENT, EQUAL};

void CopyString(char pcSource[], char pcDestination[]);
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
void AppendString(char pcSourceStr[], char pcDestinationStr[]);
void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar);



char acSourceStr[] = "source";
char acDestinationStr[64] = "destination";

int main()
{
	CopyString(acSourceStr, acDestinationStr);
	return 0;
}




//----------------------------------------------------------------------------------------
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
