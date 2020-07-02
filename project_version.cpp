#include "project_version.h"
#include "version.h"

int version() {	
	if (!PROJECT_VERSION > 0) {
		PROJECT_VERSION = 1;
	}
	return PROJECT_VERSION;
}