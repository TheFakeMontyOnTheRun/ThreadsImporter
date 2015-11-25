/*
	File:		QTDataRef.h
	
	Description: Document-specific code for thread-safety test application.

	Author:		QTEngineering, dts

	Copyright: 	� Copyright 2003-2004 Apple Computer, Inc. All rights reserved.
	
	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
				("Apple") in consideration of your agreement to the following terms, and your
				use, installation, modification or redistribution of this Apple software
				constitutes acceptance of these terms.  If you do not agree with these terms,
				please do not use, install, modify or redistribute this Apple software.

				In consideration of your agreement to abide by the following terms, and subject
				to these terms, Apple grants you a personal, non-exclusive license, under Apple�s
				copyrights in this original Apple software (the "Apple Software"), to use,
				reproduce, modify and redistribute the Apple Software, with or without
				modifications, in source and/or binary forms; provided that if you redistribute
				the Apple Software in its entirety and without modifications, you must retain
				this notice and the following text and disclaimers in all such redistributions of
				the Apple Software.  Neither the name, trademarks, service marks or logos of
				Apple Computer, Inc. may be used to endorse or promote products derived from the
				Apple Software without specific prior written permission from Apple.  Except as
				expressly stated in this notice, no other rights or licenses, express or implied,
				are granted by Apple herein, including but not limited to any patent rights that
				may be infringed by your derivative works or by other works in which the Apple
				Software may be incorporated.

				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
				WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
				WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
				PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
				COMBINATION WITH YOUR PRODUCTS.

				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
				CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
				GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
				ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
				OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
				(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
				ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
				
	Change History (most recent first): <1> dts 11/16/03 initial release

*/

#pragma once

#include <Movies.h>

#include <string.h>
#include <stdlib.h>


//////////
//
// header files
//
//////////

#include "ComApplication.h"


//////////
//
// compiler flags
//
//////////

#define USE_ADDEMPTYTRACKTOMOVIE	0			// do we use AddEmptyTrackTOMovie when building a reference movie file?


//////////
//
// constants
//
//////////

#define kGetURL_DLOGID				1001
#define kGetURL_OKButton			1
#define kGetURL_CancelButton		2
#define kGetURL_URLTextItem			3
#define kGetURL_URLLabelItem		4

#define kTextKindsResourceID		1001
#define kOpenURLResIndex			1
#define kCopyFileResIndex			2

#define kURLCopySavePrompt			"Save URL as:"
#define kURLCopySaveFileName		"untitled.mov"

#define kRefMovieSavePrompt			"Save reference movie as:"
#define kRefMovieSaveFileName		"untitled.mov"

#define kRefMediaSavePrompt			"Save media file as:"
#define kRefMediaSaveFileName		"untitled.dat"

#define kWindowTitle				"RAM Movie"

#define kQTDRResourceMovieResType	FOUR_CHAR_CODE('RTMd')
#define kQTDRResourceMovieResID		128

#define kURLSeparator				(char)'/'		// URL path separator

#define kDataBufferSize				1024*10			// the size, in bytes, of our data buffer

// type and creator for the transferred file
#define kTransFileType				FOUR_CHAR_CODE('TEXT')
#define kTransFileCreator			FOUR_CHAR_CODE('CWIE')

#define kQTDR_TimeOut				10

#define kVideoTimeScale 			600							// 600 units per second
#define kVideoFrameDuration 		kVideoTimeScale/10			// each frame is 1/10 second

#define kVideoTrackHeight 			202
#define kVideoTrackWidth 			152

#define	kPixelDepth 				32							// 32 bits per pixel
#define	kNumVideoFrames 			100

#define kPictureID					128
#define kPICTFileHeaderSize			512


//////////
//
// function prototypes
//
//////////

Handle							QTDR_MakeFileDataRef (FSSpecPtr theFile);
Handle							QTDR_MakeResourceDataRef (FSSpecPtr theFile, OSType theResType, SInt16 theResID);
Handle							QTDR_MakeHandleDataRef (Handle theHandle);
Handle							QTDR_MakeURLDataRef (char *theURL);

Movie							QTDR_GetMovieFromFile (FSSpecPtr theFile);
Movie							QTDR_GetMovieFromResource (FSSpecPtr theFile, OSType theResType, SInt16 theResID);
Movie							QTDR_GetMovieFromHandle (Handle theHandle);
Movie							QTDR_GetMovieFromURL (char *theURL);

char *							QTDR_GetURLFromUser (short thePromptStringIndex);
char *							QTDR_GetURLBasename (char *theURL);

OSErr							QTDR_AddFilenamingExtension (Handle theDataRef, StringPtr theFileName);
OSErr							QTDR_AddMacOSFileTypeDataRefExtension (Handle theDataRef, OSType theType);
OSErr							QTDR_AddMIMETypeDataRefExtension (Handle theDataRef, StringPtr theMIMEType);
OSErr							QTDR_AddInitDataDataRefExtension (Handle theDataRef, Ptr theInitDataPtr);

OSErr							QTDR_CopyRemoteFileToLocalFile (char *theURL, FSSpecPtr theFile);
PASCAL_RTN void					QTDR_ReadDataCompletionProc (Ptr theRequest, long theRefCon, OSErr theErr);
PASCAL_RTN void					QTDR_WriteDataCompletionProc (Ptr theRequest, long theRefCon, OSErr theErr);
void							QTDR_CloseDownHandlers (void);
#if TARGET_OS_WIN32
void CALLBACK					QTDR_TimerProc (HWND theWnd, UINT theMessage, UINT theID, DWORD theTime);
#endif

OSErr							QTDR_CreateReferenceCopy (Movie theSrcMovie, FSSpecPtr theDstMovieFile, FSSpecPtr theDstMediaFile);
OSErr							QTDR_PlayMovieFromRAM (Movie theMovie);

OSErr							QTDR_CreateMovieInRAM (void);
OSErr							QTDR_CreateTrackInRAM (Movie theMovie);
static OSErr					QTDR_AddVideoSamplesToMedia (Media theMedia, short theTrackWidth, short theTrackHeight);
static void						QTDR_DrawFrame (short theTrackWidth, short theTrackHeight, long theNumSample, GWorldPtr theGWorld);

Boolean							QTDR_IsMovieSelfContained (Movie theMovie);
