#include "msgs.h"
static int port;
int serverPort = 50;

void server()
{
    printf("In server \n");
    int serverBuffer[10]={200,201,202,203,204,205,206,207,208,209};
    int receiveBuffer[10];
    receive(serverPort,receiveBuffer);
    int replyPort = receiveBuffer[0];
    printf("In server reveived data from client \n");
    for(int i=0;i<10;i++)
    {
        printf("i is %d data is %d \t",i,receiveBuffer[i]);
    }
    sleep(1);
    send(replyPort,serverBuffer);
}




void client()
{
    printf("In client \n");
    int clientBuffer[10] = {100,1,2,3,4,5,6,7,8,9};
    int receiveBuffer[10];
    int portNo = port++;
    clientBuffer[0] = portNo;
    send(serverPort,clientBuffer);
    sleep(1);
    receive(portNo, receiveBuffer);
    printf("In cleint reveived data from server \n");
    for(int i=0;i<10;i++)
    {
        printf("i is %d data is %d \t",i,receiveBuffer[i]);
    }
    printf("\n");
}


int main()
{
    init_port();
    start_thread(client);
    sleep(1);
    start_thread(server);
    sleep(1);
    
    run();
    while(1){
		sleep(1);
	}

}

