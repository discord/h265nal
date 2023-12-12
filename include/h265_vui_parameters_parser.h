/*
 *  Copyright (c) Facebook, Inc. and its affiliates.
 */

#pragma once

#include <stdio.h>

#include <memory>

#include "h265_hrd_parameters_parser.h"
#include "h265nal_base/bit_buffer.h"

namespace h265nal {

enum AspectRatioType : uint8_t {
  AR_UNSPECIFIED = 0,
  AR_1_1 = 1,      // 1:1 ("square")
  AR_12_11 = 2,    // 12:11
  AR_10_11 = 3,    // 10:11
  AR_16_11 = 4,    // 16:11
  AR_40_33 = 5,    // 40:33
  AR_24_11 = 6,    // 24:11
  AR_20_11 = 7,    // 20:11
  AR_32_11 = 8,    // 32:11
  AR_80_33 = 9,    // 80:33
  AR_18_11 = 10,   // 18:11
  AR_15_11 = 11,   // 15:11
  AR_64_33 = 12,   // 64:33
  AR_160_99 = 13,  // 160:99
  AR_4_3 = 14,     // 4:3
  AR_3_2 = 15,     // 3:2
  AR_2_1 = 16,     // 2:1
  // 17..254: Reserved
  AR_EXTENDED_SAR = 255  // Extended_SAR
};

// A class for parsing out a SPS VUI data from an H265 NALU.
class H265VuiParametersParser {
 public:
  // Section E.3.1: "The value of chroma_sample_loc_type_top_field [...]
  // shall be in the range of 0 to 5, inclusive."
  const static uint32_t kChromaSampleLocTypeTopFieldMin = 0;
  const static uint32_t kChromaSampleLocTypeTopFieldMax = 5;
  // Section E.3.1: "The value of [...] chroma_sample_loc_type_bottom_field
  // shall be in the range of 0 to 5, inclusive."
  const static uint32_t kChromaSampleLocTypeBottomFieldMin = 0;
  const static uint32_t kChromaSampleLocTypeBottomFieldMax = 5;
  // from ffmpeg
  const static uint32_t kDefDispWinLeftOffsetMin = 0;
  const static uint32_t kDefDispWinLeftOffsetMax = 16384;
  // from ffmpeg
  const static uint32_t kDefDispWinRightOffsetMin = 0;
  const static uint32_t kDefDispWinRightOffsetMax = 16384;
  // from ffmpeg
  const static uint32_t kDefDispWinTopOffsetMin = 0;
  const static uint32_t kDefDispWinTopOffsetMax = 16384;
  // from ffmpeg
  const static uint32_t kDefDispWinBottomOffsetMin = 0;
  const static uint32_t kDefDispWinBottomOffsetMax = 16384;
  // Section E.3.1: "The value of vui_num_ticks_poc_diff_one_minus1 shall be
  // in the range of 0 to 2^32 - 2, inclusive.
  const static uint32_t kVuiNumTicksPocDiffOneMinus1Min = 0;
  const static uint32_t kVuiNumTicksPocDiffOneMinus1Max = UINT32_MAX - 1;
  // Section E.3.1: "The value of min_spatial_segmentation_idc shall be in
  // the range of 0 to 4095, inclusive."
  const static uint32_t kMinSpatialSegmentationIdcMin = 0;
  const static uint32_t kMinSpatialSegmentationIdcMax = 4095;
  // Section E.3.1: "The value of max_bytes_per_pic_denom shall be in the
  // range of 0 to 16, inclusive."
  const static uint32_t kMaxBytesPerPicDenomMin = 0;
  const static uint32_t kMaxBytesPerPicDenomMax = 16;
  // Section E.3.1: "The value of max_bits_per_min_cu_denom shall be in the
  // range of 0 to 16, inclusive."
  const static uint32_t kMaxBitsPerMinCuDenomMin = 0;
  const static uint32_t kMaxBitsPerMinCuDenomMax = 16;
  // Section E.3.1: "The values of log2_max_mv_length_horizontal [...] shall
  // be in the range of 0 to 15, inclusive.
  const static uint32_t kLog2MaxMvLengthHorizontalMin = 0;
  const static uint32_t kLog2MaxMvLengthHorizontalMax = 15;
  // Section E.3.1: "The values of [...] log2_max_mv_length_vertical shall
  // be in the range of 0 to 15, inclusive.
  const static uint32_t kLog2MaxMvLengthVerticalMin = 0;
  const static uint32_t kLog2MaxMvLengthVerticalMax = 15;

  // The parsed state of the SPS VUI. Only some select values are stored.
  // Add more as they are actually needed.
  struct VuiParametersState {
    VuiParametersState() = default;
    ~VuiParametersState() = default;
    // disable copy ctor, move ctor, and copy&move assignments
    VuiParametersState(const VuiParametersState&) = delete;
    VuiParametersState(VuiParametersState&&) = delete;
    VuiParametersState& operator=(const VuiParametersState&) = delete;
    VuiParametersState& operator=(VuiParametersState&&) = delete;

#ifdef FDUMP_DEFINE
    void fdump(FILE* outfp, int indent_level) const;
#endif  // FDUMP_DEFINE

    // input
    uint32_t sps_max_sub_layers_minus1 = 0;

    // content
    uint32_t aspect_ratio_info_present_flag = 0;
    uint32_t aspect_ratio_idc = 0;
    uint32_t sar_width = 0;
    uint32_t sar_height = 0;
    uint32_t overscan_info_present_flag = 0;
    uint32_t overscan_appropriate_flag = 0;
    uint32_t video_signal_type_present_flag = 0;
    uint32_t video_format = 0;
    uint32_t video_full_range_flag = 0;
    uint32_t colour_description_present_flag = 0;
    uint32_t colour_primaries = 0;
    uint32_t transfer_characteristics = 0;
    uint32_t matrix_coeffs = 0;
    uint32_t chroma_loc_info_present_flag = 0;
    uint32_t chroma_sample_loc_type_top_field = 0;
    uint32_t chroma_sample_loc_type_bottom_field = 0;
    uint32_t neutral_chroma_indication_flag = 0;
    uint32_t field_seq_flag = 0;
    uint32_t frame_field_info_present_flag = 0;
    uint32_t default_display_window_flag = 0;
    uint32_t def_disp_win_left_offset = 0;
    uint32_t def_disp_win_right_offset = 0;
    uint32_t def_disp_win_top_offset = 0;
    uint32_t def_disp_win_bottom_offset = 0;
    uint32_t vui_timing_info_present_flag = 0;
    uint32_t vui_num_units_in_tick = 0;
    uint32_t vui_time_scale = 0;
    uint32_t vui_poc_proportional_to_timing_flag = 0;
    uint32_t vui_num_ticks_poc_diff_one_minus1 = 0;
    uint32_t vui_hrd_parameters_present_flag = 0;
    std::unique_ptr<struct H265HrdParametersParser::HrdParametersState>
        hrd_parameters;
    uint32_t bitstream_restriction_flag = 0;
    uint32_t tiles_fixed_structure_flag = 0;
    uint32_t motion_vectors_over_pic_boundaries_flag = 0;
    uint32_t restricted_ref_pic_lists_flag = 0;
    uint32_t min_spatial_segmentation_idc = 0;
    uint32_t max_bytes_per_pic_denom = 0;
    uint32_t max_bits_per_min_cu_denom = 0;
    uint32_t log2_max_mv_length_horizontal = 0;
    uint32_t log2_max_mv_length_vertical = 0;

    // derived values
    float getFramerate() const noexcept;
  };

  // Unpack RBSP and parse VIU Parameters state from the supplied buffer.
  static std::unique_ptr<VuiParametersState> ParseVuiParameters(
      const uint8_t* data, size_t length,
      uint32_t sps_max_sub_layers_minus1) noexcept;
  static std::unique_ptr<VuiParametersState> ParseVuiParameters(
      h265nal_base::BitBuffer* bit_buffer, uint32_t sps_max_sub_layers_minus1) noexcept;
};

}  // namespace h265nal
