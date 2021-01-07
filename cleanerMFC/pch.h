// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <iostream>
#include <string>
#include <Windows.h>
#include <Psapi.h>
#include <fileapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <ShObjIdl.h>
#include <ShObjIdl_core.h>
#include <ObjIdl.h>
#include <ShlObj.h>
#include <sysinfoapi.h>
#include <VersionHelpers.h>
#include <WinBase.h>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 
#include <experimental/filesystem>
#pragma warning(disable:4996)

#endif //PCH_H
