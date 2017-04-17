#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "SPConfig.h"
#define MAX_LEN 1025 //1024 string including the terminating null character
FILE* configFile;

/** A type used for defining the configuration file**/
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
//	enum spKDTreeSplitMethod;
	int spKNN;
	bool spMinimalGUI;
	SP_LOGGER_LEVEL spLoggerLevel;
	char* spLoggerFilename;
}*SPConfig;


/**
 * Creates a new system configuration struct. The configuration struct
 * is initialized based on the configuration file given by 'filename'.
 *
 * @param filename - the name of the configuration file
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return NULL in case an error occurs. Otherwise, a pointer to a struct which
 * 		   contains all system configuration.
 *
 * The resulting value stored in msg is as follow:
 * - SP_CONFIG_INVALID_ARGUMENT - if filename == NULL
 * - SP_CONFIG_CANNOT_OPEN_FILE - if the configuration file given by filename cannot be open
 * - SP_CONFIG_ALLOC_FAIL - if an allocation failure occurred
 * - SP_CONFIG_INVALID_INTEGER - if a line in the config file contains invalid integer
 * - SP_CONFIG_INVALID_STRING - if a line in the config file contains invalid string
 * - SP_CONFIG_MISSING_DIR - if spImagesDirectory is missing
 * - SP_CONFIG_MISSING_PREFIX - if spImagesPrefix is missing
 * - SP_CONFIG_MISSING_SUFFIX - if spImagesSuffix is missing
 * - SP_CONFIG_MISSING_NUM_IMAGES - if spNumOfImages is missing
 * - SP_CONFIG_SUCCESS - in case of success
 *
 *
 */
SPConfig spConfigCreate(const char* filename, SP_CONFIG_MSG* msg){
	assert (!msg);  //launch err

	//malloc
	SPConfig config;
	config = (SPConfig)malloc(sizeof(config));
	if (!config){
		*msg = SP_CONFIG_ALLOC_FAIL;
		return NULL;
	}

	// valid file?
	configFile = fopen(filename, "r");
//	checkConfigFileValid(); // Viktor will complete
	if (*msg != SP_CONFIG_SUCCESS)
		spConfigDestroy(config);//correct??

//  initializing if needed, depends on AssignvariablesfromConfig()
//	config->spImagesDirectory;
//	config->spImagesPrefix;
//	config->spImagesSuffix;
//	config->spNumOfImages;
//	config->spPCADimension = 20;
//	config->spPCAFilename = pca.yml;
//	config->spNumOfFeatures = 100;
//	config->spExtractionMode = true;
//	config->spNumOfSimilarImages = 1;
//	config->spKDTreeSplitMethod = MAX_SPREAD;
//	config->spKNN = 1;
//	config->spMinimalGUI = false;
//	config->spLoggerLevel = 3;
//	config->spLoggerFilename = stdout;

//	AssignvariablesfromConfig(); //Viktor: including msg (ex. info msg "used default value "20" for spPCADimension")

	fclose(configFile);
	return config;
}


/*
 * Returns true if spExtractionMode = true, false otherwise.
 * Assuming there is a valid value of ExtractionMode
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return true if spExtractionMode = true, false otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
bool spConfigIsExtractionMode(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(*msg); //err
	*msg = SP_CONFIG_SUCCESS;
	if (!config){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return false;
	}
	return config->spExtractionMode;
}


/*
 * Returns true if spMinimalGUI = true, false otherwise.
 * Assuming there is a valid value of MinimalGui
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return true if spExtractionMode = true, false otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
bool spConfigMinimalGui(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(*msg); //err
	*msg = SP_CONFIG_SUCCESS;
	if (!config){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return false;
	}
	return config->spMinimalGUI;
}


/*
 * Returns the number of images set in the configuration file, i.e the value
 * of spNumOfImages.
 * Assuming there is a valid value of NumOfImages
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int spConfigGetNumOfImages(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(*msg); //err
	*msg = SP_CONFIG_SUCCESS;
	if (!config){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	return config->spNumOfImages;
}


/*
 * Returns the number of features to be extracted. i.e the value
 * of spNumOfFeatures.
 * Assuming there is a valid value of NumOfFeatures
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int spConfigGetNumOfFeatures(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(*msg); //err
	*msg = SP_CONFIG_SUCCESS;
	if (!config){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	return config->spNumOfImages;
}


/**
 * Returns the dimension of the PCA. i.e the value of spPCADimension.
 * Assuming there is a valid value of PCADim
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int spConfigGetPCADim(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(*msg); //err
	*msg = SP_CONFIG_SUCCESS;
	if (!config){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	return config->spPCADimension;
}


/**
 * Given an index 'index' the function stores in imagePath the full path of the
 * ith image.
 * assuming there is a valid value of Directory, Prefix, Suffix, N. Images, index
 * assuming that the total length in shorter than MAX_LEN (1025)
 * assuming imagePath's can contain MAX_LEN (1025)
 * assuming the resulting path will be checked as valid before use
 * not assuming imagePath is an empty string
 *
 * For example:
 * Given that the value of:
 *  spImagesDirectory = "./images/"
 *  spImagesPrefix = "img"
 *  spImagesSuffix = ".png"
 *  spNumOfImages = 17
 *  index = 10
 *
 * The functions stores "./images/img10.png" to the address given by imagePath.
 * Thus the address given by imagePath must contain enough space to
 * store the resulting string.
 *
 * @param imagePath - an address to store the result in, it must contain enough space.
 * @param config - the configuration structure
 * @param index - the index of the image.
 *
 * @return
 * - SP_CONFIG_INVALID_ARGUMENT - if imagePath == NULL or config == NULL
 * - SP_CONFIG_INDEX_OUT_OF_RANGE - if index >= spNumOfImages
 * - SP_CONFIG_SUCCESS - in case of success
 */
SP_CONFIG_MSG spConfigGetImagePath(char* imagePath, const SPConfig config,
		int index){
	if (!imagePath || !config)
		return SP_CONFIG_INVALID_ARGUMENT;
	if (index >= config->spNumOfImages)
		return SP_CONFIG_INDEX_OUT_OF_RANGE;
	char Sindex[MAX_LEN];
	sprintf(Sindex, "%d", index);
	strcpy(imagePath, "");// in case it wasn't empty
	strcat(imagePath, config->spImagesDirectory);
	strcat(imagePath, config->spImagesPrefix);
	strcat(imagePath, Sindex);
	strcat(imagePath, config->spImagesSuffix);
	return SP_CONFIG_SUCCESS;
}


/**
 * The function stores in pcaPath the full path of the pca file.
 * assuming there is a valid value of Directory and File Name
 * assuming that the total length in shorter than MAX_LEN (1025)
 * assuming pcaPath's can contain MAX_LEN (1025)
 * assuming the resulting path will be checked as valid before use
 * not assuming imagePath is an empty string
 *
 * For example given the values of:
 *  spImagesDirectory = "./images/"
 *  spPcaFilename = "pca.yml"
 *
 * The functions stores "./images/pca.yml" to the address given by pcaPath.
 * Thus the address given by pcaPath must contain enough space to
 * store the resulting string.
 *
 * @param imagePath - an address to store the result in, it must contain enough space.
 * @param config - the configuration structure
 * @return
 *  - SP_CONFIG_INVALID_ARGUMENT - if imagePath == NULL or config == NULL
 *  - SP_CONFIG_SUCCESS - in case of success
 */
SP_CONFIG_MSG spConfigGetPCAPath(char* pcaPath, const SPConfig config){
	if (!pcaPath || !config)
		return SP_CONFIG_INVALID_ARGUMENT;
	strcpy(pcaPath, "");// in case it wasn't empty
	strcat(pcaPath, config->spImagesDirectory);
	strcat(pcaPath, config->spPCAFilename);
	return SP_CONFIG_SUCCESS;
}


/**
 * Frees all memory resources associate with config.
 * If config == NULL nothig is done.
 */
void spConfigDestroy(SPConfig config){
	if (config){
		free(config); //more?
		fclose(configFile); //needed?
	}
}

