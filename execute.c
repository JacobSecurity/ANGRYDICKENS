#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char *shellcode_gen(const char *file_input, int shellcode_index[30]){
	FILE *open_file = fopen(file_input,"rb");
	fseek(open_file,0,SEEK_END);
	long file_size = ftell(open_file);
	rewind(open_file);
	char *ptr_to_text = malloc(sizeof(char)*file_size);
	fread(ptr_to_text,1,file_size,open_file);
	void *ptr_to_shellcode = malloc(0x500);
	
	for(int x = 0; x<30;x++){
		int sentinal = shellcode_index[x];
		memcpy(ptr_to_shellcode,(ptr_to_text+sentinal),sizeof(char));
	};

	return ptr_to_shellcode;	
};



int main(){
	int shellcode_array[30] = {1,2};
	char *shellcode_location = shellcode_gen("/root/Desktop/ANGRYDICKENS/test.txt",shellcode_array);
	void (*run_shellcode)() = shellcode_location;
	run_shellcode();
	
	return 0;
};
