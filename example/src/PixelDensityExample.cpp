#include "s3e.h"
#include "IwGx.h"
#include "PixelDensity.h"

#include <sstream>


int main(int argc, char* argv[])
{
	IwGxInit();
	IwGxSetColClear(0x1f, 0x1f, 0xc0, 0x7f);

    for (;;)
    {
        s3eDeviceYield(0);
        s3eKeyboardUpdate();

        bool result = true;
        if	(
            (result == false) ||
            (s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) ||
            (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN) ||
            (s3eDeviceCheckQuitRequest()) 
            )
            break;

        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

        int32 d = PixelDensity::GetScreenPPI();
        std::stringstream stream;
        stream << "DPI = " << d;
        std::string s = stream.str();

        IwGxPrintString(20,20,s.c_str());

        IwGxFlush();
        IwGxSwapBuffers();
    }

	IwGxTerminate();
}
