#!/bin/bash

mv webrtc/rtc_base webrtc/h265nal_base
find include src webrtc -type f \( -name '*.cc' -o -name '*.h' \) -print0 | xargs -0 sed -i .bak s/rtc_base/h265nal_base/
find webrtc -type f \( -name '*.cc' -o -name '*.h' \) -print0 | xargs -0 sed -i .bak 's/namespace rtc/namespace h265nal_base/'
find webrtc -type f \( -name '*.cc' -o -name '*.h' \) -print0 | xargs -0 sed -i .bak 's/RTC_BASE_/H265NAL_BASE_/'
find webrtc -type f \( -name '*.cc' -o -name '*.h' \) -print0 | xargs -0 sed -i .bak 's/RTC_DISALLOW_/H265NAL_DISALLOW_/'
find include src -type f \( -name '*.cc' -o -name '*.h' \) -print0 | xargs -0 sed -i .bak 's/rtc::/h265nal_base::/g'
find include webrtc src -type f -name '*.bak' -exec rm {} \;
