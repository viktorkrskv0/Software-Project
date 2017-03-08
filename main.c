/*
 * Initialize from config
 * Calc features if needed
 * Ask for quary pic
 * Show results (extended/not extended)
 */

#include "sp_image_proc_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_aux.h"
#include <stdbool.h>

//System Variables with default value
char* string spImagesDirectory;
char* spImagesPrefix;
char* spImagesSuffix;
int spNumOfImages;

//System Variables without default value
int spPCADimension = 20;
char* spPCAFilename = pca.yml;
int spNumOfFeatures = 100;
bool spExtractionMode = true;
int spNumOfSimilarImages = 1;
enum spKDTreeSplitMethod = MAX_SPREAD;
int spKNN = 1;
bool spMinimalGUI = false;
int spLoggerLevel = 3;
char* spLoggerFilename = stdout;



int main(int argc, char** argv){
	getConfigFileName(argv[]);




	//inialize from config
	initSysVariables(*spImagesDirectory, *spImagesPrefix, *spImagesSuffix, *spNumOfImages, *spPCADimension, 
			*spPCAFilename, *spNumOfFeatures, *spExtractionMode, *spNumOfSimilarImages, *spKDTreeSplitMethod, 
			*spKNN, *spMinimalGUI, *spLoggerLevel, *spLoggerFilename);
	create new run
	open config file
	read variables from config file and initilize of run.fetures from config

	if (spExtractionMode) calc features
}
