#define RECIEVER_SIZE 4
#define TERMINATOR '\0'

extern char cOdebranyZnak;

enum eRecieverStatus {EMPTY, READY, OVERFLOW};

struct RecieverBuffer
{ 
	char
	cData[RECIEVER_SIZE];
	unsigned char ucCharCtr; 
	enum eRecieverStatus eStatus;
};

void UART_InitWithInt(unsigned int uiBaudRate);
void Reciever_PutCharacterToBuffer(char cCharacter);
