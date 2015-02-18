Pixel Density (PPI/DPI) library and extension for Marmalade SDK
===============================================================

**Extension:**

Gets the pixel density in PPI (pixels per inch) from the platform if available.
Currently supported on Android and Windows desktop only. Android tested, Windows not
tested yet.

**C++ code:**

If extension not available or returns zero, this then sets density from a hard-
coded set of device->density values, or by guesswork. Also has some utility
conversion functions (currently disabled as out of date and not tested...)

Originally created by Gleb Lebedev (https://github.com/gamemaster101gr).
Tidied up/renamed and updated by Nick Smith to include iOS devices up to iPhone
5s/Retina iPad. Removed use of mdev to simplify setup. I've generally renamed
and refactored most of the code to remove dependencies, typos, etc. Also
added Quick support!


Requirements and setup for C++ and Quick
----------------------------------------

### Add the module and extensions to your Marmalade search path

You can either add the project to default paths or keep it in your github
project folder and add that to your Marmalade search paths. The later is
recommended so that you don't have to do this every time you install a new
Marmalade version and can get Github updates easier.

To add your github root to global search, put the following in
marmalade-root/s3e/s3e-default.mkf:

        options { module_path="path/to/my/github/projects/root" }

Alternatively, copy the dpi folder to marmalade-root/modules.


Additional setup for Quick only
-------------------------------

### Prerequisites for Quick only

- Marmalade SDK 7.4 or newer is needed for Quick extension improvements.

- You need scripts for rebuilding Quick binaries. Get these from
  https://github.com/nickchops/MarmaladeQuickRebuildScripts Copy those to the
  root *quick* folder in the SDK.


### You must rebuild binaries to embed the extension in Quick

For Quick, you need to make changes to two quick config files and then
rebuild the Quick binaries. Paths here refer to < marmalade-root >/quick.

1. Edit quick/quickuser_tolua.pkg and add this new line:

        $cfile "path/to/projects/dpi/h/PixelDensity.h"

2. Edit quick/quickuser.mkf and add the following to the 'subprojects' block:

        subprojects
        {
            dpi/PixelDensity
        }
        
   Make sure the parent folder of dpi is in global paths
        
3. Run quick/quickuser_tolua.bat to generate Lua bindings.

4. Rebuild the Quick binaries by running the scripts (build_quick_prebuilt.bat
   etc.)


Add the module to your C++ or Quick app/game project
----------------------------------------------------

You must add the following to your app project's MKB file:

        subprojects
        {
            dpi/PixelDensity
        }

Note that you should use the C++ subproject and not the extensions directly!


To use in C++
-------------

In game code just call this to get pixels per inch:

    int ppi = PixelDensity::GetScreenPPI();


###To rebuild the extension part

You can rebuild Android libs with the Android.jar that ships with Marmalade 7 or
newer. You need Android NDK - latest version recommended. To build, run
extension/s3ePixelDensity_Android.mkb and
extension/s3ePixelDensity_Android_java.mkb

The C++ is included as source only - no libs to build!


To use in Marmalade Quick/Lua
-----------------------------

Note that Quick uses the exact same C++ code from the PixelDensity project, the
wrapper just converts C++ namespace and types to quick table and types.

        local ppi = PixelDensity.GetScreenPPI()

If using https://github.com/nickchops/MarmaladeQuickVirtualResolution you need to
divide by the scale to position something by real world units. e.g.

        local moveBy = 3 * ppi/vr.scale --3 inches on the screen in user space

------------------------------------------------------------------------------------------
All code is provided under the MIT license unless stated otherwise:

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

