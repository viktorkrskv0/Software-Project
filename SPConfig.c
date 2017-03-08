#include <stdbool.h>
#include <stdio.h>
#include "SPConfig.h"
#define MAX_LEN 1025 //1024 string including the terminating null character
FILE configFile;

typedef enum sp_config_msg_t{
	SP_CONFIG_MISSING_DIR,
	SP_CONFIG_MISSING_PREFIX,
	SP_CONFIG_MISSING_SUFFIX,
	SP_CONFIG_MISSING_NUM_IMAGES,
	SP_CONFIG_CANNOT_OPEN_FILE,
	SP_CONFIG_ALLOC_FAIL,
	SP_CONFIG_INVALID_INTEGER,
	SP_CONFIG_INVALID_STRING,
	SP_CONFIG_INVALID_ARGUMENT,
	SP_CONFIG_INDEX_OUT_OF_RANGE,
	SP_CONFIG_SUCCESS
} SP_CONFIG_MSG;

typedef struct sp_config_t{
	char* spImagesDirectory;
	char* spImagesPrefix;
	char* spImagesSuffix;
	int spNumOfImages;
	int spPCADimension;
	char* spPCAFilename;
	int spNumOfFeatures;
	bool spExtractionMode;
	int spNumOfSimilarImages;
	enum spKDTreeSplitMethod;
	int spKNN;
	bool spMinimalGUI;
	int spLoggerLevel;
	char* spLoggerFilename;
}SPConfig;

/**
  * - SP_CONFIG_INVALID_ARGUMENT - if filename == NULL
 * - SP_CONFIG_CANNOT_OPEN_FILE - if the configuration file given by filename cannot be open
 * - SP_CONFIG_INVALID_INTEGER - if a line in the config file contains invalid integer
 * - SP_CONFIG_INVALID_STRING - if a line in the config file contains invalid string
 * - SP_CONFIG_MISSING_DIR - if spImagesDirectory is missing
 * - SP_CONFIG_MISSING_PREFIX - if spImagesPrefix is missing
 * - SP_CONFIG_MISSING_SUFFIX - if spImagesSuffix is missing
 * - SP_CONFIG_MISSING_NUM_IMAGES - if spNumOfImages is missing
 * - SP_CONFIG_SUCCESS - in case of success
 */
SPConfig spConfigCreate(const char* filename, SP_CONFIG_MSG* msg){
	assert (!msg);  //launch err
	SPConfig config = (SPConfig)malloc(sizeof(SPConfig));
	if (!config){
		msg = SP_CONFIG_ALLOC_FAIL;
		return NULL;
	}

	configFile = fopen(filename, "r");
	checkConfigFileValid();
	if (msg != SP_CONFIG_SUCCESS)
		destroy(config);//correct??
	AssignvariablesfromConfig();

	config.spImagesDirectory
	config.spImagesPrefix;
	config.spImagesSuffix;
	config.spNumOfImages;
	config.spPCADimension = 20;
	config.spPCAFilename = pca.yml;
	config.spNumOfFeatures = 100;
	config.spExtractionMode = true;
	config.spNumOfSimilarImages = 1;
	config.spKDTreeSplitMethod = MAX_SPREAD;
	config.spKNN = 1;
	config.spMinimalGUI = false;
	config.spLoggerLevel = 3;
	config.spLoggerFilename = stdout;

	fclose(configFile);
	return config;
}

//assuming there is a valid value of ExtractionMode
bool spConfigIsExtractionMode(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg); //err
	msg = SP_CONFIG_SUCCESS;
	if (!config){
		msg = SP_CONFIG_INVALID_ARGUMENT;
		return false;
	}
	return config.spExtractionMode;
}

//assuming there is a valid value of MinimalGui
bool spConfigMinimalGui(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg); //err
	msg = SP_CONFIG_SUCCESS;
	if (!config){
		msg = SP_CONFIG_INVALID_ARGUMENT;
		return false;
	}
	return config.spMinimalGUI;
}

//assuming there is a valid value of NumOfImages
int spConfigGetNumOfImages(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg); //err
	msg = SP_CONFIG_SUCCESS;
	if (!config){
		msg = SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	return config.spNumOfImages;
}

//assuming there is a valid value of NumOfFeatures
int spConfigGetNumOfFeatures(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg); //err
	msg = SP_CONFIG_SUCCESS;
	if (!config){
		msg = SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	return config.spNumOfImages;
}

//assuming there is a valid value of PCADim
int spConfigGetPCADim(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg); //err
	msg = SP_CONFIG_SUCCESS;
	if (!config){
		msg = SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	return config.spPCADimension;
}

//assuming there is a valid value of Directory, Prefix, Suffix, N. Images, index
//assuming that the total length in shorter than MAX_LEN (1025)
//assuming imagePath's can contain MAX_LEN (1025)
//assuming the resulting path will be checked as valid before use
//not assuming imagePath is an empty string
SP_CONFIG_MSG spConfigGetImagePath(char* imagePath, const SPConfig config,
		int index){
	if (!imagePath || !config)
		return SP_CONFIG_INVALID_ARGUMENT;
	if (index >= config.spNumOfImages)
		return SP_CONFIG_INDEX_OUT_OF_RANGE;
	char* Sindex[MAX_LEN];
	sprintf(Sindex, "%d", index);
	strcpy(imagePath, "");// in case it wasn't empty
	strcat(imagePath, config.spImagesDirectory);
	strcat(imagePath, config.spImagesPrefix);
	strcat(imagePath, Sindex);
	strcat(imagePath, config.spImagesSuffix);
	return SP_CONFIG_SUCCESS;
}

//assuming there is a valid value of Directory and File Name
//assuming that the total length in shorter than MAX_LEN (1025)
//assuming pcaPath's can contain MAX_LEN (1025)
//assuming the resulting path will be checked as valid before use
//not assuming imagePath is an empty string
SP_CONFIG_MSG spConfigGetPCAPath(char* pcaPath, const SPConfig config){
	if (!pcaPath || !config)
		return SP_CONFIG_INVALID_ARGUMENT;
	strcpy(pcaPath, "");// in case it wasn't empty
	strcat(pcaPath, config.spImagesDirectory);
	strcat(pcaPath, config.spPCAFilename);
	return SP_CONFIG_SUCCESS;
}

void spConfigDestroy(SPConfig config){
	if (config){
		free(config); //more?
		fclose(configFile); //needed?
	}
}

