#include <stdbool.h>
#include "main_aux.h"

void runTests(){
	mainLoggerTest();
	mainConfigTest();
	mainTreeTest();
}

bool manageCMSG(SP_CONFIG_MSG* Cmsg){
	if (Cmsg)
		if(*Cmsg != SP_CONFIG_SUCCESS)
			return false;
	return true;
}

bool manageLMSG(SP_LOGGER_MSG* Smsg){
	if (Smsg) //always true if the code is correct
		if(*Smsg != SP_LOGGER_SUCCESS){
			printf("Logger creation failed");
			return false;
		}
	return true;
}

char* getConfigFileName(int argc, char* argv[]){
	if (argc > 1)
		return argv[1];
	return "spcbir.config";
}

void freeAll(SPConfig config, SPLogger logger){
	spConfigDestroy(config);
	spLoggerDestroy(logger);
}
