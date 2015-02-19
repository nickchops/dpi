#include "s3e.h"
#include "IwGx.h"
#include "PixelDensity.h"

#include <sstream>


int main(int argc, char* argv[])
{
	IwGxInit();
	IwGxSetColClear(0x1f, 0x1f, 0xc0, 0x7f);
	
	char ppi[5];
	sprintf(ppi, "%d", PixelDensity::GetScreenPPI());

	while (!(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) &&
		!(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN) &&
		!s3eDeviceCheckQuitRequest()
		)
    {
        s3eDeviceYield(0);

        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

        IwGxPrintString(20,20,ppi);

        IwGxFlush();
        IwGxSwapBuffers();
    }

	IwGxTerminate();
}
