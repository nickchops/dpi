#include "IwDebug.h"
#include "PixelDensity.h"
#include "s3ePixelDensity.h"
#include "s3eSurface.h"
#include "s3eDevice.h"
#include "s3eConfig.h"
#include <string.h>

namespace PixelDensity
{
	int g_ppiCachedValue = 0;

	int32 ppiGetScreenPPI_iOS()
	{
        // For iOS, we hard code the values as they are not available via API
        // but the OS has a relatively small set of screen types
        // Can prob ditch some of the device ID looks ups in favour of checking
        // Coordspace scaling value (either 1 or 2 for low res vs retina)
        
        int width = s3eSurfaceGetInt(S3E_SURFACE_DEVICE_WIDTH);
        int height = s3eSurfaceGetInt(S3E_SURFACE_DEVICE_HEIGHT);
        const char* deviceId = s3eDeviceGetString(S3E_DEVICE_ID);
        
        const char* IPHONE = "iPhone";
        const char* IPOD = "iPod";
        const char* IPAD1 = "iPad1";
        
        //iPhone 1->3gs & matching iPods
        if (width == 480)
            return 163;
        
        //iPhone/iPod Retina
        else if (width == 640)
            return 326;
        
        else if (height == 768)
        {
            //iPad 1 & 2
            if (strncmp(deviceId, IPAD1, strlen(IPAD1)) == 0
                || strcmp(deviceId, "iPad2,1") == 0
                || strcmp(deviceId, "iPad2,2") == 0
                || strcmp(deviceId, "iPad2,3") == 0
                || strcmp(deviceId, "iPad2,4") == 0)
                return 132;
            
            //1st gen iPad Mini (iPad2,5 onwards)
            else
                return 163;
        }
        
        //retina mini
        else if (strcmp(deviceId, "iPad4,4") || strcmp(deviceId, "iPad4,5"))
            return 326;
        
        //future proof guess! iPhone 6 likely same PPI as 5 but with larger screen
        //estimated screen size is 4.7 inch, maybe another larger version too
        else if (strncmp(deviceId, IPHONE, strlen(IPHONE)) == 0
                        || strncmp(deviceId, IPOD, strlen(IPOD)) == 0)
        {
            if (width < 1280)
                return 326;
            else
                return 456; //= double iphone 5 resolution, on a 5 inch device!
        }
        
        //retina ipad
        else
            return 264;
	}

}

using namespace PixelDensity;

//TODO: may want to make this into a class
// and pull loading values from file/ICF into it

int32 PixelDensity::GetScreenPPI()
{
	if (g_ppiCachedValue)
		return g_ppiCachedValue;
    
    if (s3eConfigGetInt("PixelDensity", "ppi", &g_ppiCachedValue) == S3E_RESULT_SUCCESS)
        return g_ppiCachedValue;
    
    if (s3ePixelDensityAvailable())
        g_ppiCachedValue = s3ePixelDensityGetPPI(); //returns 0 on error
    
    if (!g_ppiCachedValue)
    {
        switch (s3eDeviceGetInt(S3E_DEVICE_OS))
        {
            case S3E_OS_ID_IPHONE:
                g_ppiCachedValue = ppiGetScreenPPI_iOS();
                break;
            case S3E_OS_ID_OSX:
                if (s3eSurfaceGetInt(S3E_SURFACE_DEVICE_HEIGHT) > 1440)
                    g_ppiCachedValue = 220; // Guess retina display
                else
                    g_ppiCachedValue = 109; // Average macbook pro
                break;
            case S3E_OS_ID_WINDOWS:
            case S3E_OS_ID_WS8:
            case S3E_OS_ID_WS81:
                g_ppiCachedValue = 140; // Somewhere in the middle of 1000s of screens
                break;
            default:
                g_ppiCachedValue = 216; //slightly aribitrary value: Average low res 7 inch tablet
                break;
        }
    }
    
	return g_ppiCachedValue;
}
