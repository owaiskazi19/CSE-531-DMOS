//Sai Uttej Thunuguntla - 1217167991
//Owais Kazi - 1215161454

#include "msgs.h"

static int clPort = 0;
static int serverPort= 90;

char *fileName[100];
Semaphore_t *mutex;

void server ()
{
	int receiveBuffer[10];
	char recvFileName[32];
	char fileData[36];
	int replyPort;
	FILE *fp[10];

	while(1){
			receive(serverPort,receiveBuffer);
			 
			if (receiveBuffer[0]==-1){
				replyPort=receiveBuffer[1];
				if (replyPort>2){
					continue;
				}
				memcpy(recvFileName,receiveBuffer+2,32);
				if (strlen(recvFileName) > 15){
					printf("File name exceeds 15 chars \n");
					continue;
				}
				strcat(recvFileName,".server");
				fp[replyPort] = fopen(recvFileName, "w");
			}else{
				replyPort=receiveBuffer[0];
				if(fp[replyPort]){
					int size = ftell(fp[replyPort]);

					if (size>=1048576){
						int fd = fileno(fp[replyPort]); 
						continue;
					}

					if (replyPort>2){
						continue;
					}

					memcpy(fileData,receiveBuffer+1,36);
					fprintf(fp[replyPort], "%s",fileData);
					fseek(fp[replyPort],0,SEEK_CUR);
				}
			}	
		}

	while(1){
		sleep(1);
	}
}


void client ()
{
	FILE *fp;
	char buff[36];
	int c[10];
	int clientNumber;
 
	P(mutex);
		clientNumber=clPort++;
	V(mutex);

	while(1){
		c[0]=-1;
		c[1]=clientNumber;
		memcpy(c+2,fileName[clientNumber],32);
		send(serverPort,c);
		printf("Client %d requesting file transfer \n",clientNumber);
		break;
		yield();
	}	

	fp=fopen(fileName[clientNumber],"r");

	c[0]=clientNumber;
	while(fgets(buff, 36,fp)){
		memcpy(c+1,buff,36);
		send(serverPort,c);
	}

	/* To inform which file transfer is completed. */
	if (clientNumber < 3){
		printf("Client %d transfer done.\n", clientNumber);
	}

	fclose(fp);
	

	while(1){
		yield();	
	}

}

int main(int argc, char * argv[]){

	init_port();
	mutex = CreateSem(1);
	
	start_thread(server);
	printf("Number of clients requested for file transfer are: %s\n", argv[1]);	
	
	if (argc<3 && atoi(argv[1])>0){
		printf("Arguments not matching \n");
		exit(1);
	}
	
	int clients = atoi(argv[1]);
	int i;
	for(i=0; i<clients; i++){
		fileName[i] = (char *) malloc(strlen(argv[2+i])*sizeof(char));
		memcpy(fileName[i],argv[2+i],strlen(argv[2+i])*sizeof(char));
		start_thread(client);	
	}
	   
   	run();

	while(1){
		sleep(1);
	}
}