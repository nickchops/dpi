Pixel Density (PPI/DPI) library and extension for Marmalade SDK
===============================================================

**Extension:**

Gets the pixel density in PPI (pixels per inch) from the platform if available.
Currently supported on Android and Windows desktop only. Android tested, Windows not
tested yet.

**C++ code:**

If extension not available or returns zero, this sets density from a hard coded set
of device->density values, or by guesswork. Also has some utility conversion functions
which are disabled as out of date and not tested.

Originally created by Gleb Lebedev (https://github.com/gamemaster101gr). Tidied up/renamed
and updated by Nick Smith to include iOS devices up to iPhone 5s/Retina iPad. Removed
use of mdev as that is being phased out/replaced in Marmalade. I've generally renamed
and refactored most of the code to remove dependencies, typos, etc.

To use in C++
-------------

###Use the C++ subproject, not the extension directly

In MKB add:

    subproject PixelDensity

In game code just call this to get pixels per inch:

    int ppi = PixelDensity::GetScreenPPI();


###To rebuild the extension part

You can rebuild Android libs with the Android.jar that ships with Marmalade 7 or newer.
You need Android NDK - latest version recommended. To build, run
extension/s3ePixelDensity_Android.mkb and extension/s3ePixelDensity_Android_java.mkb

The C++ is included as source only - no libs to build.


To use in Marmalade Quick/Lua
-----------------------------

Quick uses the same C++ code from the PixelDensity project. To use PixelDensity in Quick
you need to (a) update some of the Quick installation's include files, (b) run a utility
called tolua++ to generate C++->Lua bindings and (c) re-build quick_prebuilt to generate a
new version of Quicks C++ binary that includes PixelDensity.

If lazy, you can skip (b) and (c) and just use the prebuilt version ive put in the /quick
folder (see below)

All paths below are within the Marmalade sdk folder (or .app on Mac)
This assumes you've put this project's main folder in the SDK's *modules* folder.

###To include and build into Quick

1. To allow tolua++ to generate wrappers, add the following to quick/quickuser_tolua.pkg:

        $cfile "../modules/dpi/h/PixelDensity.h"

2. Run quick/quickuser_tolua(.bat) to generate lua->C++ bindings
3. To allow the extension to be built into Quick's binaries, add the following to quickuser.mkf:

        #http://github.com/nickchops/dpi
        subproject dpi/PixelDensity

4. Build quick/quick_prebuilt.mkb for all architectures you care about. This builds the
   the bindings above and C++ parts of PixelDensity into the Quick binaries (which live in
quick/target). In 7.4.1 and newer, run the relevant build_XXX scripts. In older versions:

        ARM: quick_prebuilt.mkb --buildenv=scons --compiler=gcc --arm --output-name=target/arm/quick_prebuilt --output-name-debug=target/arm/quick_prebuilt_d
        WIN: quick_prebuilt.mkb --buildenv=VC10X --x86 --output-name=target/win/quick_prebuilt --output-name-debug=target/win/quick_prebuilt_d
        MAC: quick_prebuilt.mkb --compiler=clang --buildenv=scons --x86 --output-name=../quick/target/osx/quick_prebuilt --output-name-debug=../quick/target/osx/quick_prebuilt_d
        etc.

5. Make the C++/Java libs get included in Android deployments of your Quick app by adding
   the following to quick/quick_prebuilt.mkf:

        subproject "$MARMALADE_ROOT/modules/dpi/PixelDensity"

6. If using in an existing project, clean the project via Hub > Project screen > More >
   Clean Project Build Directories (or delete project's build_temp folder). This is needed
   for the new extension to get picked up.

If running marmalade 7.3 or older, steps 1 & 4 may need additional work. See
notes in https://github.com/nickchops/s3eAndroidFullscreen/blob/master/README.md

###For the Lazy

I've supplied builds of the Mac x86 and cross-platform ARM Quick
binaries in quick/target.zip You can just replace the existing files in quick/target with
these then perform steps 5 & 6 above. Note that my binaries may not include other Quick
user extensions you might already be using! Other builds to follow!

###To use the Quick APIs

Function names are identical to the C++ ones, with the namespace now becoming a table:

        local ppi = PixelDensity.GetScreenPPI()


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

