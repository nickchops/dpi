/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
#ifndef S3E_EXT_PIXELDENSITY_H
#define S3E_EXT_PIXELDENSITY_H

#include <s3eTypes.h>

/**
 * Pixel Density Extension
 *
 * This extension allows the application to get real pixel density values from the OS.
 * Use this with the middleware module PixelDensity to also get know values for devices
 * by ID and guessed fallbacks. Note that iOS values are provided by PixelDensity and not
 * in this extension.
 *
 * @supported{
 *             @platform{Android,android}
 *             @platform{Windows,windows}
 *
 * TODO: support OSX via CGDisplayScreenSize. Likely to just return 72 x pixel size,
 * Can multiply up if retina isnt supported (should be able to get UI scale value)
 * and if none of that works just do 72*screen width!
 * }
 *
 */
// \cond HIDDEN_DEFINES
S3E_BEGIN_C_DECL
// \endcond

/**
 * Returns S3E_TRUE if the PixelDensity extension is available.
 */
s3eBool s3ePixelDensityAvailable();

int s3ePixelDensityGetPPI();

// \cond HIDDEN_DEFINES
S3E_END_C_DECL
// \endcond

#endif /* !S3E_EXT_PIXELDENSITY_H */
