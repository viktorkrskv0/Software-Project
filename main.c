//#include "sp_image_proc_util.h"
#include "SPConfig.h"
#include "main_aux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_aux.h"
#include <stdbool.h>

SP_CONFIG_MSG* msg;
SPConfig config;

//#define manageMSG if(spManageMSG(msg, config)) return-1


int main(int argc, char** argv){
	// PART A - initiating
	//logger? destroy logger?
	config = spConfigCreate(argv[1], msg); // must be initialized before a printing can be made with the Logger
	msg = spLoggerCreate(config.spLoggerFilename, config.spLoggerLevel); //what to do with the returned msg?
//	manageMSG; //assuming destroy will be done before if needed
	if (config.spExtractionMode)
		spExtract(config, msg); //including verifying DONE and saving to directory
	else //maybe anyway?
		extractFromFiles(config, msg);
	initDataStructures(config, msg);

	// PART B - Query: get query & answer it or exit
//	While (true){
//		comand = receiveComand(msg);
//		manageMSG;
//		comand? continue : return 0;
//		resImages = findSimilarImages(query, msg);
//		manageMSG;
//		showImages(config.spMinimalGUI, resImages, msg);
//		manageMSG;
//	}
}
