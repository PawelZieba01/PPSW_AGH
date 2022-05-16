#include "MyFunctions.h"
#include <stdio.h>

void TestOf_CopyString(void);
void TestOf_eCompareString(void);
void TestOf_AppendString(void);
void TestOf_ReplaceCharactersInString(void);
void TestOf_UIntToString(void);
void TestOf_eHexStringToUInt(void);
void TestOf_AppendUIntToString(void);
void TestOf_ucFindTokensInString(void);
void TestOf_DecodeTokens(void);
void TestOf_DecodeMsg(void);

//********************************** MAIN ****************************************
int main()
{
    printf("TESTY FUNKCJI DO OPERACJI NA STRINGACH \n\n\n");

    TestOf_CopyString();
    TestOf_eCompareString();
    TestOf_AppendString();
    TestOf_ReplaceCharactersInString();

    printf("TESTY FUNKCJI DO OPERACJI NA STRINGACH - KONWERSJE \n\n\n");

    TestOf_UIntToString();
    TestOf_eHexStringToUInt();
    TestOf_AppendUIntToString();

    printf("TESTY FUNKCJI DO DEKODOWANIA KOMUNIKATOW \n\n\n");

    TestOf_ucFindTokensInString();
    TestOf_eStringToKeyword();
    TestOf_DecodeTokens();
    TestOf_DecodeMsg();


	return 0;
}
//*********************************************************************************

void TestOf_CopyString(void)
{

    char acResultString[MAX_STRING_LENGTH] = "jakas przykladowa zawartosc";

    printf("CopyString\n\n");


    printf ("Test 1 - ");
    //Kopiowanie ciagu znaków dluzszego ni¿ zawartoœæ acResultString
    CopyString("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", acResultString);
    if(EQUAL == eCompareString(acResultString, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz")) printf("OK\n"); else printf("Error\n");


    printf ("Test 2 - ");
    //Kopiowanie ³ancucha znakowego, ktory zawiera tylko znak NULL
    CopyString("", acResultString);
    if(EQUAL == eCompareString(acResultString, "")) printf("OK\n"); else printf("Error\n");


    printf ("Test 3 - ");
    //Kopiowanie ciagu roznych znakow ASCII
    CopyString("COPY_TEST1234567890?!@#$%^&*()", acResultString);
    if(EQUAL == eCompareString(acResultString, "COPY_TEST1234567890?!@#$%^&*()")) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_eCompareString(void)
{

    char acStringToCompare[] = "abcdef";

    printf("eCompareString\n\n");

    printf ("Test 1 - ");
    //Porownanie takich samych ciagow znakow
    if(EQUAL == eCompareString(acStringToCompare, "abcdef")) printf("OK\n"); else printf("Error\n");


    printf ("Test 2 - ");
    //Porownanie roznych ciagow znakow
    if(DIFFERENT == eCompareString(acStringToCompare, "jklmn")) printf("OK\n"); else printf("Error\n");

    printf ("Test 3 - ");
    //Pierwszy string dluzszy
    if(DIFFERENT == eCompareString(acStringToCompare, "abc")) printf("OK\n"); else printf("Error\n");

    printf ("Test 4 - ");
    //Pierwszy string dluzszy
    if(DIFFERENT == eCompareString(acStringToCompare, "jklmnoprst")) printf("OK\n"); else printf("Error\n");

    printf ("Test 5 - ");
    //Pusty string
    if(DIFFERENT == eCompareString(acStringToCompare, "")) printf("OK\n\n"); else printf("Error\n\n");
}


void TestOf_AppendString(void)
{
    printf("AppendString\n\n");

    printf ("Test 1 - ");
    //Dopisanie pustego ciagu znakow
    char acResultString1[MAX_STRING_LENGTH] = "abcdef";
    AppendString("", acResultString1);
    if(EQUAL == eCompareString(acResultString1, "abcdef")) printf("OK\n"); else printf("Error\n");

    printf ("Test 2 - ");
    //Dopisanie kilku znakow do pustego stringa
    char acResultString2[MAX_STRING_LENGTH] = "";
    AppendString("jklmn", acResultString2);
    if(EQUAL == eCompareString(acResultString2, "jklmn")) printf("OK\n"); else printf("Error\n");

    printf ("Test 3 - ");
    //dopisanie kilku znakow do niepustego stringa
    char acResultString3[MAX_STRING_LENGTH] = "abcdef";
    AppendString("jklmn", acResultString3);
    if(EQUAL == eCompareString(acResultString3, "abcdefjklmn")) printf("OK\n\n"); else printf("Error\n\n");
}


void TestOf_ReplaceCharactersInString(void)
{
    char acResultString[MAX_STRING_LENGTH] = "jeden dwa trzy cztery";

    printf("ReplaceCharactersInString\n\n");

    printf ("Test 1 - ");
    //Zastapienie przykladowego znaku innym
    ReplaceCharactersInString(acResultString, 'e', 'O');
    if(EQUAL == eCompareString(acResultString, "jOdOn dwa trzy cztOry")) printf("OK\n"); else printf("Error\n");

    printf ("Test 2 - ");
    //Zastapienie spacji nullem
    ReplaceCharactersInString(acResultString, ' ', NULL);
    if(EQUAL == eCompareString(acResultString, "jOdOn")) printf("OK\n\n\n"); else printf("Error\n\n\n");

}


void TestOf_UIntToString(void)
{
    char acResultString[MAX_STRING_LENGTH] = "";

    printf("UIntToString\n\n");

    printf ("Test 1 - ");
    //Liczba z zerami (hex)
    UIntToString(0xF000, acResultString);
    if(EQUAL == eCompareString(acResultString, "0xF000")) printf("OK\n"); else printf("Error\n");

    printf ("Test 2 - ");
    //Skrajne wartosci tetrad
    UIntToString(0x90AF, acResultString);
    if(EQUAL == eCompareString(acResultString, "0x90AF")) printf("OK\n\n"); else printf("Error\n\n");
}


void TestOf_eHexStringToUInt(void)
{
    unsigned int uiReturnedValue;
    enum Result eReturnedResult;

    printf("eHexStringToUInt\n\n");

    printf ("Test 1 - ");
    //Skrajne wartosci tetrad
    eReturnedResult = eHexStringToUInt("0x90AF", &uiReturnedValue);
    if((OK == eReturnedResult) && (0x90AF == uiReturnedValue)) printf("OK\n"); else printf("Error\n");

    printf ("Test 2 - ");
    //Mniej niz 4 tetrady
    eReturnedResult = eHexStringToUInt("0x90", &uiReturnedValue);
    if((OK == eReturnedResult) && (0x90 == uiReturnedValue)) printf("OK\n"); else printf("Error\n");

    printf ("Test 3 - ");
    //Za krotki ciag znakow (zly format)
    eReturnedResult = eHexStringToUInt("0x", &uiReturnedValue);
    if(ERROR == eReturnedResult) printf("OK\n"); else printf("Error\n");

    printf ("Test 4 - ");
    //za dlugi ciag znakow (zly format)
    eReturnedResult = eHexStringToUInt("0x90800000", &uiReturnedValue);
    if(ERROR == eReturnedResult) printf("OK\n"); else printf("Error\n");

    printf ("Test 5 - ");
    //male litery zamiast duzych (zly format)
    eReturnedResult = eHexStringToUInt("0xabcd", &uiReturnedValue);
    if(ERROR == eReturnedResult) printf("OK\n"); else printf("Error\n");

    printf ("Test 6 - ");
    //poczatek rozny od '0x' (zly format)
    eReturnedResult = eHexStringToUInt("9080", &uiReturnedValue);
    if(ERROR == eReturnedResult) printf("OK\n\n"); else printf("Error\n\n");
}


void TestOf_AppendUIntToString(void)
{
    printf("AppendUIntToString\n\n");

    printf("Test 1 - ");
	//Dopisywanie liczby do niepustego stringa
	char acResultString1[] = "jeden dwa ";
	AppendUIntToString(0x3456, acResultString1);
	if(EQUAL == eCompareString(acResultString1, "jeden dwa 0x3456")) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//Dopisywanie liczby do pustego stringa
	char acResultString2[] = "";
	AppendUIntToString(0x1234, acResultString2);
	if(EQUAL == eCompareString(acResultString2, "0x1234")) printf("OK\n\n\n"); else printf("Error\n\n\n");
}

void TestOf_ucFindTokensInString() {

	unsigned char ucTokenNumber;

	printf("ucFindTokensInString\n\n");

	printf("Test 1 - ");
	//maksymalna liczba tokenow - 3
	ucTokenNumber = ucFindTokensInString("abcd 0x1234 load");
	if (ucTokenNumber == 3) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//same delimitery
	ucTokenNumber = ucFindTokensInString("     ");
	if (ucTokenNumber == 0) printf("OK\n"); else printf("Error\n");

	printf("Test 3 - ");
	//delimitery na poczatku, 2 tokeny
	ucTokenNumber = ucFindTokensInString("   0x1234 abc");
	if (ucTokenNumber == 2) printf("OK\n"); else printf("Error\n");

	printf("Test 4 - ");
	//kilka delimiterow pomiedzy tokenami
	ucTokenNumber = ucFindTokensInString("0x1234   abc       load");
	if (ucTokenNumber == 3) printf("OK\n"); else printf("Error\n");

	printf("Test 5 - ");
	//za duzo tokenow (czy ustawil wskazniki na 3 pierwsze tokeny?)
	char acTestString[]="0x1234 abc def reset";
	ucTokenNumber = ucFindTokensInString(acTestString);
	if ((ucTokenNumber==3) && (&acTestString[0]==asToken[0].uValue.pcString)
			&& (&acTestString[7]==asToken[1].uValue.pcString)
			&& (&acTestString[11]==asToken[2].uValue.pcString)) printf("OK\n\n"); else printf("Error\n\n");
}


void TestOf_eStringToKeyword() {

	enum KeywordCode eTokenCode;

	printf("eStringToKeyword\n\n");

	printf("Test 1 - ");
	//Slowo kluczowe
	if (eStringToKeyword("reset", &eTokenCode) == OK) printf("OK\n"); else printf("Error\n");

	printf("Test 2 - ");
	//Slowo inne niz kluczowe
	if (eStringToKeyword("slowo_niekluczowe", &eTokenCode) == ERROR) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_DecodeTokens() {

	unsigned char ucTokenNumber;
	char pcStringToDecode[] = "0x1234 abcd load";

	printf("DecodeTokens\n\n");

	printf("Test 1 - ");
	//Zdekodowanie liczby, napisu i slowa kluczowego (czy zapis ich wartosci jest poprawny?)
	ucTokenNr = 3;

	asToken[0].uValue.pcString = &pcStringToDecode[0];
	asToken[1].uValue.pcString = &pcStringToDecode[7];
	asToken[2].uValue.pcString = &pcStringToDecode[12];

	pcStringToDecode[6] = NULL;
	pcStringToDecode[11] = NULL;

	DecodeTokens();

	if ((asToken[0].eType == NUMBER) && (asToken[0].uValue.uiNumber==0x1234) &&
			(asToken[1].eType == STRING) && (&pcStringToDecode[7] == asToken[1].uValue.pcString) &&
			(asToken[2].eType == KEYWORD) && (asToken[2].uValue.eKeyword == LD)) printf("OK\n\n"); else printf("Error\n\n");
}


void TestOf_DecodeMsg() {

	char pcStringToDecode[]="0x1234 abcd load";

	printf("DecodeMsg\n\n");

	printf("Test 1 - ");
	//Zdekodowanie komunikatu zawierajacego liczbe, zwykle slowo i slowo kluczowe
	DecodeMsg(pcStringToDecode);
	if ((asToken[0].eType == NUMBER) && (asToken[0].uValue.uiNumber==0x1234) &&
			(asToken[1].eType == STRING) && (&pcStringToDecode[7] == asToken[1].uValue.pcString) &&
			(asToken[2].eType == KEYWORD) && (asToken[2].uValue.eKeyword == LD)) printf("OK\n\n"); else printf("Error\n\n");
}


