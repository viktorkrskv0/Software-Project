#include "SPLogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SP_LOGGER_OPEN_MODE "w" //File open mode
#define MAX_LEN 1025 //1024 string including the terminating null character
sp_logger_t* logger = NULL; // Global variable holding the logger


typedef struct sp_logger_t*{
	FILE* outputChannel; //The logger file
	bool isStdOut; //Indicates if the logger is stdout
	SP_LOGGER_LEVEL level; //Indicates the level
}SPLogger;

SP_LOGGER_MSG spLoggerCreate(const char* filename, SP_LOGGER_LEVEL level) {
	if (logger != NULL) { //Already defined
		return SP_LOGGER_DEFINED;
	}
	logger = (SPLogger) malloc(sizeof(*logger));
	if (logger == NULL) { //Allocation failure
		return SP_LOGGER_OUT_OF_MEMORY;
	}
	logger->level = level; //Set the level of the logger
	if (filename == NULL) { //In case the filename is not set use stdout
		logger->outputChannel = stdout;
		logger->isStdOut = true;
	} else { //Otherwise open the file in write mode
		logger->outputChannel = fopen(filename, SP_LOGGER_OPEN_MODE);
		if (logger->outputChannel == NULL) { //Open failed
			free(logger);
			logger = NULL;
			return SP_LOGGER_CANNOT_OPEN_FILE;
		}
		logger->isStdOut = false;
	}
	return SP_LOGGER_SUCCESS;
}


void spLoggerDestroy() {
	if (!logger) {
		return;
	}
	if (!logger->isStdOut) {//Close file only if not stdout
		fclose(logger->outputChannel);
	}
	free(logger);//free allocation
	logger = NULL;
}


/*
 * prints the msg by this format:
 * ---<msg type>---
 *  - file: <file>
 *  - function: <function>
 *  - line: <line>
 *  - message: <msg>
 *
 *   <msg Type> - ERROR, WARNING, INFO, DEBUG
 * 	<file> 	   - is the string given by file, it represents the file in which
 * 		   		 the error print call occurred.
 * 	<function> - is the string given by function, it represents the function in which
 * 			   	 the error print call occurred.
 * 	<line> 	   - is the string given by line, it represents the line in which
 * 		   		 the error print call occurred
 * 	<msg> 	   - is the string given by msg, it contains the msg given by the user
 *
 * 	returns the final fomated msg including /n between the lines and at the end (always needed)
 */
char* formatMSG(const char* msg, const char* file,	const char* function, const int line, char* msgType){
	char* formatedMSG = malloc(MAX_LEN*4 + strlen(msg));
	sprintf(formatedMSG, "---%s%---\n", msgType);
	sprintf(formatedMSG, "- file: %s\n", file);
	sprintf(formatedMSG, "- function: %s\n", function);
	sprintf(formatedMSG, "- line: %s\n", line);
	sprintf(formatedMSG, "- message: %s\n", msg);
	return formatedMSG;
}


/**
 * 	Prints error message. The error message format is given below:
 * 	---ERROR---
 * 	- file: <file>
 *  - function: <function>
 *  - line: <line>
 *  - message: <msg>
 *
 * 	<file> 	   - is the string given by file, it represents the file in which
 * 		   		 the error print call occurred.
 * 	<function> - is the string given by function, it represents the function in which
 * 			   	 the error print call occurred.
 * 	<line> 	   - is the string given by line, it represents the line in which
 * 		   		 the error print call occurred
 * 	<msg> 	   - is the string given by msg, it contains the msg given by the user
 *
 * 	Error messages will be printed at levels:
 *
 * 	SP_LOGGER_ERROR_LEVEL,
 *	SP_LOGGER_WARNING_ERROR_LEVEL,
 *	SP_LOGGER_INFO_WARNING_ERROR_LEVEL,
 *	SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL
 *
 * 	A new line will be printed after the print call.
 *
 * @param msg     	- The message to printed
 * @param file    	- A string representing the filename in which spLoggerPrintError call occurred
 * @param function 	- A string representing the function name in which spLoggerPrintError call ocurred
 * @param line		- A string representing the line in which the function call occurred
 * @return
 * SP_LOGGER_UNDIFINED 			- If the logger is undefined
 * SP_LOGGER_INVAlID_ARGUMENT	- If any of msg or file or function are null or line is negative
 * SP_LOGGER_WRITE_FAIL			- If Write failure occurred
 * SP_LOGGER_SUCCESS			- otherwise
 */
SP_LOGGER_MSG spLoggerPrintError(const char* msg, const char* file,
		const char* function, const int line){
	int success;
	char* formatedMSG;
	if(!logger) // if logger is NULL
		return SP_LOGGER_UNDIFINED;
	// no need to check the logger.SP_LOGGER_LEVEL in this case, but in the next functions it's needed
	if (!msg || !file || !function || line < 0) // if msg / file / func / line invalid
		return SP_LOGGER_INVAlID_ARGUMENT;
	formatedMSG = formatMSG(msg, file, function, line, "ERROR"); // get the msg to be printed
	if (logger.isStdOut == true)
		success = printf("%s/n", formatedMSG);
	else
		success = fprintf(logger.outputChannel, "%s/n", formatedMSG); // print to stdout/file
	if(success < 0)
		return SP_LOGGER_WRITE_FAIL;
	else
		return SP_LOGGER_SUCCESS;
}


/**
 * 	Prints warning message. The warning message format is given below:
 * 	---WARNING---
 * 	- file: <file>
 *  - function: <function>
 *  - line: <line>
 *  - message: <msg>
 *
 * 	<file> 	   - is the string given by file, it represents the file in which
 * 		   		 the warning print call occurred.
 * 	<function> - is the string given by function, it represents the function in which
 * 			   	 the warning print call occurred.
 * 	<line> 	   - is the string given by line, it represents the line in which
 * 		   		 the warning print call occurred
 * 	<msg> 	   - is the string given by msg, it contains the msg given by the user
 *
 * 	Warning messages will be printed at levels:
 *
 *	SP_LOGGER_WARNING_ERROR_LEVEL,
 *	SP_LOGGER_INFO_WARNING_ERROR_LEVEL,
 *	SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL
 *
 *	A new line will be printed after the print call.
 *
 * @param msg     	- The message to printed
 * @param file    	- A string representing the filename in which spLoggerPrintWarning call occurred
 * @param function 	- A string representing the function name in which spLoggerPrintWarning call ocurred
 * @param line		- A string representing the line in which the spLoggerPrintWarning call occurred
 * @return
 * SP_LOGGER_UNDIFINED 			- If the logger is undefined
 * SP_LOGGER_INVAlID_ARGUMENT	- If any of msg or file or function are null or line is negative
 * SP_LOGGER_WRITE_FAIL			- If write failure occurred
 * SP_LOGGER_SUCCESS			- otherwise
 */
SP_LOGGER_MSG spLoggerPrintWarning(const char* msg, const char* file,
		const char* function, const int line){
	int success;
	char* formatedMSG;
	if(!logger) // if logger is NULL
		return SP_LOGGER_UNDIFINED;
	if (logger.SP_LOGGER_LEVEL != SP_LOGGER_ERROR_LEVEL)
		return SP_LOGGER_WRITE_FAIL;
	if (!msg || !file || !function || line < 0) // if msg / file / func / line invalid
		return SP_LOGGER_INVAlID_ARGUMENT;
	formatedMSG = formatMSG(msg, file, function, line, "WARNING"); // get the msg to be printed
	(logger.isStdOut == true) ? success = printf("%s/n", formatedMSG) : success = fprintf(logger.outputChannel, "%s/n", formatedMSG); // print to stdout/file
	(success < 0) ?  return SP_LOGGER_WRITE_FAIL : return SP_LOGGER_SUCCESS;
}


/**
 * 	Prints Info message. The info message format is given below:
 * 	---INFO---
 *  - message: <msg>
 *
 * 	<msg> 	   - is the string given by msg, it contains the msg given by the user
 *
 * 	Info messages will be printed at levels:
 *
 *	SP_LOGGER_INFO_WARNING_ERROR_LEVEL,
 *	SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL
 *
 * 	A new line will be printed after the print call.
 *
 * @param msg     	- The message to printed
 * @return
 * SP_LOGGER_UNDIFINED 			- If the logger is undefined
 * SP_LOGGER_INVAlID_ARGUMENT	- If msg is null
 * SP_LOGGER_WRITE_FAIL			- If Write failure occurred
 * SP_LOGGER_SUCCESS			- otherwise
 */
SP_LOGGER_MSG spLoggerPrintInfo(const char* msg){
	int success;
	char* formatedMSG;
	if(!logger) // if logger is NULL
		return SP_LOGGER_UNDIFINED;
	if (logger.SP_LOGGER_LEVEL == SP_LOGGER_INFO_WARNING_ERROR_LEVEL || logger.SP_LOGGER_LEVEL == SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL)
		return SP_LOGGER_WRITE_FAIL;
	if (!msg || !file || !function || line < 0) // if msg / file / func / line invalid
		return SP_LOGGER_INVAlID_ARGUMENT;
	formatedMSG = formatMSG(msg, file, function, line, "INFO"); // get the msg to be printed
	(logger.isStdOut == true) ? success = printf("%s/n", fomatedMSG) : success = fprintf(logger.outputChannel, "%s/n", fomatedMSG); // print to stdout/file
	(success < 0) ?  return = SP_LOGGER_WRITE_FAIL : return = SP_LOGGER_SUCCESS;
}


/**
 * 	Prints the debug message. The debug message format is given below:
 * 	---DEBUG---
 * 	- file: <file>
 *  - function: <function>
 *  - line: <line>
 *  - message: <msg>
 *
 * 	<file> 	   - is the string given by file, it represents the file in which
 * 		   		 the debug print call occurred.
 * 	<function> - is the string given by function, it represents the function in which
 * 			   	 the debug print call occurred.
 * 	<line> 	   - is the string given by line, it represents the line in which
 * 		   		 the debug print call occurred
 * 	<msg> 	   - is the string given by msg, it contains the msg given by the user
 *
 * 	Debug messages will be printed at level:
 *
 *	SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL
 *
 * 	A new line will be printed after the print call.
 *
 * @param msg     	- The message to printed
 * @param file    	- A string representing the filename in which spLoggerPrintWarning call occurred
 * @param function 	- A string representing the function name in which spLoggerPrintWarning call ocurred
 * @param line		- A string representing the line in which the function call occurred
 * @return
 * SP_LOGGER_UNDIFINED 			- If the logger is undefined
 * SP_LOGGER_INVAlID_ARGUMENT	- If any of msg or file or function are null or line is negative
 * SP_LOGGER_WRITE_FAIL			- If Write failure occurred
 * SP_LOGGER_SUCCESS			- otherwise
 */
SP_LOGGER_MSG spLoggerPrintDebug(const char* msg, const char* file,
		const char* function, const int line){
	int success;
	char* formatedMSG;
	if(!logger) // if logger is NULL
		return SP_LOGGER_UNDIFINED;
	if (logger.SP_LOGGER_LEVEL == SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL)
		return SP_LOGGER_WRITE_FAIL;
	if (!msg || !file || !function || line < 0) // if msg / file / func / line invalid
		return SP_LOGGER_INVAlID_ARGUMENT;
	formatedMSG = formatMSG(msg, file, function, line, "DEBUG"); // get the msg to be printed
	(logger.isStdOut == true) ? success = printf("%s/n", fomatedMSG) : success = fprintf(logger.outputChannel, "%s/n", fomatedMSG); // print to stdout/file
	(success < 0) ?  return = SP_LOGGER_WRITE_FAIL : return = SP_LOGGER_SUCCESS;
}


/**
 * The given message is printed. A new line is printed at the end of msg
 * The message will be printed in all levels.
 *
 * @param msg - The message to be printed
 * @return
 * SP_LOGGER_UNDIFINED 			- If the logger is undefined
 * SP_LOGGER_INVAlID_ARGUMENT	- If msg is null
 * SP_LOGGER_WRITE_FAIL			- If Write failure occurred
 * SP_LOGGER_SUCCESS			- otherwise
 */
SP_LOGGER_MSG spLoggerPrintMsg(const char* msg){
	int success;
	if(!logger) // if logger is NULL
		return SP_LOGGER_UNDIFINED;
	if (!msg) // if msg invalid
		return SP_LOGGER_INVAlID_ARGUMENT;
	success = printf("%s/n", msg);
	(success < 0) ?  return = SP_LOGGER_WRITE_FAIL : return = SP_LOGGER_SUCCESS;
}

#endif
