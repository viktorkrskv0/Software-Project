#include <stdbool.h>
#define debug config.spLoggerLevel = 3
#define info config.spLoggerLevel >= 2
#define warning config.spLoggerLevel >= 1

bool spManageMSG(SP_CONFIG_MSG msg, SPConfig config){

	switch (msg)

	case SP_CONFIG_MISSING_DIR:
		info ?
		break;

	case SP_CONFIG_MISSING_PREFIX:
		break;

	case SP_CONFIG_MISSING_SUFFIX:
		break;

	case SP_CONFIG_MISSING_NUM_IMAGES:
		break;

	case SP_CONFIG_CANNOT_OPEN_FILE:
		break;

	case SP_CONFIG_ALLOC_FAIL:
		break;

	case SP_CONFIG_INVALID_INTEGER:
		break;

	case SP_CONFIG_INVALID_STRING:
		break;

	case SP_CONFIG_INVALID_ARGUMENT:
		break;

	case SP_CONFIG_INDEX_OUT_OF_RANGE:
		break;

	case SP_CONFIG_SUCCESS:
		break;
}
