#pragma once

#include "ffmpegHeaders.h"
#include "davImpl.h"
#include "scaleFilter.h"

namespace ff_dynamic {

class FFmpegVideoEncode : public DavImpl {
public:
    FFmpegVideoEncode(const DavWaveOption & options) : DavImpl(options) {
        implDefaultInstantiate();
    }
    virtual ~FFmpegVideoEncode() {onDestruct();}

private: /* data process */
    FFmpegVideoEncode(const FFmpegVideoEncode &) = delete;
    FFmpegVideoEncode & operator= (const FFmpegVideoEncode &) = delete;
    virtual int onConstruct();
    virtual int onDestruct();
    virtual int onProcess(DavProcCtx & ctx);
    virtual int onDynamicallyInitializeViaTravelStatic(DavProcCtx & ctx);
    virtual int onProcessTravelDynamic(DavProcCtx & ctx) {return 0;}
    int dynamicallyInitialize(const DavImplTravel::TravelStatic & in);
    int setupScaleFilter(const DavImplTravel::TravelStatic & in, const DavImplTravel::TravelStatic & out);
    int receiveEncodeFrames(DavProcCtx & ctx);

private: /* event process */
    // int keyFrameRequest(const KeyFrameRequestEvent & event);

private:
    AVCodecContext *m_encCtx = nullptr;
    ScaleFilter *m_scaleFilter = nullptr;
    ScaleFilterParams m_sfp;
    uint64_t m_discardFrames = 0;
    bool m_bForcedKeyFrame = false;
};

} //namespace ff_dynamic
