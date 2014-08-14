Pixel Density (DPI/PPI) library and extension for Marmalade SDK
===============================================================

**Extension:**

Gets the pixel density in PPI (pixels per inch) from the platform if available.

**C++ code:**

If extension not available or returns zero, this sets density from a hard coded list
of device=density values, or by guesswork. Also has utility conversion functions.

Originally created by Gleb Lebedev (https://github.com/gamemaster101gr). Tidied up/renamed
and updated by Nick Smith to include iOS devices up to iPhone 5s/Retina iPad. Removed
use of mdev as that is being phased out/replaced in Marmalade.
