/*CopyString(char pcSource[], char pcDestination[])
Zadaniem funkcji jest skopiowac lancuch znakowy wlacznie ze znakiem NULL z tablicy source do tablicy destination.
Maksymalny poziom zagniezdzenia = 2.
Uzyc „pelnego” fora tj. z inicjalizacja i inkrementacja licznika.*/

#define NULL '\0'
#define STRING_LENGTH 254

char cSourceStr[] = "";
char cDestinationStr[STRING_LENGTH] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

// Jezeli nie podamy rozmiaru bufora zrodlowego to co zostanie wkopiowane do bufora przeznaczenia? -> wszystko co trzeba, bo wpisanie znaku NULL kasuje wszystko co bylo dalej
void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucStrIndex;
	
	for(ucStrIndex = 0; pcSource[ucStrIndex] != NULL; ucStrIndex++)
	{
		pcDestination[ucStrIndex] = pcSource[ucStrIndex];
	}
	pcDestination[ucStrIndex] = pcSource[ucStrIndex];		//LDRB
	//pcDestination[ucStrIndex] = NULL; //MOV
}

int main()
{
	CopyString(cSourceStr, cDestinationStr);
}
