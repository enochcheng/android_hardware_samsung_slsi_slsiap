#include <linux/videodev2.h>
#include <nxp-v4l2.h>
#include "SP2518.h"

enum {
    WB_INCANDESCENT = 0,
    WB_FLUORESCENT,
    WB_DAYLIGHT,
    WB_CLOUDY,
    WB_TUNGSTEN,
    WB_AUTO,
    WB_MAX
};

enum {
    COLORFX_NONE = 0,
    COLORFX_MONO,
    COLORFX_SEPIA,
    COLORFX_NEGATIVE,
    COLORFX_MAX
};

#define MIN_EXPOSURE     -3
#define MAX_EXPOSURE     3

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

namespace android {

const int32_t ResolutionSP2518[] = {
    1600, 1200,
    1280, 720,
    800, 600,
    704, 480,
    720, 480,
    640, 480
#if 0
    352, 288,
    320, 240,
    176, 144
#endif
};

// TOP/system/media/camera/include/system/camera_metadata_tags.h
static const uint8_t AvailableAfModesSP2518[] = {
    ANDROID_CONTROL_AF_MODE_OFF,
    ANDROID_CONTROL_AF_MODE_AUTO,
    ANDROID_CONTROL_AF_MODE_MACRO,
    ANDROID_CONTROL_AF_MODE_CONTINUOUS_PICTURE,
    ANDROID_CONTROL_AF_MODE_CONTINUOUS_VIDEO
};

static const uint8_t AvailableAeModesSP2518[] = {
    ANDROID_CONTROL_AE_MODE_OFF,
    ANDROID_CONTROL_AE_MODE_ON,
    ANDROID_CONTROL_AE_MODE_ON_AUTO_FLASH
};

static const uint8_t SceneModeOverridesSP2518[] = {
    // ANDROID_CONTROL_SCENE_MODE_PORTRAIT
    ANDROID_CONTROL_AE_MODE_ON,
    ANDROID_CONTROL_AWB_MODE_AUTO,
    ANDROID_CONTROL_AF_MODE_CONTINUOUS_PICTURE,
    // ANDROID_CONTROL_SCENE_MODE_LANDSCAPE
    ANDROID_CONTROL_AE_MODE_ON,
    ANDROID_CONTROL_AWB_MODE_AUTO,
    ANDROID_CONTROL_AF_MODE_CONTINUOUS_PICTURE,
    // ANDROID_CONTROL_SCENE_MODE_SPORTS
    ANDROID_CONTROL_AE_MODE_ON,
    ANDROID_CONTROL_AWB_MODE_DAYLIGHT,
    ANDROID_CONTROL_AF_MODE_CONTINUOUS_PICTURE,
#if 0
    // ANDROID_CONTROL_SCENE_MODE_NIGHT
    ANDROID_CONTROL_AE_MODE_ON_AUTO_FLASH,
    ANDROID_CONTROL_AWB_MODE_AUTO,
    ANDROID_CONTROL_AF_MODE_CONTINUOUS_PICTURE
#endif
};

static const uint8_t AvailableEffectsSP2518[] = {
    ANDROID_CONTROL_EFFECT_MODE_MONO,
    ANDROID_CONTROL_EFFECT_MODE_NEGATIVE,
    ANDROID_CONTROL_EFFECT_MODE_SEPIA,
    ANDROID_CONTROL_EFFECT_MODE_AQUA
};

static const uint8_t AvailableSceneModesSP2518[] = {
    ANDROID_CONTROL_SCENE_MODE_PORTRAIT,
    ANDROID_CONTROL_SCENE_MODE_LANDSCAPE,
    ANDROID_CONTROL_SCENE_MODE_SPORTS,
#if 0
    ANDROID_CONTROL_SCENE_MODE_NIGHT
#endif
};

static const uint32_t ExposureCompensationRangeSP2518[] = {
     MIN_EXPOSURE, MAX_EXPOSURE
};

static const uint8_t AvailableAntibandingModesSP2518[] = {
    ANDROID_CONTROL_AE_ANTIBANDING_MODE_OFF,
    ANDROID_CONTROL_AE_ANTIBANDING_MODE_50HZ,
    ANDROID_CONTROL_AE_ANTIBANDING_MODE_60HZ
};

static const uint8_t AvailableAwbModesSP2518[] = {
    ANDROID_CONTROL_AWB_MODE_OFF,
    ANDROID_CONTROL_AWB_MODE_AUTO,
    ANDROID_CONTROL_AWB_MODE_DAYLIGHT,
    ANDROID_CONTROL_AWB_MODE_CLOUDY_DAYLIGHT,
    ANDROID_CONTROL_AWB_MODE_FLUORESCENT,
    ANDROID_CONTROL_AWB_MODE_INCANDESCENT
};

static const int32_t AvailableFpsRangesSP2518[] = {
    8, 15
    //8, 15, 30
    //15, 30
    //8, 8, 15, 15, 24, 24, 15, 30
};

void SP2518::init()
{
    // TODO
    Width = ResolutionSP2518[0];
    Height = ResolutionSP2518[1];
    NumResolutions = ARRAY_SIZE(ResolutionSP2518)/2;
    Resolutions = ResolutionSP2518;
    NumAvailableAfModes = ARRAY_SIZE(AvailableAfModesSP2518);
    AvailableAfModes = AvailableAfModesSP2518;
    NumAvailableAeModes = ARRAY_SIZE(AvailableAeModesSP2518);
    AvailableAeModes = AvailableAeModesSP2518;
    NumSceneModeOverrides = ARRAY_SIZE(SceneModeOverridesSP2518);
    SceneModeOverrides = SceneModeOverridesSP2518;
    ExposureCompensationRange = ExposureCompensationRangeSP2518;
    AvailableAntibandingModes = AvailableAntibandingModesSP2518;
    NumAvailAntibandingModes = ARRAY_SIZE(AvailableAntibandingModesSP2518);
    AvailableAwbModes = AvailableAwbModesSP2518;
    NumAvailAwbModes = ARRAY_SIZE(AvailableAwbModesSP2518);
    AvailableEffects = AvailableEffectsSP2518;
    NumAvailEffects = ARRAY_SIZE(AvailableEffectsSP2518);
    AvailableSceneModes = AvailableSceneModesSP2518;
    NumAvailSceneModes = ARRAY_SIZE(AvailableSceneModesSP2518);
    AvailableFpsRanges = AvailableFpsRangesSP2518;
    NumAvailableFpsRanges = ARRAY_SIZE(AvailableFpsRangesSP2518);

    // TODO
    FocalLength = 3.43f;
    Aperture = 2.7f;
    MinFocusDistance = 0.1f;
    FNumber = 2.7f;

    // TODO
    //MaxFaceCount = 16;
    MaxFaceCount = 1;

    // Crop
    CropWidth = Width;
    CropHeight = Height;
    CropLeft = 0;
    CropTop = 0;
}

SP2518::SP2518()
{
    init();
}

SP2518::SP2518(uint32_t v4l2ID)
    : NXCameraBoardSensor(v4l2ID)
{
    init();
}

SP2518::~SP2518()
{
}

void SP2518::setAfMode(uint8_t afMode)
{
    AfMode = afMode;
}

void SP2518::afEnable(bool enable)
{
}

void SP2518::setEffectMode(uint8_t effectMode)
{
    if (effectMode != EffectMode) {
        uint32_t val = 0;

        switch (effectMode) {
        case ANDROID_CONTROL_EFFECT_MODE_OFF:
            val = COLORFX_NONE;
            break;
        case ANDROID_CONTROL_EFFECT_MODE_MONO:
            val = COLORFX_MONO;
            break;
        case ANDROID_CONTROL_EFFECT_MODE_NEGATIVE:
            val = COLORFX_NEGATIVE;
            break;
        case ANDROID_CONTROL_EFFECT_MODE_SEPIA:
            val = COLORFX_SEPIA;
            break;
        default:
            //ALOGE("%s: unsupported effectmode 0x%x", __func__, effectMode);
            return;
        }

        v4l2_set_ctrl(V4l2ID, V4L2_CID_COLORFX, val);
        EffectMode = effectMode;
    }
}

void SP2518::setSceneMode(uint8_t sceneMode)
{
}

void SP2518::setAntibandingMode(uint8_t antibandingMode)
{
}

void SP2518::setAwbMode(uint8_t awbMode)
{
    if (awbMode != AwbMode) {
        uint32_t val = 0;

        switch (awbMode) {
        case ANDROID_CONTROL_AWB_MODE_OFF:
            v4l2_set_ctrl(V4l2ID, V4L2_CID_AUTO_WHITE_BALANCE, 0);
            return;
        case ANDROID_CONTROL_AWB_MODE_AUTO:
            v4l2_set_ctrl(V4l2ID, V4L2_CID_AUTO_WHITE_BALANCE, 1);
            return;
        case ANDROID_CONTROL_AWB_MODE_DAYLIGHT:
            val = WB_DAYLIGHT;
            break;
        case ANDROID_CONTROL_AWB_MODE_CLOUDY_DAYLIGHT:
            val = WB_DAYLIGHT;
            break;
        case ANDROID_CONTROL_AWB_MODE_FLUORESCENT:
            val = WB_FLUORESCENT;
            break;
        case ANDROID_CONTROL_AWB_MODE_INCANDESCENT:
            val = WB_INCANDESCENT;
            break;
        default:
            //ALOGE("%s: unsupported awb mode 0x%x", __func__, awbMode);
            return;
        }
        AwbMode = awbMode;

        v4l2_set_ctrl(V4l2ID, V4L2_CID_WHITE_BALANCE_TEMPERATURE, val);
    }
}

void SP2518::setExposure(int32_t exposure)
{
    if (exposure < MIN_EXPOSURE || exposure > MAX_EXPOSURE) {
        ALOGE("%s: invalid exposure %d", __func__, exposure);
        return;
    }

    if (exposure != Exposure) {
        Exposure = exposure;
        v4l2_set_ctrl(V4l2ID, V4L2_CID_BRIGHTNESS, exposure + 3);
    }
}

uint32_t SP2518::getZoomFactor(void)
{
    // disable zoom
    return 1;
}

status_t SP2518::setZoomCrop(uint32_t left, uint32_t top, uint32_t width, uint32_t height)
{
    return NO_ERROR;
}

}; // namespace
