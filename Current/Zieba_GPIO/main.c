#include <LPC21xx.H>					// Dolaczenie pliku biblioteki odpowiadajacej za obsluge procesora LPC2129

int main()
{
	IO1DIR = IODIR1 | (1<<16);	//Wpisanie '1' na 16 pozycje w rejestrze IO1DIR (input output port1 direction)	-	 (1<<16) to maska bitowa (1 przesuniete w lewo o 16 miejsc)  -  | bitowy OR
	IO1SET = IO1SET | (1<<16);	//jak wyzej dla portu SET
	IO1CLR = IO1CLR | (1<<16);	//jak wyzej dla portu CLEAR
	
	while(1)
	{
		
	}
}
