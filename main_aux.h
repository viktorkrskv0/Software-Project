/*
 * main_aux.h
 *
 *  Created on: Mar 30, 2017
 *      Author: gleit
 */

#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_
#include <stdbool.h>
#include "unit_tests\\unit_test_util.h"
#include "SPConfig.h"
#include "SPLogger.h"

void runTests();

char* getConfigFileName(int argc, char** agrv);

bool manageCMSG(SP_CONFIG_MSG* Cmsg);

bool manageLMSG(SP_LOGGER_MSG* Smsg);

void freeAll(SPConfig config, SPLogger logger);

#endif /* MAIN_AUX_H_ */
