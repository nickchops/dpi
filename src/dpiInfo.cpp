#include <IwDebug.h>
#include <dpiInfo.h>
#include <dpiExt.h>

namespace DPI
{
	int initCounter = 0;
	bool g_dpiCached = false;
	int g_dpiCachedValue = 96;

	int32 dpiGetScreenDPI_iOS()
	{
        // For iOS, we hard code the values as they are not available via API
        // but the OS has a relatively small set of screen types
        // Can prob ditch some of the device ID looks ups in favour of checking
        // Coordspace scaling value (either 1 or 2 for low res vs retina)
        
        int width = s3eSurfaceGetInt(S3E_SURFACE_DEVICE_WIDTH);
        int height = s3eSurfaceGetInt(S3E_SURFACE_DEVICE_HEIGHT);
        const char* deviceId = s3eDeviceGetInt(S3E_DEVICE_ID);
        
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
        else if (strcmp(deiceId, "iPad4,4") || strcmp(deviceId, "iPad4,5"))
            return 326;
        
        //future proof guess! iPhone 6 likely same DPI as 5 but with larger screen
        //estimated screen size is 4.7 inch, maybe another larger version too
        //assuming f pixel count gets v high then DPI
        else if strncmp(deviceId, IPHONE, strlen(IPHONE) == 0
                        || strncmp(deviceId, IPOD, strlen(IPOD) == 0)
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

using namespace DPI;

void DPI::dpiInit()
{
	++initCounter;
	if (initCounter != 1)
		return;

	//IW_CLASS_REGISTER(CfthFont);
}

void DPI::dpiTerminate()
{
	--initCounter;
	if (initCounter < 0)
		IwAssertMsg(FREETYPE,false,("dpiTerminate doesn't match dpiInit"));
	if (initCounter != 0)
		return;
}

int32 DPI::dpiGetScreenDPI()
{
	if (g_dpiCached)
		return g_dpiCachedValue;
    
    g_dpiCached = true;
    
    if (dpiExtAvailable())
        g_dpiCachedValue = dpiExtGetDeviceDPI();
    
    if (!g_dpiCachedValue)
    {
        switch (s3eDeviceGetInt(S3E_DEVICE_OS))
        {
        case S3E_OS_ID_IPHONE:
            g_dpiCachedValue = dpiGetScreenDPI_iOS();
            break;
        default:
            g_dpiCachedValue = 216; //slightly aribitrary value: Average low res 7 inch tablet
            break;
        }
    }
    
	return g_dpiCachedValue;
}
