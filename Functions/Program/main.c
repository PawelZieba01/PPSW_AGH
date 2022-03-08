#define NULL '\0'

char cSourceStr[] = "tekst_1";
char cDestinationStr[254] = "tekst_2";
unsigned int uiTest = 0;

enum CompResult{DIFFERENT, EQUAL};
enum Result{OK, ERROR};

void CopyString(char pcSource[], char pcDestination[]);
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
void AppendString(char pcSourceStr[], char pcDestinationStr[]);
void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar);
void UIntToString(unsigned int uiValue, char pcStr[]);
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue);
void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]);


int main()
{
	//AppendString(cSourceStr, cDestinationStr);
	//AppendUIntToString(0xa1b2, cDestinationStr);
}



//DZIALA
/*CopyString(char pcSource[], char pcDestination[])
Zadaniem funkcji jest skopiowac lancuch znakowy wlacznie ze znakiem NULL z tablicy source do tablicy destination.
Maksymalny poziom zagniezdzenia = 2.
Uzyc „pelnego” fora tj. z inicjalizacja i inkrementacja licznika.*/
void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucStringIndex;
	
	for(ucStringIndex = 0; pcSource[ucStringIndex] != NULL; ucStringIndex++)
	{
		pcDestination[ucStringIndex] = pcSource[ucStringIndex];
	}
	pcDestination[ucStringIndex] = pcSource[ucStringIndex];		//LDRB
	//pcDestination[ucStrIndex] = NULL; //MOV
}



//DZIALA
/*Zadaniem funkcji jest porównywac lancuchy znakowe zakonczone znakiem NULL.
Jezeli lancuchy sa sobie równe funkcja powinna zwracac „EQUEL” , w przeciwnym przypadku „NOTEQUAL”
Funkcja zwraca wartosc typu „enum CompResult { DIFFERENT , EQUAL }”
W funkcji ni powinno znajdowac sie wiecej niz 3 porównania (chociaz mozna „zejsc” do 2)
Wystarczy jeden for i jeden if.
Wystarczy jedna zmienna lokalna pracujaca jako licznik petli.
Maksymalny poziom zagniezdzenia = 3.*/
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



//DZIALA
/*Zadaniem funkcji jest dodac do lancucha znakowego znajdujacego sie w cDestinationStr lancuch znakowy
znajdujacy sie w cSourceStr.
Pierwszy znak lancucha cSourceStr powinien zostac nadpisany na NULL-u lancucha cDestinationStr .
Nalezy wykorzystac jedna z wczesniejszych funkcji.
Wystarczy jeden for.
Nie uzywac bufora pomocniczego.*/
// Tu trzeba uwazac zeby nie dokleic znakow poza tablice pcDestinationStr!
void AppendString(char pcSourceStr[], char pcDestinationStr[])
{
	unsigned char ucLastCharacter;
	
	for(ucLastCharacter = 0; pcDestinationStr[ucLastCharacter] != NULL; ucLastCharacter++){}
	CopyString(pcSourceStr, &pcDestinationStr[ucLastCharacter]);
}

//DZIALA
/*Zadaniem funkcji jest zamienic w String-u wszystkie znaki OldChar na NewChar.*/
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



//DZIALA
/*Zadaniem funkcji jest skonwertowac liczbe typu „ui” na lancuch tekstowy w formacie heksadecymalnym.
Lancuch tekstowy powinien znalezc sie w tablicy „cStr”.
Lancuch powinien konczyc sie znakiem NULL.
Lancuch musi zaczynac sie od „0x” nastepnie moga pojawiac sie kody ascci z zakresów „0-9”, „A-F”
Przyklady:
uiValue = 0; cStr=”0x0000”+NULL
uiValue = 1; cStr=”0x0001”+NULL
uiValue = 65000; cStr=0xFDE8”+NULL
Przed implementacja nalezy zapoznac sie z tablica kodów ascii oraz z zapisem heksadecymalny.
Nalezy iterowac po tetradach (niblach, tetradach) zmiennej uiValue od najmlodszej do najstarszej.
Uzywac operatorów bitowych w tym przesuniec. Maski bitowe powinny miec odpowiedni format.
Nie stosowac wiecej niz jednej petli w kodzie.
Nie modyfikowac zmiennej wejsciowej uiValue;
Nie stosowac tablic ani cas-ów do przekodowywania liczby na znak.
Wystarcza dwie zmienne lokalne (wliczajac licznik petli).
Unikac powtórzen kodu.*/
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



//DZIALA
/*Zadaniem funkcji jest zamienic lancuch znakowy w formacie hexadecymalnym (duze litery) na wartosc.
Adres lancucha znajduje sie w zmiennej cStr.
Zaklada sie ze jest to lancuch typu NULL terminated string
Wartosc przekazywana jest na zewnatrz funkcji poprzez wskaznik puiValue
Lancuch heksadecymalny akceptowany przez funkcje musi zaczynac sie od „0x” .
Po „0x” musi znajdowac sie przynajmniej jeden znak rózny od NULL.
Po „0x” nie moze znajdowac sie wiecej niz 4 znaki rózne od NULL.
Zgodnosc z formatem powinna sie zakonczyc zwróceniem przez funkcje wartosci OK. a niezgodnosc ERROR.
Funkcja zwraca wartosc typu „enum Result { OK, ERROR }”
Maksymalnie jeden „for”.
W „forze” jedno odwolanie do tablicy „[]”. Nie uzywac wskazników do iterowania po cStr.*/
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



//DZIALA
/*Zadaniem funkcji jest dodac liczbe w formacie heksadecymalnym (patrz ucUIntToHexStr) do lancucha
znakowego znajdujacego sie w cDestinationStr.
Pierwszy znak liczby powinien zostac nadpisany na NULL-u lancucha cDestinationStr.
Nie nalezy tworzyc bufora pomocniczego – nalezy odpowiednio zastosowac wskazniki.*/
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucLastCharacter;
	
	for(ucLastCharacter = 0; pcDestinationStr[ucLastCharacter] != NULL; ucLastCharacter++){}
	UIntToString(uiValue, &pcDestinationStr[ucLastCharacter]);
}

