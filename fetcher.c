#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


char *fetch(char *host,int remote_port){
	//Create socket
	int socket_descriptor = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_connection;
	server_connection.sin_family = AF_INET;
	server_connection.sin_port = htons(remote_port); 
	server_connection.sin_addr.s_addr = inet_addr(host);

	int connect_status = connect(socket_descriptor,(struct sockaddr *)&server_connection,sizeof(server_connection));

	if(connect_status != 0 ){
		printf("Error connecting");

	};

	char *header = malloc(0x500);
	sprintf(header,"GET /book.txt HTTP/1.1\r\n\r\n");
	
	void *response = malloc(0x1643210);
	
	send(socket_descriptor,header,strlen(header),MSG_CONFIRM);
	recv(socket_descriptor,response,0x1643210,MSG_WAITALL);
	
	char *truncated_buffer = response+182; 
	printf("%s\n",truncated_buffer);
	
	close(socket_descriptor);
	return truncated_buffer;

};
