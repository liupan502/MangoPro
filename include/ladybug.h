//=============================================================================
// Copyright ?2004 Point Grey Research, Inc. All Rights Reserved.
// 
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with Point Grey Research, Inc. (PGR).
// 
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
#ifndef __LADYBUG_H__
#define __LADYBUG_H__

/** 
 * @defgroup Ladybug_h ladybug.h
 *
 *  ladybug.h
 *
 *   This file defines the interface to the Ladybug Library.  Linking to 
 *   ladybug.lib will load ladybug.dll at run-time.
 *
 *  We welcome your bug reports, suggestions, and comments: 
 *  http://www.ptgrey.com/support/contact
 *
 */

/*@{*/


#ifdef LADYBUGDLL_EXPORTS
#define LADYBUGDLL_API __declspec( dllexport )
#else
#define LADYBUGDLL_API __declspec( dllimport )
#endif


#ifdef __cplusplus
extern "C"
{
#endif

/**
 *  The "instance" of the Ladybug library.  To access most camera-specific 
 *  methods, a LadybugContext must be created using ladybugCreateContext().
 *  Once created, the context is passed to the particular function.
 *
 */
typedef void* LadybugContext;


/**
 *   The format of the Ladybug serial number.
 */
typedef unsigned long LadybugSerialNumber;


/**
 *   The number of image sensors on the Ladybug.
 */
#define	 LADYBUG_NUM_CAMERAS  6


/** 
 * @defgroup Enumerations Enumerations 
 */

/*@{*/ 

/**
 *   An enumeration of all possible errors returned by the Ladybug API.
 */
typedef enum LadybugError
{
   /**
    * Function completed successfully.
    */
   LADYBUG_OK,

   /**
    * General failure.
    */
   LADYBUG_FAILED,

   /**
    * Invalid argument passed to the function.
    */
   LADYBUG_INVALID_ARGUMENT,

   /**
    * Invalid context passed to the function.
    */
   LADYBUG_INVALID_CONTEXT,

   /**
    * The functionality is not implemented with this version of the library.
    */
   LADYBUG_NOT_IMPLEMENTED,

   /**
    * The functionality is not supported with the current software or hardware
    * configurations.
    */
   LADYBUG_NOT_SUPPORTED,

   /**
    * The device or context has already been initialized.
    */
   LADYBUG_ALREADY_INITIALIZED,

   /**
    * Grabbing has already been started.
    */
   LADYBUG_ALREADY_STARTED,

   /**
    * Failed to open file.
    */
   LADYBUG_COULD_NOT_OPEN_FILE,

   /**
    * Memory allocation error.
    */
   LADYBUG_MEMORY_ALLOC_ERROR,

   /**
    *  There is not enough space on the disk.
    */
   LADYBUG_ERROR_DISK_NOT_ENOUGH_SPACE,

   /**
    *  Stream file has not opened.
    */
   LADYBUG_STREAM_FILE_NOT_OPENED,

   /**
    *  Invalid stream file name.
    */
   LADYBUG_INVALID_STREAM_FILE_NAME,

   /**
    * Device or object not initialized.
    */
   LADYBUG_NOT_INITIALIZED,

   /**
    * Camera has not been started.
    */
   LADYBUG_NOT_STARTED,

   /**
    * Request would exceed maximum bandwidth of the 1394a or 1394b bus.
    */
   LADYBUG_MAX_BANDWIDTH_EXCEEDED,      

   /**
    * Invalid video mode or frame rate passed or retrieved.
    */
   LADYBUG_INVALID_VIDEO_SETTING,

   /**
    * The rectify resolution has not been properly set.
    */
   LADYBUG_NEED_RECTIFY_RESOLUTION,

   /**
    * Function is deprecated - please see documentation.
    */
   LADYBUG_DEPRECATED,

   /**
    * The image buffer returned by the camera was too small to contain all of
    * the JPEG image data.
    */
   LADYBUG_IMAGE_TOO_SMALL,

   /**
    * Operation timed out.
    */
   LADYBUG_TIMEOUT,

   /**
    * Too many image buffers are locked by the user.
    */
   LADYBUG_TOO_MANY_LOCKED_BUFFERS,

   /**
    * No calibration file was found on the Ladybug head unit.
    */
   LADYBUG_CALIBRATION_FILE_NOT_FOUND,

   /**
    * An error occurred during JPEG decompression.
    */
   LADYBUG_JPEG_ERROR,

   /**
    * An error occurred in JPEG header verification.
    */
   LADYBUG_JPEG_HEADER_ERROR,

   /**
    * The compressor did not have enough time to finish compressing the data.
    */
   LADYBUG_JPEG_INCOMPLETE_COMPRESSION,

   /**
    * There is no image in this frame.
    */
   LADYBUG_JPEG_NO_IMAGE,

   /**
    * The compressor detected a corrupted image.
    */
   LADYBUG_CORRUPTED_IMAGE_DATA,

   /**
    * An error occurred in off-screen buffer initialization.
    */
   LADYBUG_OFFSCREEN_BUFFER_INIT_ERROR,

   /**
    * Unsupported framebuffer format.
    */
   LADYBUG_FRAMEBUFFER_UNSUPPORTED_FORMAT,

   /**
    * Framebuffer incomplete.
    */
   LADYBUG_FRAMEBUFFER_INCOMPLETE,

   /**
    * GPS device could not be started.
    */
   LADYBUG_GPS_COULD_NOT_BE_STARTED,

   /**
    * GPS has not been started.
    */
   LADYBUG_GPS_NOT_STARTED,

   /**
    * No GPS data.
    */
   LADYBUG_GPS_NO_DATA,

   /**
    * No GPS data for this sentence.
    */
   LADYBUG_GPS_NO_DATA_FOR_THIS_SENTENCE,

   /**
    * GPS communication port may be in use.
    */
   LADYBUG_GPS_COMM_PORT_IN_USE,

   /**
    * GPS communication port does not exist.
    */
   LADYBUG_GPS_COMM_PORT_DOES_NOT_EXIST,

   /**
    * OpenGL display list has not initialized.
    */
   LADYBUG_OPENGL_DISPLAYLIST_NOT_INITIALIZED,

   /**
    * OpenGL image texture has not updated.
    */
   LADYBUG_OPENGL_TEXTUREIMAGE_NOT_UPDATED,

   /**
    * OpenGL device context is invalid.
    */
   LADYBUG_INVALID_OPENGL_DEVICE_CONTEXT,

   /**
    * OpenGL rendering context is invalid.
    */
   LADYBUG_INVALID_OPENGL_RENDERING_CONTEXT,

   /**
    * OpenGL texture is invalid.
    */
   LADYBUG_INVALID_OPENGL_TEXTURE,

   /**
    * The requested OpenGL operation is not valid.
    */
   LADYBUG_INVALID_OPENGL_OPERATION,

   /**
    * There are not enough resources available for image texture.
    */
   LADYBUG_NOT_ENOUGH_RESOURCE_FOR_OPENGL_TEXTURE,

   /**
    * The current rendering context failed to share 
    * the display-list space of another rendering context
    */
   LADYBUG_SHARING_DISPLAYLIST_FAILED,

   /**
    * The specified off-screen image is invalid.
    */
   LADYBUG_INVALID_OFFSCREEN_BUFFER_SIZE,

   /**
    * The requested job is still on-going.
    */
   LADYBUG_STILL_WORKING,

   /**
    * The PGR stream is corrupted and cannot be corrected.
    */
   LADYBUG_CORRUPTED_PGR_STREAM,

   /**
    * There is no device supporting CUDA, or driver and runtime version may be mismatched.
    */
   LADYBUG_GPU_CUDA_DRIVER_ERROR,

   /**
    * An error occurred in GPU functions.
    */
   LADYBUG_GPU_ERROR,

   /**
    * Low level failure
    */
   LADYBUG_LOW_LEVEL_FAILURE,

   /**
    * Register failure
    */
   LADYBUG_REGISTER_FAILED,

   /**
    * Isoch-related failure
    */
   LADYBUG_ISOCH_FAILED,

   /**
    * Buffer retrieval failure
    */
   LADYBUG_RETRIEVE_BUFFER_FAILED,

   /**
    * Image library failure
    */
   LADYBUG_IMAGE_LIBRARY_FAILED,

   /**
    * Busmaster-related failure
    */
   LADYBUG_BUS_MASTER_FAILED,


   /**
    * Unknown error.
    */
   LADYBUG_ERROR_UNKNOWN,


   /**
    * Number of errors
    */
   LADYBUG_NUM_LADYBUG_ERRORS,


   /**
    * Unused member to force this enumeration to compile to 32 bits.
    */
   LADYBUG_ERROR_FORCE_QUADLET = 0x7FFFFFFF,
      
} LadybugError;


/**
 *   An enumeration used to describe the maximum 1394 bus speed.
 */
typedef enum LadybugBusSpeed
{
   /** Speed 100M */
   LADYBUG_S100,

   /** Speed 200M */
   LADYBUG_S200,

   /** Speed 400M */
   LADYBUG_S400,

   /** Speed 800M */
   LADYBUG_S800,

   /** Speed 1.6G */
   LADYBUG_S1600,

   /** Speed 3.2G */
   LADYBUG_S3200,

   /** Fastest speed */
   LADYBUG_S_FASTEST,

   /** Unknown speed */
   LADYBUG_SPEED_UNKNOWN = -1,

   /** Unused member to force this enumeration to compile to 32 bits. */
   LADYBUG_SPEED_FORCE_QUADLET = 0x7FFFFFFF,

} LadybugBusSpeed;


/**
 *
 * 
 *   An enumeration of the different camera properties for the Ladybug.  
 *
 * Remarks:
 *   Many of these properties are included only for completeness and future
 *   expandability, and will have no effect on a Ladybug camera.
 *
 */
typedef enum LadybugProperty
{
   /** The brightness property. */
   LADYBUG_BRIGHTNESS,

   /** The auto exposure property. */
   LADYBUG_AUTO_EXPOSURE,

   /** The sharpness property. Not supported */
   LADYBUG_SHARPNESS,

   /** The white balance property. */
   LADYBUG_WHITE_BALANCE,

   /** The hue property. Not supported */
   LADYBUG_HUE,

   /** The saturation property. Not supported */
   LADYBUG_SATURATION,

   /** The gamma property. */
   LADYBUG_GAMMA,

   /** The iris property. Not supported */
   LADYBUG_IRIS,

   /** The focus property. Not supported */
   LADYBUG_FOCUS,

   /** The zoom property. Not supported */
   LADYBUG_ZOOM,

   /** The pan property. Not supported */
   LADYBUG_PAN,

   /** The tilt property. Not supported */
   LADYBUG_TILT,

   /** The shutter property. */
   LADYBUG_SHUTTER,

   /** The gain property. */
   LADYBUG_GAIN,

   /** The camera heads frame rate */
   LADYBUG_FRAME_RATE,

   /** Unused member to force this enumeration to compile to 32 bits. */
   LADYBUG_PROPERTY_FORCE_QUADLET = 0x7FFFFFFF,

} LadybugProperty;


/**
 *   The independent properties provide control over each of the
 *   individual camera units.
 */
typedef enum LadybugIndependentProperty
{
   /** Per-camera gain settings. */
   LADYBUG_SUB_GAIN,

   /** Per-camera shutter settings. */
   LADYBUG_SUB_SHUTTER,

   /** Per-camera auto exposure settings as well as "cameras of interest". */
   LADYBUG_SUB_AUTO_EXPOSURE,


   /** Unused member to force this enumeration to compile to 32 bits. */
   LADYBUG_SUB_FORCE_QUADLET = 0x7FFFFFFF,

} LadybugIndependentProperty;


/**
 *   Bit positions for API functions requiring a camera selection bit field, 
 *   such as ladybugSetIndProperty().
 */
typedef enum LadybugCameraBits
{
   /** Camera Unit 0 */
   LADYBUG_UNIT_0    = ( 0x1 << 0 ),

   /** Camera Unit 1 */
   LADYBUG_UNIT_1    = ( 0x1 << 1 ),

   /** Camera Unit 2 */
   LADYBUG_UNIT_2    = ( 0x1 << 2 ),

   /** Camera Unit 3 */
   LADYBUG_UNIT_3    = ( 0x1 << 3 ),

   /** Camera Unit 4 */
   LADYBUG_UNIT_4    = ( 0x1 << 4 ),

   /** Camera Unit 5 */
   LADYBUG_UNIT_5    = ( 0x1 << 5 ),

   /** All camera units  */
   LADYBUG_ALL_UNITS = 0xFF

} LadybugCameraBits;

/**
 *   This enumeration describes the possible data formats returned by the 
 *   Ladybug library. 
 */
typedef enum LadybugDataFormat
{
   /**
    * This format produces a single image buffer that has each sensor's image 
    * one after the other. Again, each pixel is in its raw 8bpp format.
    */
   LADYBUG_DATAFORMAT_RAW8 = 1,

   /**
    * This format is similar to LADYBUG_DATAFORMAT_RAW8 except that the entire
    * buffer is JPEG compressed.  This format is intended for use with cameras
    * that have black and white sensors.
    */
   LADYBUG_DATAFORMAT_JPEG8,

   /**
    * This format separates each individual image into its 4 individual Bayer
    *channels (Green, Red, Blue and Green - not necessarily in that order).
    */
   LADYBUG_DATAFORMAT_COLOR_SEP_RAW8,

   /**
    * This format is very similar to LADYBUG_DATAFORMAT_COLOR_SEP_RAW8
    * except that the transmitted buffer is JPEG compressed.
    */
   LADYBUG_DATAFORMAT_COLOR_SEP_JPEG8,

   /**
    * This format is similar to LADYBUG_DATAFORMAT_RAW8. 
    * The height of the image is only half of that in LADYBUG_DATAFORMAT_RAW8 format. 
    * This format is only supported by Ladybug3.
    */
   LADYBUG_DATAFORMAT_HALF_HEIGHT_RAW8,

   /**
    * This format is similar to LADYBUG_DATAFORMAT_COLOR_SEP_JPEG8.
    * The height of the image is only half of the original image. 
    * This format is only supported by Ladybug3.
    */
   LADYBUG_DATAFORMAT_COLOR_SEP_HALF_HEIGHT_JPEG8,

   /**
    * This format produces a single image buffer that has each sensor's image 
    * one after the other. Each pixel is in raw 16bpp format.  
    * This format is only supported by Ladybug3.
    */
   LADYBUG_DATAFORMAT_RAW16,

   /**
    * This format is very similar to LADYBUG_DATAFORMAT_COLOR_SEP_JPEG8 except
    * that the image data is 12bit JPEG compressed.
    * This format is only supported by Ladybug3.
    */
   LADYBUG_DATAFORMAT_COLOR_SEP_JPEG12,

   /**
    * This format is very similar to LADYBUG_DATAFORMAT_HALF_HEIGHT_RAW8. 
    * Each pixel is in raw 16bpp format.
    */
   LADYBUG_DATAFORMAT_HALF_HEIGHT_RAW16,

   /**
    * This format is similar to LADYBUG_DATAFORMAT_COLOR_SEP_HALF_HEIGHT_JPEG8
    * except that the image data is 12bit JPEG compressed.
    */
   LADYBUG_DATAFORMAT_COLOR_SEP_HALF_HEIGHT_JPEG12,

   /**
    * The number of possible data formats.
    */
   LADYBUG_NUM_DATAFORMATS,

   /**
    * Hook for "any usable video mode".
    */
   LADYBUG_DATAFORMAT_ANY,
   
   /**
    * Unused member to force this enumeration to compile to 32 bits.
    */
   LADYBUG_DATAFORMAT_FORCE_QUADLET = 0x7FFFFFFF,

   /**
    * Deprecated data formats - these will disappear from the header file
    * from the SDK version 1.7.
    */
   LADYBUG_DATAFORMAT_INTERLEAVED = 0,
   LADYBUG_DATAFORMAT_SEQUENTIAL = LADYBUG_DATAFORMAT_RAW8,
   LADYBUG_DATAFORMAT_SEQUENTIAL_JPEG = LADYBUG_DATAFORMAT_JPEG8,
   LADYBUG_DATAFORMAT_COLOR_SEP_SEQUENTIAL = LADYBUG_DATAFORMAT_COLOR_SEP_RAW8,
   LADYBUG_DATAFORMAT_COLOR_SEP_SEQUENTIAL_JPEG = LADYBUG_DATAFORMAT_COLOR_SEP_JPEG8,
   LADYBUG_DATAFORMAT_SEQUENTIAL_HALF_HEIGHT = LADYBUG_DATAFORMAT_HALF_HEIGHT_RAW8,
   LADYBUG_DATAFORMAT_COLOR_SEP_SEQUENTIAL_HALF_HEIGHT_JPEG = LADYBUG_DATAFORMAT_COLOR_SEP_HALF_HEIGHT_JPEG8,

} LadybugDataFormat;


/**
 *   This enumeration describes the raw per-sensor resolutions returned by
 *   the camera.
 *
 * Remarks:
 *   This enumeration is not used to represent the resolution of the actual image.
 *   The only resolution supported by the Ladybug and Ladybug2 is 1024 x 768.
 *   Ladybug3 only supports 1616x1232.
 *   Or, LADYBUG_RESOLUTION_ANY can be used to work both with Ladybug2 and Ladybug3.
 *
 */
typedef enum LadybugResolution
{
   /** 128x96 pixels. Not supported. */
   LADYBUG_RESOLUTION_128x96,

   /** 256x192 pixels. Not supported. */
   LADYBUG_RESOLUTION_256x192,

   /** 512x384 pixels. Not supported. */
   LADYBUG_RESOLUTION_512x384,

   /** 640x480 pixels. Not supported. */
   LADYBUG_RESOLUTION_640x480,

   /** 1024x768 pixels. Ladybug2 camera. */
   LADYBUG_RESOLUTION_1024x768,

   /** 1216x1216 pixels. Not supported. */
   LADYBUG_RESOLUTION_1216x1216,

   /** 1616x1216 pixels. Not supported. */
   LADYBUG_RESOLUTION_1616x1216,

   /** 1600x1200 pixels, Not supported. */
   LADYBUG_RESOLUTION_1600x1200,

   /** 1616x1232 pixels. Ladybug3 camera.  */
   LADYBUG_RESOLUTION_1616x1232,

   /** Number of possible resolutions. */
   LADYBUG_NUM_RESOLUTIONS,

   /** Hook for "any usable resolution". */
   LADYBUG_RESOLUTION_ANY,
   

   /** Unused member to force this enumeration to compile to 32 bits. */
   LADYBUG_RESOLUTION_FORCE_QUADLET = 0x7FFFFFFF,

} LadybugResolution;


/**
 *   The available color processing/destippling/de-mosaicing methods.
 */
typedef enum LadybugColorProcessingMethod
{
   /**
    * Disable color processing - This is useful for retrieving the
    * original bayer patten image. When the image is the color-separated
    * JPEG stream, the JPEG data is decompressed and the 4 color-separated 
    * channels are combined into one bayer image.
    */
   LADYBUG_DISABLE,

   /**
    * Edge sensing de-mosaicing - This is the most accurate method
    *  that can keep up with the camera's frame rate.
    */
   LADYBUG_EDGE_SENSING,

   /**
    * Nearest neighbor de-mosaicing - This algorithm is significantly
    * faster than edge sensing, at the cost of accuracy.
    * This method is derecated and will be removed from SDK version 1.7.
    */
   LADYBUG_NEAREST_NEIGHBOR,

   /**
    * Nearest neighbour de-mosaicing (fast) - Faster, less accurate than
    * nearest neighbor de-mosaicing.
    */
   LADYBUG_NEAREST_NEIGHBOR_FAST,

   /**
    *  Rigorous de-mosaicing - This provides the second best quality colour
    *  reproduction.  This method is very processor intensive and may
    *  not keep up with the camera's frame rate.  Best used for
    *  offline processing where accurate colour reproduction is required. 
    */
   LADYBUG_RIGOROUS,

   /**
    * Quarter image downsampling - Only used for compressed images. Instead
    * of color processing, 4 bayer pixels are combined to form one colour
    * pixel.  Thus, the result image has half width and half height of the 
    * original image. This allows for fast previews.
    */
   LADYBUG_DOWNSAMPLE4,

   /**
    * Mono - This processing method only uses the green color channel to
    * generate grey scale Ladybug images. It is designed for fast previews of
    * compressed JPEG image streams. This method also downsamples the image
    * as in LADYBUG_DOWNSAMPLE4 so the result image is quarter size.
    */
   LADYBUG_MONO,

   /**
    * High quality linear interpolation - This algorithm provides similar
    * results to Rigorous, but is up to 30 times faster.
    */
   LADYBUG_HQLINEAR,

   /**
    * High quality linear interpolation - This algorithm is the same with
    * LADYBUG_HQLINEAR, but the color processing is performed on GPU.
    */
   LADYBUG_HQLINEAR_GPU,

   /**
    * A de-mosaicking algorithm based on the directional filter - This should
    * give the best image quality. 
    */
   LADYBUG_DIRECTIONAL_FILTER,

   /**
    * Unused member to force this enumeration to compile to 32 bits.
    */
   LADYBUG_COLOR_FORCE_QUADLET = 0x7FFFFFFF,

} LadybugColorProcessingMethod;


/**
 * 
 *   The format of stippled pixels (Bayer pattern.)  
 *
 * Remarks:
 *   This format is read from the camera and set automatically.  It is
 *   rarely necessary to set this.
 *
 *   The four characters correspond to the top left 2x2 grid of pixels.
 *   For example, a "BGGR" image has row 0 = BGBGBGBGBG... and
 *   row 1 = GRGRGRGR...
 */
typedef enum LadybugStippledFormat
{
   /** Indicates a BGGR image. */
   LADYBUG_BGGR,

   /** Indicates a GBRG image. */
   LADYBUG_GBRG,

   /** Indicates a GRBG image. */
   LADYBUG_GRBG,

   /** Indicates an RGGB image. */
   LADYBUG_RGGB,

   /** Indicates the default stipple format for the camera. */
   LADYBUG_DEFAULT,

   /** Unused member to force this enumeration to compile to 32 bits. */
   LADYBUG_STIPPLED_FORCE_QUADLET = 0x7FFFFFFF,

} LadybugStippledFormat;


/**
 *   An enumeration used to indicate the pixel format of an image.
 *   This is used for ladybugRenderOffscreenImage() and LadybugProcessedImage struct.
 */
typedef enum LadybugPixelFormat
{
   /* 8 bit of mono */
   LADYBUG_MONO8     = 0x00000001,

   /** 16 bit mono */
   LADYBUG_MONO16    = 0x00000020,

   /** 8 bit raw data */
   LADYBUG_RAW8      = 0x00000200,

   /** 16 bit raw data */
   LADYBUG_RAW16     = 0x00000400,

   /** 24 bit BGR */
   LADYBUG_BGR       = 0x10000001,

   /** 32 bit BGRU */
   LADYBUG_BGRU      = 0x10000002,

   /** 48 bit BGR (16 bit int per channel) */
   LADYBUG_BGR16     = 0x10000004,

   /** 64 bit BGRU (16 bit int per channel) */
   LADYBUG_BGRU16    = 0x10000008,

   /** 48 bit BGR (16 bit float per channel) */
   LADYBUG_BGR16F    = 0x10000010,

   /** 96 bit BGR (32 bit float per channel) */
   LADYBUG_BGR32F    = 0x10000020,


   /** Unused member to force this enum to compile to 32 bits. */
   LADYBUG_PIXELFORMAT_FORCE_QUADLET   = 0x7FFFFFFF,
           
   /** Unspecified pixel format. */
   LADYBUG_UNSPECIFIED_PIXEL_FORMAT = 0

} LadybugPixelFormat;


/**
 *   File format for saved images.    
 *
 * Remarks:
 *   Not all of these file formats are compatible with all functions that take 
 *   a LadybugSaveFileFormat argument.
 */
typedef enum LadybugSaveFileFormat
{

   /** 8-bit greyscale .PGM */
   LADYBUG_FILEFORMAT_PGM,

   /** 24 bit .PPM */
   LADYBUG_FILEFORMAT_PPM,

   /** 24 bit .BMP */
   LADYBUG_FILEFORMAT_BMP,

   /** JPEG image */
   LADYBUG_FILEFORMAT_JPG,

   /** PNG image */
   LADYBUG_FILEFORMAT_PNG,

   /** TIFF image */
   LADYBUG_FILEFORMAT_TIFF,

   /**
    * EXIF image 
    * GPS information is stored in EXIF tags if it is present in LadybugProcessedImage.
    */
   LADYBUG_FILEFORMAT_EXIF,

   /** HDR (Radiance) format */
   LADYBUG_FILEFORMAT_HDR,

   /** Unused member to force this enumeration to compile to 32 bits. */
   LADYBUG_FILEFORMAT_FORCE_QUADLET = 0x7FFFFFFF,

} LadybugSaveFileFormat;


/**
 *   A value indicating an infinite wait when used as a parameter for 
 *   ladybugSetGrabTimeout().
 *
 */
#define LADYBUG_INFINITE   0xFFFFFFFF


/**
 *   The type of device the driver is talking to.
 */
typedef enum LadybugDeviceType
{
   /** Ladybug base unit (Original Ladybug Unit). */
   LADYBUG_DEVICE_LADYBUG,

   /** Ladybug JPEG compressor (Ladybug2). */
   LADYBUG_DEVICE_COMPRESSOR,

   /** Ladybug3 camera */
   LADYBUG_DEVICE_LADYBUG3,

   /** This is an error case. */
   LADYBUG_DEVICE_UNKNOWN,

   /** Unused member to force this enumeration to compile to 32 bits. */
   LADYBUG_DEVICE_FORCE_QUADLET = 0x7FFFFFFF,

} LadybugDeviceType;

/*@}*/ 

/** 
 * @defgroup Structures Structures
 */

/*@{*/ 

/**
 *  This structure defines the format by which time is represented in the
 *  Ladybug SDK. 
 *
 *  The ulSeconds and ulMicroSeconds values represent the
 *  absolute system time when the image was captured.
 *
 *  The ulCycleSeconds and ulCycleCount are higher-precision values that
 *  have either been propagated up from the 1394 bus or extracted from 
 *  the image itself. The data will be extracted from the image if image
 *  timestamping is enabled and directly (and less accurately) from the 
 *  1394 bus otherwise.
 *
 *  The ulCycleSeconds value will wrap around after 128 seconds. The
 *  ulCycleCount represents the 1/8000 second component.
 *
 */
typedef struct LadybugTimestamp
{

   /**
    * The number of seconds since the epoch.
    */
   unsigned long ulSeconds;

   /**
    * The microseconds component.
    */
   unsigned long ulMicroSeconds;

   /**
    * The cycle time seconds.  0-127. 
    */
   unsigned long ulCycleSeconds;

   /**
    * The cycle time count.  0-7999 (1/8000th of a second.)
    */
   unsigned long ulCycleCount;

   /**
    * The cycle offset.  0-3071 (1/3072th of a cycle count.)
    */
   unsigned long ulCycleOffset;
   
} LadybugTimestamp;

/**
 *   All valid LadybugImage structures should have this number in their
 *   LadybugImageInfo fingerprint field.
 */
#define LADYBUGIMAGEINFO_STRUCT_FINGERPRINT 0xCAFEBABE


/**
 *   Current supported version of the LadybugImageInfo structure. 

 * Remarks: 
 *   Cameras not returning images with this version should have their firmware 
 *   upgraded.
 *
 */
#define LADYBUGIMAGEINFO_STRUCT_VERSION 0x00000002


/**
 *   Structure containing the image information of the captured images.
 *  
 * Remarks:
 *   There are 3 main uses for this structure:
 *
 *   (a) It is stored to the hard drive as part of each image set at capture 
 *       time.
 *
 *   (b) It is used in LadybugImage to store image information when each 
 *       image is captured. 
 *
 *   (c) It is used in LadybugImage to store image information when each 
 *       image is read from a .pgr stream file.
 *
 *   This image info structure will only contain valid information if 
 *   the camera is set in either JPEG (for Ladybug2/Ladybug3) or INTERLEAVED
 *   (for Ladybug1) mode.
 *
 */
typedef struct LadybugImageInfo
{
   /**
    * Constant fingerprint, should be LADYBUGIMAGEINFO_STRUCT_FINGERPRINT.
    */
   unsigned long ulFingerprint;

   /**
    * Structure version number, should be 0x00000002.
    */
   unsigned long ulVersion;

   /**
    * Timestamp, in seconds, since the UNIX time epoch. 
    * If it is 0, all the data in LadybugImageInfo are invalid.
    */
   unsigned long ulTimeSeconds;

   /**
    * Microsecond fraction of above second.
    */
   unsigned long ulTimeMicroSeconds;

   /**
    * Sequence number of the image.  Reset to zero when the head powers up 
    *  and incremented for every image.
    */
   unsigned long ulSequenceId;

   /**
    * Horizontal refresh rate. (reserved)
    */
   unsigned long ulHRate;

   /**
    * Actual adjusted gains used by each of the 6 cameras.  Similar to the 
    *  IEEE 1394 gain register.
    */
   unsigned long arulGainAdjust[ 6 ];

   /**
    * A copy of the IEEE 1394 whitebalance register.
    */
   unsigned long ulWhiteBalance;

   /**
    * This is the same as register 0x1044, described in the Point Grey Digital Camera 
    *  Register Reference.
    */
   unsigned long ulBayerGain;

   /**
    * This is the same as register 0x1040, described in the Point Grey Digital Camera 
    *  Register Reference.
    */
   unsigned long ulBayerMap;

   /**
    * A copy of the Brightness IEEE 1394 register.
    */
   unsigned long ulBrightness;

   /**
    * A copy of the Gamma IEEE 1394 register.
    */
   unsigned long ulGamma;

   /**
    * The serial number of the Ladybug head.
    */
   unsigned long ulSerialNum;

   /**
    * Shutter values for each sensor.  Similar to the IEEE 1394 shutter register.
    */
   unsigned long ulShutter[ 6 ];

   /**
    * GPS Latitude, < 0 = South of Equator, > 0 = North of Equator. 
    * If dGPSLatitude = LADYBUG_INVALID_GPS_DATA(defined in ladybugstream.h), 
    * the data is invalid
    */
   double        dGPSLatitude;

   /**
    * GPS Longitude, < 0 = West of Prime Meridian, > 0 = East of Prime Meridian. 
    * If dGPSLongitude = LADYBUG_INVALID_GPS_DATA(defined in ladybugstream.h), 
    * the data is invalid
    */
   double        dGPSLongitude;

   /**
    * GPS Antenna Altitude above/below mean-sea-level (geoid) (in meters).
    * If dGPSAltitude = LADYBUG_INVALID_GPS_DATA(defined in ladybugstream.h),
    * the data is invalid
    */
   double        dGPSAltitude;

} LadybugImageInfo;


/**
 *   The LadybugImage structure is used to describe the image captured from the camera.
 */
typedef struct LadybugImage
{
   /**
    * Columns, in pixels, of a single sensor image. 
    */
   unsigned int      uiCols;
 
   /**
    * Rows, in pixels, of a single sensor image. 
    */
   unsigned int      uiRows;

   /**
    *The data format of the associated image buffer contained in pData. 
    */
   LadybugDataFormat dataFormat;

   /**
    * The raw per-sensor resolution of the returned image.
    * This doesn't indicate the image's resolution.
    */
   LadybugResolution resolution;

   /**
    * Timestamp of this image.
    */
   LadybugTimestamp  timeStamp;
  
   /**
    * Image information for this image. 
    */
   LadybugImageInfo  imageInfo;
    
   /**
    * Pointer to the image data.  The format is defined by dataFormat. 
    */
   unsigned char*    pData;
    
   /**
    * Indicates whether the raw image data is stippled or not. 
    */
   bool              bStippled;
    
   /**
    * Real data size, in bytes, of the data pointed to by pData.  Useful for
    * non-constant sizes (JPEG images).
    */
   unsigned int      uiDataSizeBytes;

   /**
    * The sequence number of the image.  This number is generated in the 
    * driver, and sequential images should have a difference of one.  If
    * the difference is greater than one, it indicates the number of missed
    * images since the last lock image call. If the image is read from a stream
    * file, the value of uiSeqNum is invalid. 
    * Since from SDK 1.6, this number is no more valid and is always 0.
    */
   unsigned int      uiSeqNum;

   /**
    * The internal buffer index that the image buffer corresponds to.  
    * For functions that lock the image, this number must be passed back to 
    * the "unlock" function.  If ladybugInitializePlus() was called, this 
    * number corresponds to the position of the buffer in the buffer array 
    * passed in. If the image is read from a stream file, the value of 
    * uiBufferIndex is invalid.
     */
   unsigned int      uiBufferIndex;

   /**
    * Reserved for future image information
    */
   unsigned long ulReserved[ 3 ];
   
} LadybugImage;


/**
 *   Structure containing metadata for a Ladybug image.
 */
typedef struct _LadybugImageMetaData
{ 
   /** Hour, in Coordinated Universal Time */
   unsigned char    ucGPSHour;
   /** Minute, in Coordinated Universal Time */
   unsigned char    ucGPSMinute;
   /** Second, in Coordinated Universal Time  */
   unsigned char    ucGPSSecond;
   /** Hundredth of a second */
   unsigned short   wGPSSubSecond;
   /** Day  */
   unsigned char    ucGPSDay;
   /** Month  */	
   unsigned char    ucGPSMonth;	
   /** Year  */
   unsigned short   wGPSYear;
   /** Latitude, <0 south of Equator, >0 north of Equator  */
   double           dGPSLatitude;
   /** Longitude, <0 west of Prime Meridian, >0 east of Prime Meridian  */
   double           dGPSLongitude;
   /** Antenna altitude.  */
   double           dGPSAltitude;
   /** Ground speed, in kilometers per hour  */
   double           dGPSGroundSpeed;

   /** Reserved. */
   unsigned long ulReserved[ 50 ];

} LadybugImageMetaData;


/**
 *   The Ladybug processed image structure.
 */
typedef struct LadybugProcessedImage
{ 
   /** Width, in pixels, of the stitched image. */
   unsigned int      uiCols;

   /** Height, in pixels, of the stitched image. */
   unsigned int      uiRows;

   /** Pointer to the image data. */
   unsigned char*    pData;
   
   /** The pixel format of the image. */
   LadybugPixelFormat pixelFormat;

   /** Metadata of the image. */
   LadybugImageMetaData   metaData;

   /** Reserved. */
   unsigned long ulReserved;

} LadybugProcessedImage;


/**
 *   A record used in querying the camera properties.
 */
typedef struct LadybugCameraInfo
{
   /*
    * Base unit serial number for Ladybug2 or ealier model.
    * For Ladybug3, it is assigned the same number as serialHead.
    */
   LadybugSerialNumber	serialBase;

   /** Camera serial number. */
   LadybugSerialNumber	serialHead;

   /** Indicates whether or not the camera is a colour camera. */
   bool bIsColourCamera;

   /** Camera type. */
   LadybugDeviceType deviceType;

   /** Model name string. */
   char pszModelName[ 256 ];

   /** Sensor info string. */
   char pszSensorInfo[ 256 ];

   /** Vendor name string. */
   char pszVendorName[ 256 ];

   /** Version of the IEEE 1394 spec this device is compliant with. Value is
    * version * 100.
    */
   int iDCAMVer;

   /** Low-level bus number. */
   int iBusNum;

   /** Low-level node number. */
   int iNodeNum;

   /**  Maximum bus speed. */
   LadybugBusSpeed   maxBusSpeed;
   
} LadybugCameraInfo;


/**
 * A camera trigger property
 */
typedef struct _LadybugTriggerModeInfo
{
   /** Presence of trigger mode */
   bool bPresent;

   /** Whether or not the user can read values in the trigger functionality. */
   bool bReadOutSupported;

   /** Whether or not the functionality can be turned on or off. */
   bool bOnOffSupported;

   /** Whether or not the polarity can be changed. */
   bool bPolaritySupported;

   /** Whether or not the raw trigger input can be read. */
   bool bValueReadable;

   /** A bit field indicating which trigger sources are available. */
   unsigned int uiSourceMask;

   /** Whether or not software triggering is available. */
   bool bSoftwareTriggerSupported;

   /** A bit field indicating which trigger modes are available. */
   unsigned int uiModeMask;

} LadybugTriggerModeInfo;

/*
 * A camera trigger
 */
typedef struct _LadybugTriggerMode
{      
   /** On off enabled/disabled */
   bool bOnOff;

   /** The polarity of the trigger. 1 or 0. */
   unsigned int uiPolarity;

   /** The trigger source.  Corresponds to the source mask. Use 7 for software triggering. */
   unsigned int uiSource; 

   /** The trigger mode.  Corresponds to the mode mask. */
   unsigned int uiMode;

   /** The (optional) parameter to the trigger function, if required. */
   unsigned int uiParameter;      

} LadybugTriggerMode;

/*
 *	 A camera strobe property
 */
typedef struct _LadybugStrobeInfo
{
  /** Strobe source to be queried. */
  unsigned int uiSource;

  /** Indicates if strobe is supported. */
  bool bAvailable;

  /** Describes whether the source allows reading of the current value. */
  bool bReadOutSupported;

  /** Describes whether the source can be turned on or off. */
  bool bOnOffSupported;

  /** Describes whether the source's polarity can be changed. */
  bool bPolaritySupported;

  /** This parameter holds the minimum value of the delay and duration. */
  float fMinValue;

  /** This parameter holds the maximum value of the delay and duration. */
  float fMaxValue;

} LadybugStrobeInfo;

/*
 *	 A camera strobe
 */
typedef struct _LadybugStrobeControl
{      
   /** Strobe source to be set */
   unsigned int uiSource;

   /** Describes whether to turn the strobe on or off. */
   bool bOnOff;

   /** The polarity of the strobe. 1 or 0. */
   unsigned int uiPolarity;

   /** The delay of the strobe. */
   float fDelay;

   /** The duration of the strobe. */
   float fDuration;

} LadybugStrobeControl;


/*
 *	 A structure to control stabilization. 
 */
typedef struct _LadybugStabilizationParams
{
   /**
    * The square of this number is used for the number of templates in the 
    * image of one camera.
    * A higher value produces more reliable results, at the expense of 
    * processing speed.
    * A range between 5 and 8 is preferable.
    */
   int      iNumTemplates;
   
   /**
    * Templates are searched in each image within the range specified by this
    * value, in pixels.
    * If camera movement is significant and/or the frame rate is low, a higher 
    * value should be specified. However, a higher value results in lower 
    * processing speed.
    * A range between 50 and 200 is preferable.
    */
   int      iMaximumSearchRegion;

   /**
    * Rotational differences accumulate over time in successive frames.
    * To prevent these differences from accumulating, the rotation result can 
    * fall back to an initial position. This value determines how gradually the
    * fall back, or 'decay,' should take place.
    * A value between 0 and 1 must be specified. A value of 1 specifies no decay.
    * A value between 0.9 and 1.0 is usually used.
    */
   double   dDecayRate;

   int reserved[ 28];

} LadybugStabilizationParams;

/**
 *   A structure to control dynamic stitching.
 */
typedef struct _LadybugDynamicStitchingParams
{
   /**
    * The range of distances being searched by the dynamic stitching mechanism. 
    * If the distances to the subjects in the scene falls within a known range, it
    * can be set to avoid false matching. 
    * Also, by limiting the range, the precision of the search result could be
    * improved.
    * The values are in meters and the default values for dMinimumDistance is 2,
    * dMaximumDistance is 100, and dDefaultDistance is 20.
    * For all the three members, the value less than 0.5 can not be set.
    */
   double      dMinimumDistance;
   double      dMaximumDistance;
   double      dDefaultDistance;

   int reserved[ 26];

} LadybugDynamicStitchingParams;

/**
 *   A value that represents the size of the histogram array
 *   of LadybugImageStatistics struct.
 */
#define LADYBUG_HISTOGRAM_SIZE   256


/**
 *	 Structure containing Ladybug image statistics data.
 */
typedef struct _LadybugImageStatistics
{
   enum Channel
   {
      GREY,
      RED,
      GREEN,
      BLUE,
      NUM_STATISTICS_CHANNELS
   };
   
   typedef struct _ChannelData
   { 
      /** Whether this channel has valid data.  */
      bool bValid; 

      /** Minimum possible pixel value for this channel. */
      unsigned int uiRangeMin;

      /** Maximum possible pixel value for this channel. */
      unsigned int uiRangeMax;

      /** Minimum pixel value of the channel. */
      unsigned int uiPixelValueMin;

      /** Maximum pixel value of the channel. */
      unsigned int uiPixelValueMax;

      /** Mean value of the channel. */
      float fPixelValueMean;      

      /**
       * Histogram array. Each value in the array contains the pixel
       * count for the corresponding pixel value. For example, if 
       * histogram[1] is 100, that means there are 100 pixels in the image
       * with a pixel value of 1 for that channel. 
       */
      int uiHistogram[ LADYBUG_HISTOGRAM_SIZE ];  

   } ChannelData;

   ChannelData StatisticsData[ NUM_STATISTICS_CHANNELS ];

} LadybugImageStatistics;

/*
 * 
 *	 Structure containing color correction parameters.
 */
typedef struct _LadybugColorCorrectionParams
{
   /** The hue value. */
   int iHue;

   /** The saturation value. */
   int iSaturation;

   /** The intensity value. */
   int iIntensity;

   /** The red value */
   int iRed;

   /** The green value */
   int iGreen;

   /** The blue value */
   int iBlue;

   /** Reserved field. Should not be used. */
   int reserved[ 25];

}LadybugColorCorrectionParams;

/*@}*/ 

/** 
 * @defgroup GeneralFunctions General Functions 
 */

/*@{*/ 

/**
 *   Returns a string describing the passed LadybugError.
 *
 * @param   error - The LadybugError to convert.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 */
LADYBUGDLL_API const char*
ladybugErrorToString( 
            const LadybugError error );


/**
 *   Returns the version numbers of the ladybug library.
 *
 *   @param context  - The LadybugContext to access.
 *   @param puiMajor - The major version number
 *   @param puiMinor - The minor version number
 *   @param puiType  - The version type (0-alpha, 1-beta, 2-release)
 *   @param puiBuild - The build number
 *
 *   @return A LadybugError indicating the success of the function.
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetLibraryVersion( 			   
            LadybugContext context,
            unsigned int* puiMajor,
            unsigned int* puiMinor,
            unsigned int* puiType,
            unsigned int* puiBuild );

/**
 *   Writes the specified image to disk. 
 *
 * @param   context         - The LadybugContext to access.
 * @param   pProcessedImage - The image to save.
 * @param   pszPath         - The name of the file to write to.
 * @param   format          - The file format to write to. See LadybugSaveFileFormat.
 * @param   bAsync          - A flag indicating if the image saving operation is 
 *                     synchronous or asynchronous. If true, the image saving 
 *                     operation is asynchronous and this function returns
 *                     immediately. The default value is false.
 *
 * @return   A LadybugError indicating the success of the function.   
 *
 * Remarks:
 *   If the file format is LADYBUG_FILEFORMAT_JPG, the JPEG compression quality
 *   may be set by calling ladybugSetImageSavingJpegQuality().
 *   
 *   If the file format is LADYBUG_FILEFORMAT_EXIF, the metadata in 
 *   LadybugProcessedImage should be filled in properly.
 *
 *   If bAsync is not specified or specified as false, the image saving is 
 *   performed synchronously. The function is blocked until the image saving
 *   operation completes.
 *
 *   If bAsync is true, the image saving is performed asynchronously on a 
 *   separate thread. The function returns immediately, before the operation 
 *   completes. Note that when attempting to access the image file specified by 
 *   pszPath, the file does not appear on disk until the image saving operation 
 *   completes.
 *
 * @see   ladybugSetImageSavingJpegQuality(),
 *   ladybugGetImageSavingJpegQuality()
 *
 */
LADYBUGDLL_API LadybugError
ladybugSaveImage(
		 LadybugContext                context,
		 const LadybugProcessedImage*  pProcessedImage,
		 const char*                   pszPath,
		 LadybugSaveFileFormat         format,
                 bool                          bAsync = false );

/**
 *   Sets the JPEG compression quality to use when saving JPEG images.
 *
 * @param   context         - The LadybugContext to access.
 * @param   iQuality	     - The JPEG compression quality to use. 
 *                     The valid value range is between 1 and 100. Default is 85.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugSaveImage(),
 *   ladybugGetImageSavingJpegQuality()
 *
 */
LADYBUGDLL_API LadybugError
ladybugSetImageSavingJpegQuality(
		 LadybugContext			context,
		 int				iQuality);

/**
 *   Gets the JPEG compression quality being used when saving JPEG images.
 *
 * @param   context         - The LadybugContext to access.
 * @param   piQuality	     - A pointer to the JPEG quality being used to save images.
 *
 * @return   A LadybugError indicating the success of the function.   
 *
 * @see   ladybugSaveImage(), 
 *   ladybugSetImageSavingJpegQuality()
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetImageSavingJpegQuality(
		 LadybugContext			context,
		 int*				piQuality);

/**
 *   Enables or disables image stabilization functionality.
 *   When stabilization is enabled, the output of stitched images are
 *   stabilized so that the effect of camera rotation is minimized.
 *   This feature works by setting an initial rotation position, and in
 *   successive frames, the rotation positions fall back to that initial
 *   setting according to a specified decay rate.
 *   This function can be applied either during image grabbing or
 *   when images are read from stream files. We recommend enabling image
 *   stabilization while reading stream files, as this feature can be 
 *   computationally intensive and may result in lost frames during image capture.
 *
 * @param   context         - The LadybugContext to access.
 * @param   bEnable	     - Flag to indicate whether stabilization is enabled or disabled.
 * @param   pParams         - The stabilization control parameters used when bEnable is
 *                     true. If this is null, the default parameters are used.
 *
 * @return   A LadybugError indicating the success of the function.   
 *
 * @see   ladybugConvertImage().
 *
 */
LADYBUGDLL_API LadybugError
ladybugEnableImageStabilization(
		 LadybugContext			context,
		 bool				bEnable,
                 LadybugStabilizationParams     *pParams);


/*@}*/ 

/** 
 * @defgroup ContextCreationMethods Context Creation and Initialization Methods 
 *
 * The functions contained within this group allow users
 * to create and initialize the camera context.  Generally speaking, these
 * functions need to be called prior to other functions in the library.
 */

/*@{*/ 


/**
 *   Creates a new context for accessing the camera-specific functions of the
 *   library.  
 *
 * @param   pcontext - A pointer to a LadybugContext to fill with the created context.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   A context must be created for every camera that is going to be controlled.
 *   This must be done before any other function calls can be made.
 *
 *   This function will set the context to NULL if it is unsuccessful.
 *
 * @see   ladybugDestroyContext()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugCreateContext( LadybugContext* pcontext );


/**
 *   Frees memory associated with the LadybugContext.
 *
 * @param   pcontext - A pointer to the LadybugContext to destroy.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function should be called when your application stops using the Ladybug API.
 *   
 *   This function will set the context to NULL if successful.
 *
 * @see   ladybugCreateContext()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugDestroyContext( LadybugContext* pcontext );


/**
 *   Initializes a camera on the 1394a or 1394b bus using a serial number.  
 *
 * @param   context      - The LadybugContext to access.
 * @param   serialNumber - The serial number of the Ladybug to initialize.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function, ladybugInitializePlus(), or ladybugInitializeFromIndex()
 *   must be called before any of the ladybugStart commands.
 *
 * @see   ladybugInitializeFromIndex(),
 *   ladybugInitializePlus()
 *   ladybugStart(),
 *   ladybugStartEx(),
 *   ladybugStartLockNext(),
 *   ladybugStartLockNextEx()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugInitializeFromSerialNumber( 
            LadybugContext      context,
            LadybugSerialNumber serialNumber );


/**
 * @param   context  - The LadybugContext to access.
 * @param   ulDevice - The device number of the Ladybug to initialize. Use 0 to 
 *              initialize the first (or only) Ladybug on the bus.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function, ladybugInitializePlus(), or ladybugInitializeFromIndex() 
 *   must be called before any of the ladybugStart commands.
 *
 * @see   ladybugInitializePlus()
 *   ladybugInitializeFromSerialNumber(),
 *   ladybugStart(),
 *   ladybugStartEx(),
 *   ladybugStartLockNext(),
 *   ladybugStartLockNextEx()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugInitializeFromIndex( 
            LadybugContext context,
            unsigned long  ulDevice );

/**
 * @param   context - The LadybugContext to access.
 * @param   parInfo - An array of LadybugCameraInfo structures, at least as
 *             large as the number of Ladybug cameras on the bus.
 * @param   puiSize - The size of the array passed in. The number of cameras
 *             detected is passed back in this argument also.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function fills an array of LadybugCameraInfo structures with all of 
 *   the pertinent information from the attached cameras.
 *   If camera is not a Ladybug, the deviceType in the LadybugCameraInfo 
 *   structure is set as LADYBUG_DEVICE_UNKNOWN.
 *
 */
LADYBUGDLL_API LadybugError 
ladybugBusEnumerateCameras(
            LadybugContext       context,
            LadybugCameraInfo*   parInfo,
            unsigned int*        puiSize );


/**
 *   Initialize a camera on the 1394a or 1394b bus using a device number. This function also allows the user to specify the number of buffers to use, and 
 *   optionally allocate those buffers outside the library.
 *
 * @param   context      - The LadybugContext to access.
 * @param   uiBusIndex   - The zero-based device index of the camera to be initialized.
 * @param   uiNumBuffers - The number of buffers to expect or allocate.  For 
 *                  lock next mode, the minimum number of buffers is 2.  
 *                  For lock latest mode, the minimum number of buffers 
 *                  is 4.  The maximum  number of buffers is limited only by
 *                  system memory.
 * @param   pBuffer      - A pointer to the user-supplied buffer.  If this argument 
 *                  is NULL the library will allocate and free the buffers
 *                  internally, otherwise the caller is responsible for
 *                  allocation and deallocation.  
 *                  This buffer has to be one buffer that can hold the entire
 *                  images. Therefore, the size of the buffer has to be
 *                    uiSize >= uiNumBuffers * size_of_each_image.
 *                  No boundary checking is
 *                  performed on these images, so if you are supplying your own
 *                  buffers, they must be large enough to hold the largest
 *                  image that is expected.
 * @param   uiSize       - The size of the buffer. This is valid when pBuffer is not NULL.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   Identical behaviour to ladybugInitializeFromIndex, except that 
 *   the user has the option of specifying the number of buffers to use, and 
 *   optionally allocate those buffers outside the library.
 *   Also, since from SDK 1.6, the function prototype has been changed.
 *   Fore more information, see Arguments section.
 *
 * @see   ladybugInitializeFromIndex(),
 *   ladybugInitializeFromSerialNumber(),
 *   ladybugStart(),
 *   ladybugStartEx(),
 *   ladybugStartLockNext(),
 *   ladybugStartLockNextEx()
 *
 */
LADYBUGDLL_API LadybugError
ladybugInitializePlus(
            LadybugContext    context,
            unsigned int      uiBusIndex,
            unsigned int      uiNumBuffers,
            unsigned char*    pBuffer,
            unsigned int      uiSize );


/**
 *   Writes the configuration information of the context to a file.
 *
 * @param   context           - The LadybugContext to access.
 * @param   pszConfigFileName - The name of the configuration file. If this file
 *                       already exists, this function overwrites the existing
 *                       file. If pszConfigFileName is NULL, this function
 *                       returns an error.
 *
 * @return   A LadybugError indicating the success of the function.
 * @see ladybugLoadConfig()
 */
LADYBUGDLL_API LadybugError 
ladybugWriteConfigurationFile( 
            LadybugContext context,
            const char*    pszConfigFileName  );


/**
 *   Retrieves camera information for the given context.
 *
 * @param   context - The LadybugContext to access.
 * @param   pinfo   - A pointer to a LadybugCameraInfo structure to be populated.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetCameraInfo( 
            LadybugContext	  context,
            LadybugCameraInfo*   pinfo );


/**
 *   Sets the asynchronous and isochronous transmit and receive bus speeds.
 *
 * @param   context       - The LadybugContext to access.
 * @param   asyncBusSpeed - One of the available bus speeds, LADYBUG_S100, etc.
 * @param   isochBusSpeed - One of the available bus speeds, LADYBUG_S100, etc.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   If only one of asyncBusSpeed or isochBusSpeed is required, set the other
 *   parameter to LADYBUG_S_FASTEST.
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetBusSpeed(
            LadybugContext	  context,
            LadybugBusSpeed      asyncBusSpeed,
            LadybugBusSpeed      isochBusSpeed );


/**
 *   Gets the current isochronous bus speed and the current asynchronous bus 
 *   speed.
 *
 * @param   context       - The LadybugContext to access.
 * @param   pAsyncSpeed   - The location to return current asynchronous bus speed
 * @param   pIsochSpeed   - The location to return current isochronous bus speed
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   If the camera has not been initialized, LADYBUG_NOT_INITIALIZED is returned.
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetBusSpeed(
            LadybugContext	  context,
            LadybugBusSpeed*     pAsyncSpeed,
            LadybugBusSpeed*     pIsochSpeed );


/*@}*/ 

/** 
 * @defgroup CameraStartMethods Camera Start and Image Grab Methods 
 *
 * All of the functions in this group allow the user
 * to initiate data transmission from the camera and acquire images.
 */

/*@{*/ 

/**
 *   Starts the camera.  
 *
 * @param   context    - The LadybugContext to access.
 * @param   resolution - The resolution to start the camera in. This has to be LADYBUG_RESOLUTION_ANY.
 * @param   format     - The data format to start the camera in.
 * @param   frameRate  - The frame rate to start the camera in. This is not used.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function must be called before ladybugGrabImage().
 *
 *   For Ladybug2 and Ladybug3 cameras, this function 
 *   always starts the camera in Format 7 custom image mode. 
 *
 *   The frameRate parameter is ignored. If the frame rate should be controlled,
 *   users can use ladybugStartEx function. Or, it is also possible to control frame
 *   rate by calling ladybugSetAbsProperty with LADYBUG_FRAME_RATE property after
 *   starting the camera.
 *
 * @see   ladybugStartEx(),
 *   ladybugStartLockNext(),
 *   ladybugStartLockNextEx(),
 *   ladybugStop()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugStart( 
            LadybugContext    context,
            LadybugResolution resolution,
            LadybugDataFormat format,
            int               frameRate = 0);


/**
 *   Starts the camera with the specified packet size and image buffer size.  
 *
 * @param   context      - The LadybugContext to access.
 * @param   resolution   - The resolution to start the camera in. This has to be LADYBUG_RESOLUTION_ANY.
 * @param   format       - The data format to start the camera in.
 * @param   uiPacketSize - The packet size.
 * @param   uiBufferSize - The image buffer size for receiving image data.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function must be called before ladybugGrabImage(). 
 *
 *   This function negotiates 1394 bandwidth between the camera and the PC. 
 *   The bandwidth is negotiated based on two parameters:
 *
 *   * The number of bytes sent in a packet every 1394 cycle (there are 8000
 *     cycles per second). On 1394a, this is a maximum of 4096 and on 1394b,
 *     this is a maximum of 9792. As there is a limited amount of bandwidth
 *     on the bus, any bandwidth used limits what is available to other devices 
 *     on the bus.
 *   * The total size of the buffer to be used for each image. The maximum
 *     size is the total number of pixels on all of the sensors
 *     (1024x768x6 = 4718592 for the Ladybug2, or 1616x1232x6 = 11945472 for 
 *     the Ladybug3). The larger the buffer size, the lower the maximum 
 *     transferred frame rate. Please see the table below for an example.
 *
 *   In order to achieve the desired frame rate, the user may also have to
 *   set two additional parameters:
 *
 *   * Set the frame rate on the head unit using the ladybugSetAbsProperty()
 *     function in order to adjust the number of images actually being 
 *     generated.
 *   * When using JPEG formats, use the auto JPEG compression quality setting
 *     functionality by calling ladybugSetAutoJPEGQualityControlFlag() function
 *     in order to make sure that the data being produced does not exceed the 
 *     buffer size.
 * 
 *   If the value of uiPacketSize is not specified or specified as 0, 
 *   this call starts the camera with the current packet size value. 
 *   
 *   If the value of uiBufferSize is not specified or specified as 0, 
 *   this call starts the camera with the current buffer size setting 
 *   for JPEG compressed images and use the maximum buffer size value
 *   for un-compressed images.
 *
 *  Example:
 *   The following tables indicate a couple of useful combinations of the
 *   packet size and buffer size parameters.
 *   Basically, the buffer size and maximum frame rate are trade off.
 *   This is useful for JPEG formats because you can adjust the image quality
 *   ( determined by the buffer size) and the frame rate based on your 
 *   requirement.
 *
 *   * Ladybug2
 *   |------------|----------------|-------------|-------------|---------------|
 *   | 1394 speed | Cameras on Bus | Packet Size | Buffer Size | Max Frame Rate|
 *   |------------|----------------|-------------|-------------|---------------|
 *   |    S800    |       1        |    9792     |  2400000    |   29.38fps    |
 *   |    S800    |       1        |    9792     |  4718592    |   14.69fps    |
 *   |    S800    |       2        |    4096     |  1200000    |   29.38fps    |
 *   |    S400    |       1        |    4096     |  1000000    |   29.38fps    |
 *   |    S400    |       2        |    2048     |  1000000    |   14.69fps    |  
 *   |------------|----------------|-------------|-------------|---------------|
 *
 *   * Ladybug3
 *   |------------|----------------|-------------|-------------|---------------|
 *   | 1394 speed | Cameras on Bus | Packet Size | Buffer Size | Max Frame Rate|
 *   |------------|----------------|-------------|-------------|---------------|
 *   |    S800    |       1        |    9792     |  4650848    |   16.0fps     |
 *   |    S800    |       1        |    9792     | 11945472    |    6.5fps     |
 *   |    S800    |       2        |    4096     |  4650848    |    7.0fps     |
 *   |    S400    |       1        |    4096     |  4650848    |    7.0fps     |
 *   |    S400    |       1        |    4096     |  2571056    |   12.1fps     |
 *   |    S400    |       2        |    2048     |  4650848    |    3.5fps     |  
 *   |------------|----------------|-------------|-------------|---------------|
 *
 * @see   ladybugStart(),
 *   ladybugStartLockNext(),
 *   ladybugStartLockNextEx(),
 *   ladybugStop()
 *   ladybugSetAutoJPEGQualityControlFlag()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugStartEx( 
            LadybugContext    context,
            LadybugResolution resolution,
            LadybugDataFormat format,
            unsigned int      uiPacketSize = 0,
            unsigned int      uiBufferSize = 0);


/**
 *   Starts the camera and initializes the library for "lock next"
 *   functionality.  
 *
 * @param   context    - The LadybugContext to access.
 * @param   resolution - The resolution to start the camera in.  This has to be LADYBUG_RESOLUTION_ANY.
 * @param   format     - The data format to start the camera in.
 * @param   frameRate  - The frame rate to start the camera in. This is not used.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function should be used instead of ladybugStart() or
 *   ladybugStartEx() to start the camera in "lock next" mode. 
 *   For "lock latest" functionality, use ladybugStart() and 
 *   ladybugLockLatest().
 *
 *   For Ladybug2 and Ladybug3 cameras, this function 
 *   always starts the camera in Format 7 custom image mode. 
 *
 *   The frameRate parameter is ignored. If the frame rate should be controlled,
 *   users can use ladybugStartEx function. Or, it is also possible to control frame
 *   rate by calling ladybugSetAbsProperty with LADYBUG_FRAME_RATE property after
 *   starting the camera.
 *
 * @see   ladybugStart(),
 *   ladybugStartEx(),
 *   ladybugStartLockNextEx(),
 *   ladybugStop()
 *
 */
LADYBUGDLL_API LadybugError
ladybugStartLockNext(
            LadybugContext    context,
            LadybugResolution resolution,
            LadybugDataFormat format,
            int               frameRate = 0);


/**
 *   Starts the camera with the specified packet size and image buffer size, and initializes the library for "lock next"
 *   functionality.
 *
 * @param   context      - The LadybugContext to access.
 * @param   resolution   - The resolution to start the camera in. This has to be LADYBUG_RESOLUTION_ANY.
 * @param   format       - The data format to start the camera in.
 * @param   uiPacketSize - The packet size.
 * @param   uiBufferSize - The buffer size for receiving JPEG image data.
 *
 * @return   A LadybugError indicating the success of the function. 
 *
 * Remarks:
 *   This function should be used for the "lock next" functions.
 *
 *   If the value of uiPacketSize is not specified or specified as 0, 
 *   this call starts the camera with the current packet size value. 
 *   
 *   If the value of uiBufferSize is not specified or specified as 0, 
 *   this call starts the camera with the current buffer size setting 
 *   for JPEG compressed images and use the maximum buffer size value
 *   for un-compressed images.
 *
 *   For "lock latest" functionality, use ladybugStart(),
 *   ladybugLockLatest() or ladybugStartEx().
 *
 *   See comments in ladybugStartEx() for bandwidth negotiation between the
 *   camera and the PC. 
 *
 * @see   ladybugStart(),
 *   ladybugStartEx(),
 *   ladybugStartLockNext(),
 *   ladybugStop()
 *
 */
LADYBUGDLL_API LadybugError
ladybugStartLockNextEx(
            LadybugContext    context,
            LadybugResolution resolution,
            LadybugDataFormat format,
            unsigned int      uiPacketSize = 0,
            unsigned int      uiBufferSize = 0);

             
/**
 *   Stops the camera from grabbing images.
 *
 * @param   context - The LadybugContext to access.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function should be called to stop the camera from sending images to the
 *   driver on the host machine. This function actually frees any previously
 *   negotiated bandwidth.
 *
 * @see   ladybugStart(),
 *   ladybugStartEx(),
 *   ladybugStartLockNext(),
 *   ladybugStartLockNextEx()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugStop(
	    LadybugContext context );


/**
 *
 * Name: ladybugSetGrabTimeout()
 *
 * 
 *   Sets the timeout value for grab functions.
 *
 * @param   context   - The LadybugContext to access.
 * @param   uiTimeout - The timeout value, in milliseconds.  A value of 
 *               LADYBUG_INFINITE indicates an infinite wait.  A value of
 *               zero indicates a nonblocking grab call.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   Use of this capability is recommended in cases where it is not desirable
 *   to wait for the next image to arrive at the PC.  Setting uiTimeout to 0
 *   can also be useful in cases where 'Lock Next' functionality is being used 
 *   and one is trying to determine how far behind they are.
 *
 *   Since Ladybug SDK version 1.6.0.1, This function needs to be called prior 
 *   to the camera starting functions.
 *   
 * @see   ladybugStart(),
 *   ladybugStartEx(),
 *   ladybugStartLockNext(),
 *   ladybugStartLockNextEx()
 *
 */
LADYBUGDLL_API LadybugError
ladybugSetGrabTimeout(
            LadybugContext   context,
            unsigned int     uiTimeout );


/**
 *   Grabs the latest image that has not previously been grabbed.
 *
 * @param   context - The LadybugContext to access.
 * @param   pImage  - A pointer to an image structure. It will be filled with the
 *             image information.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   If an image is waiting, the function will return immediately. Otherwise,
 *   the function will block until the next image arrives or the grab timeout
 *   expires - whichever happens first.
 *
 * @see   ladybugSetGrabTimeout()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGrabImage( 
		 LadybugContext	 context,
		 LadybugImage*	 pImage );


/**
 *   Locks the "next" image that has not been seen until it is manually released.
 *
 * @param   context - The LadybugContext to access.
 * @param   pImage  - A pointer to an image structure. It will be filled with the
 *             image information.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   If there is an image available that has not yet been locked, this
 *   function will return immediately. Otherwise, it will block until an image
 *   arrives or the grab timeout expires - whichever happens first.
 *
 *   As long as the user locks and releases the image buffers fast enough to
 *   prevent the allocated buffers from filling up, this function will ensure
 *   that each image is seen. 
 *
 *   Users can verify image sequentiality by comparing sequence numbers of 
 *   images.
 *
 * @see   ladybugSetGrabTimeout(),
 *   ladybugUnlock(),
 *   ladybugUnlockAll()
 *
 */
LADYBUGDLL_API LadybugError
ladybugLockNext(
                LadybugContext   context,
                LadybugImage*    pImage );

  
/**
 *   Unlocks and returns a previously locked buffer into the pool to be filled by
 *   the camera driver.
 *
 * @param   context       - The LadybugContext to access.
 * @param   uiBufferIndex - The index of the buffer to unlock.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function must be called for each image locked using the lock 
 *   functions. Otherwise, the driver will run out of buffers.
 *
 * @see   ladybugLockNext(),
 *   ladybugUnlockAll()
 *
 */
LADYBUGDLL_API LadybugError
ladybugUnlock(
              LadybugContext  context,
              unsigned int    uiBufferIndex );

  
/**
 *   Unlocks all locked images.
 *
 * @param   context - The LadybugContext to access.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function is equivalent to maintaining a list of locked buffers and calling 
 *   ladybugUnlock() for each.
 *
 * @see   ladybugLockNext(),
 *   ladybugUnlock()
 *
 */
LADYBUGDLL_API LadybugError
ladybugUnlockAll(
                 LadybugContext  context );

/*@}*/ 

/** 
 * @defgroup ColorProcessingMethods Color Processing and Color Correction Methods 
 *
 * The functions contained within this group provide the functionality 
 * required to perform color processing and color correction on incoming
 * images.
 */

/*@{*/ 

/**
 *   Gets the current color processing method.
 *
 * @param   context - The LadybugContext to access.
 * @param   pMethod - The current color processing method.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugSetColorProcessingMethod()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetColorProcessingMethod( 
				LadybugContext		      context,
				LadybugColorProcessingMethod* pMethod );


/**
 *   Sets the color processing method to use.  
 *
 * @param   context - The LadybugContext to access.
 * @param   method  - The color processing method to set.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This method is useful when trying to change the quality of the images that are
 *   produced by the library.
 *   
 *   If the color processing method is set to LADYBUG_HQLINEAR_GPU, the color
 *   processing will be performed on the GPU. This function checks the
 *   availability of the required GPU resources, and may return 
 *   LADYBUG_GPU_CUDA_DRIVER_ERROR indicating the required GPU functions 
 *   are not supported or the GPU driver needs to be updated.
 *
 * @see   ladybugGetColorProcessingMethod()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetColorProcessingMethod( 
				LadybugContext               context,
				LadybugColorProcessingMethod method );


/**
 *   Gets the current color tile format.
 *
 * @param   context  - The LadybugContext to access.
 * @param   pFormat  - The current color tile format.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugSetColorTileFormat()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetColorTileFormat( 
			  LadybugContext	 context,
			  LadybugStippledFormat* pFormat );


/**
 *   Sets the current color tile format.
 *
 * @param   context - The LadybugContext to access.
 * @param   format  - The color tile format to set.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The color tile format is read from hardware and set automatically.  You should not
 *   have to use this function.
 *
 * @see   ladybugGetColorTileFormat()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetColorTileFormat( 
			  LadybugContext        context,
			  LadybugStippledFormat format );


/**
 *   Fills in the alpha channel value in the specified BGRA buffers. 
 *
 * @param   context         - The LadybugContext to access.
 * @param   uiCols          - The number of columns in the images.
 * @param   uiRows          - The number of rows in the images.
 * @param   arpBGRA32Images - The array of BGRA images
 * @param   pixelFormat     - Pixel format of the BGRA images
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The alpha channel specifies how the overlapped regions between cameras 
 *   should be rendered by OpenGL. Therefore, this function should be called 
 *   before passing the BGRA buffers to any of the OpenGL views.
 *
 * @see
 */
LADYBUGDLL_API LadybugError 
ladybugAddAlphaChannel(
            LadybugContext  context,
            unsigned int    uiCols,
            unsigned int    uiRows,
            unsigned char** arpBGRA32Images,
            LadybugPixelFormat pixelFormat = LADYBUG_BGRU);

/**
 *   Parses the 6 images in a LadybugImage into 
 *   6 BGRU32 buffers. 
 *
 *   This function is being deprecated and will be removed from SDK version 1.7. It is
 *   replaced by ladybugConvertImage().
 *
 * @param   context        - The LadybugContext to access.
 * @param   pImage         - A pointer to the raw image to be processed.
 * @param   arpDestBuffers - An array of pointers to destination buffers that will 
 *                    hold the processed images. If specified as NULL,
 *                    this function will use internal buffers as 
 *                    destination buffers.
 * @param   pImageInfo     - The array of stippled input images
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The current color processing method is used.
 *
 *   If arpDestBuffers is specified as NULL, this function will put the 
 *   processed images in internal buffers. If there are no internal 
 *   buffers, this function creates them.
 *   This function also checks the size of the internal buffers and adjusts 
 *   accordingly.
 *
 *   The alpha mask (see ladybuggeom.h) is only written to the 
 *   destination buffer the first time any of the Convert functions
 *   are called.  If you wish to use a different destination buffer,
 *   call ladybugSetAlphaMasking( true ) again.
 *   
 *   Falloff correction is applied if the falloff correction flag is on.
 *   Color correction is applied if the color correction flag is on.
 *   Image statistics data is calculated if the image statistics flag is on.
 *
 * @see   ladybugConvertImage()
 *   ladybugSetAlphaMasking(),
 *   ladybugSetFalloffCorrectionFlag(),
 *   ladybugSetFalloffCorrectionAttenuation(),
 *   ladybugSetColorCorrectionFlag(),
 *   ladybugGetColorCorrectionFlag(),
 *   ladybugSetColorCorrection(),
 *   ladybugGetColorCorrection()
 *   ladybugSetImageStatisticsFlag()
 *   ladybugGetImageStatisticsFlag()
 *   ladybugGetImageStatistics()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugConvertToMultipleBGRU32(
            LadybugContext      context,
            const LadybugImage* pImage,
            unsigned char**     arpDestBuffers,
            LadybugImageInfo*   pImageInfo  );

/**
 *   Converts the 6 images in a LadybugImage into 
 *   6 BGRA buffers. 
 *
 * @param   context        - The LadybugContext to access.
 * @param   pImage         - A pointer to the raw image to be processed.
 * @param   arpDestBuffers - An array of pointers to destination buffers that 
 *                           will hold the processed images. If specified as
 *                           NULL, this function will use internal buffers as 
 *                           destination buffers.
 * @param   pixelFormat    - Pixel format of the processed images. The
 *                           supported formats depend on the data format
 *                           of the raw image pointed by pImage. The default 
 *                           value is LADYBUG_UNSPECIFIED_PIXEL_FORMAT.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The current color processing method is used.
 *
 *   If arpDestBuffers is specified as NULL, this function will put the 
 *   processed images in internal buffers. If there are no internal 
 *   buffers, this function creates them.
 *   This function also checks the size of the internal buffers and adjusts 
 *   accordingly.
 *
 *   If pixelFormat is specified as LADYBUG_UNSPECIFIED_PIXEL_FORMAT, the 
 *   image will be converted to LADYBUG_BGRU for a raw8 or 8-bit JPEG raw
 *   image, or LADYBUG_BGRU16 for a raw16 or 12-bit JPEG raw image. If the raw
 *   image format is raw8 or 8-bit JPEG, specifying pixelFormat as 
 *   LADYBUG_BGRU16 will return LADYBUG_INVALID_ARGUMENT. 
 *
 *   The alpha mask (see ladybuggeom.h) is only written to the 
 *   destination buffer the first time any Convert functions
 *   are called.  If you wish to use a different destination buffer,
 *   call ladybugSetAlphaMasking( true ) again.
 *   
 *   Falloff correction is applied if the falloff correction flag is on.
 *   Color correction is applied if the color correction flag is on.
 *   Image statistics data is calculated if the image statistics flag is on.
 *
 * @see   ladybugSetAlphaMasking(),
 *   ladybugSetFalloffCorrectionFlag(),
 *   ladybugSetFalloffCorrectionAttenuation(),
 *   ladybugSetColorCorrectionFlag(),
 *   ladybugGetColorCorrectionFlag(),
 *   ladybugSetColorCorrection(),
 *   ladybugGetColorCorrection()
 *   ladybugSetImageStatisticsFlag()
 *   ladybugGetImageStatisticsFlag()
 *   ladybugGetImageStatistics()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugConvertImage(
            LadybugContext      context,
            const LadybugImage* pImage,
            unsigned char**     arpDestBuffers,
            LadybugPixelFormat  pixelFormat = LADYBUG_UNSPECIFIED_PIXEL_FORMAT );


/**
 *   Converts a LadybugImage to a set of color-processed images.  
 *
 * @param   context            - The LadybugContext to access.
 * @param   pImage             - A pointer to the image to be processed.
 * @param   arpszFilenames     - An array of pointers to filenames for
 *                        saving the images.
 * @param   pImageInfo         - Image information extracted from the retrieved 
 *                        image. Use NULL to disable.
 * @param   saveformat	        - The format to save the images in.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The current color processing method is used.
 *
 */
LADYBUGDLL_API LadybugError 
ladybugExtractLadybugImageToFilesBGRU32(
            LadybugContext	       context,
            const LadybugImage*    pImage,   
            const char**	       arpszFilenames,
            LadybugImageInfo*      pImageInfo,
            LadybugSaveFileFormat  saveformat );


/**
 *   Converts an interleaved data buffer to a set of color-processed images.  
 *
 * @param   context    - The LadybugContext to access.
 * @param   pImage     - A pointer to the raw image to be processed.
 * @param   iImage     - The image number this image corresponds to.  Use -1
 *                to disable image numbering in the output filenames.
 * @param   pszPath    - The base path to use when generating filenames.
 * @param   pImageInfo	- Image information extracted from the image. 
 *                Use NULL to disable.
 * @param   saveformat	- The format to save the images in.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The current color processing method is used.
 *
 *   Filenames are generated automatically.
 *
 *   The alpha mask (see ladybuggeom.h) are only written to the 
 *   destination buffer the first time any of the Convert functions
 *   are called.  If you wish to use a different destination buffer,
 *   call ladybugSetAlphaMasking( true ) again.
 *   
 *   Falloff correction is applied if the correction flag is on.
 *
 * @see   ladybugSetAlphaMasking(),
 *   ladybugSetFalloffCorrectionFlag(),
 *   ladybugSetFalloffCorrectionAttenuation()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugExtractLadybugImageToAutoFilesBGRU32(
            LadybugContext	      context,
            const LadybugImage*   pImage,   
            int                   iImage,
            const char*		      pszPath,
            LadybugImageInfo*     pImageInfo,
            LadybugSaveFileFormat saveformat );



/**
 *   Retrieves a flag indicating if color correction is applied in 
 *   ladybugConvertImage. It is off by default.
 *
 * @param   context          - The LadybugContext to access.
 * @param   pbCorrectColor   - Location to return the color correction flag.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugSetColorCorrectionFlag()
 *   ladybugGetColorCorrection()
 *   ladybugSetColorCorrection()
 *   ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetColorCorrectionFlag( 
         LadybugContext  context,
         bool*		pbCorrectColor );


/**
 *   Sets an internal flag indicating if color correction is applied
 *   in ladybugConvertImage. It is off by default.
 *
 * @param   context         - The LadybugContext to access.
 * @param   bCorrectColor   - A flag indicating if color correction is applied.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugGetColorCorrectionFlag()
 *   ladybugGetColorCorrection()
 *   ladybugSetColorCorrection()
 *   ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetColorCorrectionFlag( 
            LadybugContext  context,
            bool            bCorrectColor );


/**
 *   Retrieves the current color correction values.
 *
 * @param   context         - The LadybugContext to access.
 * @param   pParams         - The pointer to store the correction parameter struct.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugGetColorCorrectionFlag()
 *   ladybugSetColorCorrectionFlag()
 *   ladybugSetColorCorrection()
 *   ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetColorCorrection( 
            LadybugContext  context,
            LadybugColorCorrectionParams *pParams );


/**
 *   Sets the color correction parameters to be applied when it is enabled.
 *
 * @param   context         - The LadybugContext to access.
 * @param   pParams         - The pointer to the color correction parameter struct.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks: 
 *   The valid range of values is between -255 and 255.
 *   A value of 0 indicates no adjustment.
 *
 * @see   ladybugGetColorCorrectionFlag()
 *   ladybugSetColorCorrectionFlag()
 *   ladybugGetColorCorrection()
 *   ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetColorCorrection( 
            LadybugContext  context,
            LadybugColorCorrectionParams *pParams);


/**
 *   Retrieves a flag indicating if image sharpening is applied in 
 *   ladybugConvertImage. It is off by default.
 *
 * @param   context          - The LadybugContext to access.
 * @param   pbSharpening     - Location to return the sharpening flag.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugSetSharpening()
 *   ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetSharpening( 
         LadybugContext  context,
         bool*		pbSharpening );


/**
 *   Sets an internal flag indicating if image sharpening is applied
 *   in ladybugConvertImage. It is off by default.
 *
 * @param   context         - The LadybugContext to access.
 * @param   bSharpening     - A flag indicating if sharpening is applied.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugGetSharpening()
 *   ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetSharpening( 
            LadybugContext  context,
            bool            bSharpening );


/*@}*/ 

/** 
 * @defgroup LensFallOffMethods Lens Falloff Correction Methods
 *
 * Because of their short focal length, the 
 * lenses used in the Ladybug camera system suffer from lens falloff.  This
 * phenomenon can be observed in both raw and color-processed images as a 
 * darkening near the edges of the images.  
 * The functions contained in this group provide the the ability
 * to control the amount of correction applied to the images.
 * 
 * The correction can either be applied implicitly or explicitly as outlined
 * below.
 * Implicit - ladybugConvertImage will correct falloff with the 
 *  specified attenuation factor if and only if the correction flag has been 
 *  set via ladybugSetFalloffCorrectionFlag. The correction is done implicitly
 *  when the function parses the raw image into 6 individual BGRU images.
 */

/*@{*/ 

/**
 *   Retrieves a flag indicating if intensity falloff will be corrected in 
 *   ladybugConvertImage.
 *
 * @param   context          - The LadybugContext to access.
 * @param   pbCorrectFalloff - Location to return the intensity falloff 
 *                      correction flag.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The exact amount to be corrected is controlled by the correction
 *   attenuation factor set in ladybugSetFalloffCorrectionAttenuation.
 *
 * @see   ladybugSetFalloffCorrectionFlag(),
 *   ladybugGetFalloffCorrectionAttenuation(),
 *   ladybugSetFalloffCorrectionAttenuation(),
 *   ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetFalloffCorrectionFlag( 
         LadybugContext  context,
         bool*		pbCorrectFalloff );


/**
 *   Sets an internal flag indicating if intensity falloff will be corrected
 *   in ladybugConvertImage.
 *
 * @param   context         - The LadybugContext to access.
 * @param   bCorrectFalloff - A flag indicating if intensity falloff will be 
 *                     corrected.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The exact amount to be corrected is controlled by the correction
 *   attenuation factor set in ladybugSetFalloffCorrectionAttenuation().
 *
 * @see   ladybugGetFalloffCorrectionFlag(),
 *   ladybugGetFalloffCorrectionAttenuation(),
 *   ladybugSetFalloffCorrectionAttenuation(),
 *   ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetFalloffCorrectionFlag( 
            LadybugContext  context,
            bool            bCorrectFalloff );


/**
 *   Gets the current falloff correction value.
 *
 * @param   context               - The LadybugContext to access.
 * @param   pfAttenuationFraction - Location to return the fraction used for
 *                           falloff correction.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugGetFalloffCorrectionFlag(),
 *   ladybugSetFalloffCorrectionFlag(),
 *   ladybugSetFalloffCorrectionAttenuation()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetFalloffCorrectionAttenuation( 
            LadybugContext  context,
            float*          pfAttenuationFraction );

/**
 *   Sets the current falloff correction value.
 *
 * @param   context              - The LadybugContext to access.
 * @param   fAttenuationFraction - Fraction used to adjust the intensity correction 
 *                          amount. (Must be a value between 0.0 and 1.0).
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugGetFalloffCorrectionFlag(),
 *   ladybugSetFalloffCorrectionFlag(),
 *   ladybugGetFalloffCorrectionAttenuation()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetFalloffCorrectionAttenuation( 
            LadybugContext  context,
            float           fAttenuationFraction );



/**
 *   Applies intensity falloff correction on the specified BGRU images.
 *
 * @param   context         - The LadybugContext to access.
 * @param   uiCols          - The number of columns in the images.
 * @param   uiRows          - The number of rows in the images.
 * @param   arpBGRU32Images - The array of BGRU images.
 * @param   pixelFormat     - The pixel format of the BGRU images.
 * @param   lGamma          - The gamma value under which the images were captured.
 *                            (A -1 gamma value will invoke the default gamma value)
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The amount of correction applied will depend on the setting of the current
 *   correction attenuation factor (see ladybugSetFalloffCorrectionAttenuation)
 *   and the specified gamma.
 *
 *   The specified gamma should match the gamma setting when these images were
 *   originally captured. Gamma can be extracted either interactively from the
 *   Camera Control Dialog of the LadybugCap or LadybugCapPro programs, or programmatically from the
 *   ulGamma field inside the LaydbugImageInfo of the original LadybugImage.
 *   Note that the ulGamma field in LadybugImageInfo is in IEEE-1394
 *   register encoded format. Be sure to decode it appropriately to extract 
 *   the value (see description in the Point Grey Digital Camera Register Reference).
 *
 * @see   ladybugGetFalloffCorrectionAttenuation(),
 *   ladybugSetFalloffCorrectionAttenuation()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugCorrectBGRUFalloffEx(
                           LadybugContext  context,
                           unsigned int    uiCols,
                           unsigned int    uiRows,
                           unsigned char** arpBGRU32Images,
                           LadybugPixelFormat   pixelFormat,
                           long            lGamma );


/**
 *   Applies intensity falloff correction on the specified stippled images.
 *
 * @param   context           - The LadybugContext to access.
 * @param   uiCols            - The number of columns in the images.
 * @param   uiRows            - The number of rows in the images.
 * @param   arpStippledImages - The array of stippled images.
 * @param   lGamma            - The gamma value under which the images were captured.
 *                       (A -1 gamma value will invoke the default gamma value)
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The amount of correction applied will depend on the setting of the
 *   current correction attenuation factor (see ladybugSetFalloffCorrectionAttenuation)
 *   and the specified gamma.
 *
 *   The specified gamma should match the gamma setting when these images were
 *   originally captured. Gamma can be extracted either interactively from the
 *   Camera Control Dialog of the LadybugCap or LadybugCapPro programs or programmatically from the
 *   ulGamma field inside the LaydbugImageInfo of the original LadybugImage.
 *   Note that the ulGamma field in LadybugImageInfo is in IEEE-1394
 *   register encoded format. Be sure to decode it appropriately to extract 
 *   the value (see description in the Point Grey Digital Camera Register Reference).
 *
 * @see   ladybugGetFalloffCorrectionAttenuation(),
 *   ladybugSetFalloffCorrectionAttenuation()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugCorrectStippledFalloffEx(
            LadybugContext    context,
            unsigned int      uiCols,
            unsigned int      uiRows,
            unsigned char**   arpStippledImages,
            long              lGamma );

/*@}*/ 

/** 
 * @defgroup CameraPropMethods Camera Property Access and Control Methods
 *
 * These functions allow users
 * to access and control a variety of camera parameters.
 */

/*@{*/ 

/**
 *   Get information about the range of a specific camera property.
 *
 * @param   context   - The LadybugContext to access.
 * @param   property  - The camera property to query.
 * @param   pbPresent - Whether or not the property is present.
 * @param   plMin     - The minimum value of the property.
 * @param   plMax     - The maximum value of the property.
 * @param   plDefault - The default value of the property.
 * @param   pbAuto    - The availability of auto mode for the property.
 * @param   pbManual  - The ability to manually control the value of the property.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   The values obtained from this function are useful when trying to interpret
 *   and set camera properties with the ladybugGetProperty and 
 *   ladybugSetProperty functions.
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugGetAbsProperty(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetPropertyRange( 
            LadybugContext  context,
            LadybugProperty property,
            bool*           pbPresent,
            long*           plMin, 
            long*           plMax, 
            long*           plDefault,
            bool*           pbAuto,
            bool*           pbManual );


/**
 *   Gets information about the features and range of values of a specific camera property.  
 *
 * @param   context   - The LadybugContext to access.
 * @param   property  - The camera property to query.
 * @param   pbPresent - Whether or not the property is present.
 * @param   pbOnePush - The availability of the one push feature.
 * @param   pbReadOut - The ability to read out the value of this property.
 * @param   pbOnOff   - The ability to turn this property on and off.
 * @param   pbAuto    - The availability of auto mode for the property.
 * @param   pbManual  - The ability to manually control the value of the property.
 * @param   plMin     - The minimum possible value of the property.
 * @param   plMax     - The maximum possible value of the property.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This function provides better access to camera features as compared to
 *   ladybugGetPropertyRange(). The values obtained from this function are 
 *   useful when trying to interpret and set camera properties with the 
 *   ladybugGetProperty and ladybugSetProperty functions.
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugGetAbsProperty(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetPropertyRangeEx( 
            LadybugContext    context,
            LadybugProperty   property,
            bool*             pbPresent,
            bool*             pbOnePush,
            bool*             pbReadOut,
            bool*             pbOnOff,
            bool*             pbAuto,
            bool*             pbManual,
            long*             plMin, 
            long*             plMax );


/**
 *   Gets the range of possible absolute values of the specified camera property. 
 *
 * @param   context      - The LadybugContext to access.
 * @param   property     - The camera property to query.
 * @param   pbPresent    - Presence of the property.
 * @param   pfMin        - The absolute minimum value of the property.
 * @param   pfMax        - The absolute maximum value of the property.
 * @param   ppszUnits    - A string containing the units of the register.
 * @param   ppszUnitAbbr - A string containing an abbreviation of the units.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetAbsProperty(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetAbsPropertyRange( 
            LadybugContext  context,
            LadybugProperty property,
            bool*           pbPresent,
            float*          pfMin, 
            float*          pfMax, 
            const char**    ppszUnits,
            const char**    ppszUnitAbbr );


/**
 *   Gets the current values of the specified property.
 *
 * @param   context  - The LadybugContext to access.
 * @param   property - The camera property to query.
 * @param   plValueA - The "A", or first, value of the property.
 * @param   plValueB - The "B", or second, value of the property.
 * @param   pbAuto   - The current auto value of the property.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   Most properties only have an "A" value. 
 *
 * @see    ladybugSetProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetAbsProperty(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetProperty(
            LadybugContext   context,
            LadybugProperty  property,
            long*            plValueA,
            long*            plValueB,
            bool*            pbAuto );


/**
 *   Gets information about the features and current values of a specified camera property.  
 *
 * @param   context   - The LadybugContext to access.
 * @param   property  - The camera property to query.
 * @param   pbOnePush - The availability of the one push feature.
 * @param   pbOnOff   - The ability to turn this property on and off.
 * @param   pbAuto    - The auto value of the property.
 * @param   plValueA  - The "A" value.
 * @param   plValueB  - The "B" value.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This API function provides better access to camera features as compared to
 *   ladybugGetProperty().
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugSetPropertyEx(),
 *    ladybugGetAbsProperty(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetPropertyEx(
            LadybugContext   context,
            LadybugProperty  property,
            bool*            pbOnePush,
            bool*            pbOnOff,
            bool*            pbAuto,
            long*            plValueA,
            long*            plValueB );


/**
 *   Gets the current absolute value of the specified property.
 *
 * @param   context  - The LadybugContext to access.
 * @param   property - The camera property to query.
 * @param   pfValue  - A pointer to a float that will contain the result.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetAbsProperty(
            LadybugContext   context,
            LadybugProperty  property,
            float*           pfValue );


/**
 *   Gets information about the range of the absolute value of a specific camera property.  
 *
 * @param   context   - The LadybugContext to access.
 * @param   property  - The camera property to query.
 * @param   pbOnePush - The availability of the one push feature.
 * @param   pbOnOff   - The ability to turn this property on and off.
 * @param   pbAuto    - The auto value of the property.
 * @param   pfValue  - A pointer to a float that will contain the result.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This API function provides better access to camera features as compared to
 *   ladybugGetAbsProperty().
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugGetAbsProperty(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetAbsPropertyEx(
            LadybugContext   context,
            LadybugProperty  property,
            bool*            pbOnePush,
            bool*            pbOnOff,
            bool*            pbAuto,
            float*           pfValue );

/**
 *   Sets a camera property.  
 *
 * @param   context  - The LadybugContext to access.
 * @param   property - The camera property to query.
 * @param   lValueA  - The "A", or first, new value of the property.
 * @param   lValueB  - The "B", second, new value of the property.
 * @param   bAuto    - The auto value.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   Most properties only require an "A" value.
 *
 * @see    ladybugGetProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugGetAbsProperty(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetProperty(
            LadybugContext   context,
            LadybugProperty  property,
            long             lValueA,
            long             lValueB,
            bool             bAuto );


/**
 *   Sets the value and other features of a specified camera property.   
 *
 * @param   context   - The LadybugContext to access.
 * @param   property  - The camera property to query.
 * @param   bOnePush  - Specifies if the one push feature is enabled.
 * @param   bOnOff    - Specifies if the property should be on or off.
 * @param   bAuto     - Specifies if the property can be automatically controlled by the camera..
 * @param   lValueA   - The "A", or first, value of the property.
 * @param   lValueB   - The "B", or second, value of the property.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This API function provides better access to camera features as compared
 *   to ladybugSetProperty().
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugGetAbsProperty(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetPropertyEx(
            LadybugContext   context,
            LadybugProperty  property,
            bool             bOnePush,
            bool             bOnOff,
            bool             bAuto,
            const long       lValueA,
            const long       lValueB );


/**
 *   Sets the absolute value of a camera property.
 *
 * @param   context  - The LadybugContext to access.
 * @param   property - The camera property to query.
 * @param   fValue   - A float containing the new value of the parameter.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugGetAbsProperty(),
 *    ladybugGetAbsPropertyEx(),
 *    ladybugSetAbsPropertyEx(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetAbsProperty(
            LadybugContext   context,
            LadybugProperty  property,
            float            fValue );


/**
 *   Sets the absolute value of a camera property.  This function also allows the user to specify the one push, on/off, and auto settings of the same property. 
 *
 * @param   context   - The LadybugContext to access.
 * @param   property  - The camera property to query.
 * @param   bOnePush  - Specifies if the one push feature is enabled.
 * @param   bOnOff    - Specifies if the property should be on or off.
 * @param   bAuto     - Specifies if the property can be automatically controlled by the camera.
 * @param   fValue    - A float containing the new value of the parameter.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   This API function provides better access to camera features as compared
 *   to ladybugSetProperty().
 *
 * @see    ladybugGetProperty(),
 *    ladybugSetProperty(),
 *    ladybugGetPropertyEx(),
 *    ladybugSetPropertyEx(),
 *    ladybugGetAbsProperty(),
 *    ladybugSetAbsProperty(),
 *    ladybugGetPropertyRange(),
 *    ladybugGetPropertyRangeEx(),
 *    ladybugGetAbsPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetAbsPropertyEx(
            LadybugContext   context,
            LadybugProperty  property,
            bool             bOnePush,
            bool             bOnOff,
            bool             bAuto,
            float            fValue );

/**
 *   Gets the value of a register on the camera.
 *
 * @param   context    - The LadybugContext to access.
 * @param   ulRegister - The register to query.
 * @param   pulValue   - The returned register value.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   pulValue is set to zero if this function fails.
 *
 *   All of the Ladybug camera systems loosely follow the IIDC digital camera specification.
 *   As such, users wishing to explore low level camera
 *   configuration options should reference the Point Grey Digital Camera Register
 *   Reference.
 *
 * @see    ladybugSetRegister()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetRegister( 
            LadybugContext   context,
            unsigned long    ulRegister, 
            unsigned long*   pulValue );


/**
 *   Sets the value of a register on the camera.
 *
 * @param   context    - The LadybugContext to access.
 * @param   ulRegister - The register to set.
 * @param   ulValue    - The value of the register to set.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   All of the Ladybug camera systems loosely follow the IIDC digital camera specification.
 *   As such, users wishing to explore low level camera
 *   configuration options should reference the Point Grey Digital Camera Register
 *   Reference.
 *
 * @see    ladybugGetRegister()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetRegister( 
		   LadybugContext   context,
		   unsigned long    ulRegister, 
		   unsigned long    ulValue );


/**
 *   Provides block-read (asynchronous) access to the entire register space of 
 *   the Ladybug camera.
 *
 * @param   context    - The LadybugContext to access.
 * @param   usAddrHigh - The top 16 bits of the 48-bit absolute address to read.
 * @param   ulAddrLow  - The bottom 32 bits of the 48-bit absolute address to read.
 * @param   pulBuffer  - The buffer that will receive the data. Must be of size ulLength.
 * @param   ulLength   - The length, in quadlets, of the block to read.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see    ladybugWriteRegisterBlock()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugReadRegisterBlock( 
            LadybugContext      context,
            unsigned short      usAddrHigh,
            unsigned long       ulAddrLow,
            unsigned long*      pulBuffer,
            unsigned long       ulLength );


/**
 *   Provides block-write (asynchronous) access to the entire register space of 
 *   the Ladybug camera.
 *
 * @param   context    - The LadybugContext to access.
 * @param   usAddrHigh - The top 16 bits of the 48-bit absolute address to write.
 * @param   ulAddrLow  - The bottom 32 bits of the 48-bit absolute address to write.
 * @param   pulBuffer  - The buffer that contains the data to be written.
 * @param   ulLength   - The length, in quadlets, of the block to write.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see    ladybugReadRegisterBlock()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugWriteRegisterBlock( 
            LadybugContext         context,
            unsigned short         usAddrHigh,
            unsigned long          ulAddrLow,
            const unsigned long*   pulBuffer,
            unsigned long          ulLength );

/**
 *   Gets the range of possible values of a property associated with a 
 *   specified camera, independent of other Ccameras in the camera unit.
 *
 * @param   context   - The LadybugContext to access.
 * @param   property  - The independent property to query.
 * @param   uiCamera  - The camera to query.  
 * @param   pbPresent - The presence of the register.
 * @param   pulMin    - The minimum value.
 * @param   pulMax    - The maximum value.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see    ladybugSetIndPropertyRange()
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetIndPropertyRange( 
            LadybugContext	       context,
            LadybugIndependentProperty property,
            unsigned int               uiCamera,
            bool*                      pbPresent,
            unsigned long*             pulMin, 
            unsigned long*             pulMax );


/**
 *   Gets the current value and other features of a property associated 
 *   with a specified camera, independent of other cameras in the camera unit.
 *
 * @param   context        - The LadybugContext to access.
 * @param   property       - The independent property to query.
 * @param   uiCamera       - The CCD to query.  
 * @param   pulValue       - The current value of the property.
 * @param   pbOnOff        - Whether the property is on or off.
 * @param   pbAuto         - Whether or not the auto flag is set for the property.
 * @param   puiAutoExpCams - A bitfield indicating which of the other CCDs this CCD
 *                    should use for Auto Exposure calculations.  Only used
 *                    with LADYBUG_SUB_AUTO_EXPOSURE. See LadybugCameraBits.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see    ladybugSetIndProperty()
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetIndProperty(
            LadybugContext               context,
            LadybugIndependentProperty   property,
            unsigned int                 uiCamera,
            unsigned long*		 pulValue,
            bool*                        pbOnOff,
            bool*                        pbAuto,
            unsigned int*                puiAutoExpCams );


/**
 *   Sets the value of a property of a specified camera, independent of the 
 *   other cameras in the camera unit.
 *
 * @param   context       - The LadybugContext to access.
 * @param   property      - The independent property to query.
 * @param   uiCamera      - The camera to query.  
 * @param   ulValue       - The value to set.
 * @param   bOnOff        - Specifies if the property should be on or off. 
 *                          In Ladybug3, this flag affects the On/Off settings
 *                          of all the other cameras, too. If you set On to any one
 *                          of the cameras, then the camera is set to the independent
 *                          shutter (or gain) mode, where each shutter (or gain) can
 *                          take different values. If you set Off to any one of the
 *                          cameras, all the shutter ( or gain) values will be the
 *                          same across cameras.
 * @param   bAuto         - Specifies if the property should be automatically 
 *                          controlled by the camera. If you want to specify
 *                          the value manually with ulValue, this must be false.
 * @param   uiAutoExpCams - A bitfield indicating which of the other cameras this camera
 *                          should use for Auto Exposure calculations.  Only used
 *                          with LADYBUG_SUB_AUTO_EXPOSURE. See LadybugCameraBits.
 *                          This parameter is ignored in Ladybug3.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see    ladybugGetIndProperty()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetIndProperty(
            LadybugContext	         context,
            LadybugIndependentProperty   property,
            unsigned int                 uiCamera,
            unsigned long		 ulValue,
            bool                         bOnOff,
            bool		         bAuto,
            unsigned int                 uiAutoExpCams );


/*@}*/ 

/** 
 * @defgroup JPEGMethods JPEG Methods
 *
 * These functions are related to the camera and
 * library's JPEG compression functionality.  All of these functions are only applicable
 * to the Ladybug2 and Ladybug3.
 */

/*@{*/ 

/**
 *
 * Name: ladybugGetJPEGQuality()
 *
 * 
 *   Gets the current JPEG compression quality setting for the Compressor.
 *
 * @param   context   - The LadybugContext to access.     
 * @param   piQuality - The retrieved quality metric.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugSetJPEGQuality()
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetJPEGQuality( 
            LadybugContext   context,
            int*             piQuality );


/**
 *   Sets the JPEG compression quality setting for the Compressor.
 *
 * @param   context  - The LadybugContext to access.     
 * @param   iQuality - An integer from 1 to 100 indicating the JPEG compression 
 *              quality.  Higher settings result in a larger image
 *              data size and slower decompression rate.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugGetJPEGQuality()
 *
 */
LADYBUGDLL_API LadybugError
ladybugSetJPEGQuality( 
            LadybugContext   context,
            int              iQuality );


/**
 *   Gets the current value of the JPEG image buffer usage register.
 *
 * @param   context         - The LadybugContext to access.     
 * @param   puiBufferUsage  - The retrieved JPEG image buffer usage value.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * @see   ladybugSetAutoJPEGBufferUsage(),
 *   ladybugSetAutoJPEGQualityControlFlag(),
 *   ladybugGetAutoJPEGQualityControlFlag(),
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetAutoJPEGBufferUsage( 
                      LadybugContext   context,
                      unsigned int*    puiBufferUsage );


/**
 *   Sets a value to JPEG buffer usage register indicating the percentage of 
 *   of the image buffer used for JPEG image dada.  Specifying a value less 
 *   than the maximum allows for room in the image buffer to accommodate extra
 *   image data, depending on scene variations from frame to frame.
 *
 * @param   context       - The LadybugContext to access.     
 * @param   uiBufferUsage - An integer from 0x00 (0%) to 0x7F (100%) indicating the 
 *                   percentage of the image buffer used for JPEG image data.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   A value of 0 is treated as 0x66 (80%) for a Ladybug2 camera. On Ladybug3 
 *   firmware v1.2.2.1 or later, a value of 0 is treated as 0x72 (90%).
 *
 * @see   ladybugGetAutoJPEGBufferUsage()
 *   ladybugSetAutoJPEGQualityControlFlag(),
 *   ladybugGetAutoJPEGQualityControlFlag(),
 *
 */
LADYBUGDLL_API LadybugError
ladybugSetAutoJPEGBufferUsage( 
                              LadybugContext   context,
                              unsigned int     uiBufferUsage );


/**
 *   Gets the auto JPEG compression quality control flag.
 *
 * @param   context                  - The LadybugContext to access.
 * @param   pbAutoJPEGQualityControl - Location to return the auto JPEG quality 
 *                              control flag.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   If the returned value pointed by pbAutoJPEGQualityControl is true,
 *   the Ladybug camera is automatically controlling the JPEG compression
 *   quality.
 *
 * @see   ladybugSetAutoJPEGQualityControlFlag()
 *   ladybugGetAutoJPEGBufferUsage()
 *   ladybugSetAutoJPEGBufferUsage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetAutoJPEGQualityControlFlag( 
            LadybugContext  context,
            bool*           pbAutoJPEGQualityControl );


/**
 *   Sets the auto JPEG compression quality control flag.
 *
 * @param   context                 - The LadybugContext to access.
 * @param   bAutoJPEGQualityControl - A flag indicating if the Ladybug camera should
 *                             automatically control JPEG compression            
 *                             quality.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *   If bAutoJPEGQualityControl is true, the Ladybug camera automatically 
 *   controls JPEG compression quality.  
 *
 * @see   ladybugGetAutoJPEGQualityControlFlag()
 *   ladybugGetAutoJPEGBufferUsage()
 *   ladybugSetAutoJPEGBufferUsage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetAutoJPEGQualityControlFlag( 
            LadybugContext  context,
            bool            bAutoJPEGQualityControl );


/*@}*/ 

/** 
 * @defgroup TriggerMethods Trigger and Strobe methods
 *
 * The functions in this group allow the user to control triggering and strobe
 * functions.
 */

/*@{*/ 

/**
 *   This function retrieves information from the camera about the 
 *   trigger feature.
 *
 * @param   context   - The LadybugContext to access.
 * @param   pTriggerModeInfo - Structure that receives the information from 
 *                       the camera about the trigger.
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *
 * @see   ladybugGetTriggerMode()
 *   ladybugSetTriggerMode()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetTriggerModeInfo( 
            LadybugContext  context, 
            LadybugTriggerModeInfo* pTriggerModeInfo );

/**
 *   This function gets the current settings for the trigger feature. 
 *
 * @param   context      - The LadybugContext to access.
 * @param   pTriggerMode - Structure that receives the current settings 
 *                  from the camera about the trigger.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *
 * @see   ladybugGetTriggerModeInfo()
 *   ladybugSetTriggerMode()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetTriggerMode( 
            LadybugContext  context,
            LadybugTriggerMode* pTriggerMode );

/**
 *   This function sets the trigger settings on the camera.  Note 
 *   this function will also set the specified GPIO pin to an input
 *   for trigger input.
 *   Also note that in Ladybug2, the image grabbed at the trigger is
 *   the image of the previous trigger. So, there is one-trigger
 *   delay.
 *
 * @param   context      - The LadybugContext to access.
 * @param   pTriggerMode - Structure that provides the settings to be 
 *                  written to the camera.
 * @param   broadcast    - Flag indicating whether setting of the 
 *                  trigger should be broadcast.   
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *
 * @see   ladybugGetTriggerMode()
 *   ladybugGetTriggerModeInfo()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetTriggerMode( 
            LadybugContext  context, 
	    LadybugTriggerMode* pTriggerMode,
	    bool broadcast = false );		

/**
 *   This function retrieves information about the strobe feature
 *   from the camera.
 *
 * @param   context     - The LadybugContext to access.
 * @param   pStrobeInfo - Structure that receives the information from the 
 *                 camera about the strobe.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *
 * @see   ladybugGetStrobe()
 *   ladybugSetStrobe()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetStrobeInfo( 
            LadybugContext  context,
            LadybugStrobeInfo* pStrobeInfo );

/**
 *   This function gets the current settings for the strobe feature. 
 *   Note that the strobe pin must be specified in the structure 
 *   before being passed in as an argument.
 *
 * @param   context        - The LadybugContext to access.
 * @param   pStrobeControl - Structure that receives the current settings 
 *                    from the camera about the strobe.
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *
 * @see   ladybugGetStrobeInfo()
 *   ladybugSetStrobe()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetStrobe( 
            LadybugContext  context,
            LadybugStrobeControl* pStrobeControl );

/**
 *   This function sets up the strobe and turns it on for the
 *   specified source. Note that this function will also set the 
 *   GPIO pin to an output for strobe.
 *
 * @param   context        - The LadybugContext to access.
 * @param   pStrobeControl - Structure that provides the settings to be 
 *                    written to the camera.
 * @param   broadcast      - Flag indicating whether setting of the strobe 
 *                    feature should be broadcast.    
 *
 * @return   A LadybugError indicating the success of the function.
 *
 * Remarks:
 *
 * @see   ladybugGetStrobe()
 *   ladybugGetStrobeInfo()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetStrobe( LadybugContext  context,
            LadybugStrobeControl* pStrobeControl,
            bool           broadcast = false );


/**
 *    Sets an internal flag indicating if image statistics data will be 
 *    calculated in ladybugConvertImage().
 *
 * @param    context          - The LadybugContext to access.
 * @param    bImageStatistics - Flag indicating whether image statistics data
 *                       will be calculated.
 *
 * @return    A LadybugError indicating the success of the function.
 *
 * Remarks:
 *
 * @see    ladybugGetImageStatisticsFlag()
 *    ladybugGetImageStatistics()
 *    ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugSetImageStatisticsFlag( LadybugContext context, bool bImageStatistics );

/**
 *    Retrieves a flag indicating if image statistics are calculated in 
 *    ladybugConvertImage. Off by default.
 *
 * @param    context             - The LadybugContext to access.
 * @param    pbImageStatistics   - Location to return the image statistics flag.
 *
 * @return    A LadybugError indicating the success of the function.
 *
 * Remarks:
 *
 * @see    ladybugSetImageStatisticsFlag()
 *    ladybugGetImageStatistics()
 *    ladybugConvertImage()
 *
 */
LADYBUGDLL_API LadybugError 
ladybugGetImageStatisticsFlag( 
            LadybugContext  context,
            bool*           pbImageStatistics );

/**
 *    Gets image statistics data for the specified Ladybug camera unit.    
 *
 * @param    context     - The LadybugContext to access.
 * @param    uiCamera    - The camera index corresponding to the requested image 
 *                  statistics data.
 * @param    pStatistics - The pointer to LadybugImageStatistics to return 
 *                  the statistics data
 * 
 * @return    A LadybugError indicating the success of the function. 
 * 
 * Remarks: 
 *    If the image statistics flag has not been set by 
 *    calling ladybugSetImageStatisticsFlag(), this function returns
 *    LADYBUG_FAILED.
 *
 *    The bValid in struct LadybugImageStatistics indicates whether the
 *    data returned for this channel is valid.
 *
 *    For example, ladybugGetImageStatistics( Context, 2, &ImageStats )
 *    will return the image statistics data for camera 2, where
 *    ImageStats is defined as LadybugImageStatistics.
 *
 *
 * @see    ladybugSetImageStatisticsFlag()
 *    ladybugGetImageStatisticsFlag()
 *    ladybugConvertImage()
 */
LADYBUGDLL_API LadybugError
ladybugGetImageStatistics( 
                     LadybugContext context, 
                     unsigned int uiCamera, 
                     LadybugImageStatistics* pStatistics );

/**
 *    Instructs ladybugConvertToMultipleBGRU3, when called, to perform a 
 *    one-shot auto white balance adjustment.
 *
 * @param    context     - The LadybugContext to access.
 * 
 * @return    A LadybugError indicating the success of the function. 
 * 
 * Remarks: 
 *    When this function is called, subsequent calls to 
 *    ladybugConvertImage() will perform a one-shot auto white balance 
 *    adjustment by modifying the relative gain of red and blue channels. 
 *    Because Ladybug cameras do not have full hardware auto white balance 
 *    functionality, white balance adjustment is initially performed in the 
 *    software by analyzing images that are already grabbed and processed on the 
 *    PC. The actual modification of white balance is then performed inside the 
 *    camera. This half-software, half-hardware solution helps ensure better 
 *    image quality over a software-only solution.
 *    Note that calling this function by itself does not adjust white balance. 
 *    Additionally, the application may need to call 
 *    ladybugConvertImage() many times until proper white balance 
 *    adjustment is achieved. You can get the current status of white balance 
 *    adjustment by calling ladybugGetOneShotAutoWhiteBalanceStatus.
 *
 * @see    ladybugGetOneShotAutoWhiteBalanceStatus()
 *
 */
LADYBUGDLL_API LadybugError
ladybugDoOneShotAutoWhiteBalance( 
                     LadybugContext context);

/**
 *    Returns the status of a previously-called instance of 
 *    ladybugDoOneShotAutoWhiteBalance. 
 *
 * @param    context     - The LadybugContext to access.
 * 
 * @return    A LadybugError indicating the success of the function. 
 * 
 * Remarks: 
 *    A return value of LADYBUG_STILL_WORKING indicates white balance
 *    adjustment is ongoing.
 *    A return value of LADYBUG_FAILED indicates white balance adjustment
 *    failed.
 *
 * @see    ladybugDoOneShotAutoWhiteBalance()
 *
 */
LADYBUGDLL_API LadybugError
ladybugGetOneShotAutoWhiteBalanceStatus( 
                     LadybugContext context);

/*@}*/

/*@}*/

#ifdef __cplusplus
};
#endif

#endif // #ifndef __LADYBUG_H__
