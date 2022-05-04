#define RECIEVER_SIZE 64
//extern char cOdebranyZnak;

enum eRecieverStatus {EMPTY, READY, OVERFLOW};

struct RecieverBuffer
{ 
	char
	cData[RECIEVER_SIZE];
	unsigned char ucCharCtr; 
	enum eRecieverStatus eStatus;
};

void UART_InitWithInt(unsigned int uiBaudRate);
enum eRecieverStatus eReciever_GetStatus(void);
void Reciever_GetStringCopy(char * DestinationBuffer);

