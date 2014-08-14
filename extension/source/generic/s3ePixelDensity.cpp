/*
Generic implementation of the s3ePixelDensity extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3ePixelDensity_internal.h"
s3eResult s3ePixelDensityInit()
{
    //Add any generic initialisation code here
    return s3ePixelDensityInit_platform();
}

void s3ePixelDensityTerminate()
{
    //Add any generic termination code here
    s3ePixelDensityTerminate_platform();
}

int s3ePixelDensityGetPPI()
{
	return s3ePixelDensityGetPPI_platform();
}
