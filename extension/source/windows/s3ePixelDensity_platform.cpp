/*
 * windows-specific implementation of the s3ePixelDensity extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3ePixelDensity_internal.h"
#include <Windows.h>

#include "IwDebug.h"

s3eResult s3ePixelDensityInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3ePixelDensityTerminate_platform()
{
    // Add any platform-specific termination code here
}

int s3ePixelDensityGetPPI_platform()
{
	HDC hScreenDC = GetDC( NULL );
    int pixelsWide = GetDeviceCaps( hScreenDC, HORZRES );
    int millimetersWide = GetDeviceCaps( hScreenDC, HORZSIZE );

	IwTrace(PIXELDENSITY, ("HORZRES (pixels wide, may be scaled) %d", pixelsWide));
	IwTrace(PIXELDENSITY, ("HORZSIZE (millimeters wide, not scaled) %d", millimetersWide));

	int ppi = 254 * pixelsWide / millimetersWide / 10;
	IwTrace(PIXELDENSITY, ("Pixels Per Inch (may be scaled) = pixels / millimeters * 25.4 = %d", ppi));

	IwTrace(PIXELDENSITY, ("LOGPIXELSX (pixels per 'logical inch' - Windows seems to scale this, so ignoring) %d", GetDeviceCaps(hScreenDC, LOGPIXELSX)));

    ReleaseDC( NULL, hScreenDC );

	return ppi;
}
