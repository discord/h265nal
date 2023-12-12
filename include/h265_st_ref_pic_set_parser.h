/*
 *  Copyright (c) Facebook, Inc. and its affiliates.
 */

#pragma once

#include <stdio.h>

#include <memory>
#include <vector>

#include "h265nal_base/bit_buffer.h"

namespace h265nal {

// A class for parsing out a Short-term reference picture set syntax
// (`st_ref_pic_set()`, as defined in Section 7.3.7 of the 2016-12
// standard) from an H265 NALU.
class H265StRefPicSetParser {
 public:
  // Section 7.4.8: "The value of delta_idx_minus1 shall be in the range
  // of 0 to stRpsIdx - 1, inclusive."
  const static uint32_t kDeltaIdxMinus1Min = 0;
  // Section 7.4.8: "The value of abs_delta_rps_minus1 shall be in the range
  // of 0 to 2^15 - 1, inclusive."
  const static uint32_t kAbsDeltaRpsMinus1Min = 0;
  const static uint32_t kAbsDeltaRpsMinus1Max = 32767;
  // Section 7.4.8: "When nuh_layer_id of the current picture is equal to 0,
  // the value of num_negative_pics shall be in the range of 0 to
  // sps_max_dec_pic_buffering_minus1[sps_max_sub_layers_minus1],
  // inclusive."
  const static uint32_t kNumNegativePicsMin = 0;
  // Section 7.4.8: "When nuh_layer_id of the current picture is equal to 0,
  // the value of num_positive_pics shall be in the range of 0 to
  // sps_max_dec_pic_buffering_minus1[sps_max_sub_layers_minus1] -
  // num_negative_pics, inclusive."
  const static uint32_t kNumPositivePicsMin = 0;

  // The parsed state of the StRefPicSet.
  struct StRefPicSetState {
    StRefPicSetState() = default;
    ~StRefPicSetState() = default;
    // disable copy ctor, move ctor, and copy&move assignments
    StRefPicSetState(const StRefPicSetState&) = delete;
    StRefPicSetState(StRefPicSetState&&) = delete;
    StRefPicSetState& operator=(const StRefPicSetState&) = delete;
    StRefPicSetState& operator=(StRefPicSetState&&) = delete;

#ifdef FDUMP_DEFINE
    void fdump(FILE* outfp, int indent_level) const;
#endif  // FDUMP_DEFINE

    // input parameters
    uint32_t stRpsIdx = 0;
    uint32_t num_short_term_ref_pic_sets = 0;

    // contents
    uint32_t inter_ref_pic_set_prediction_flag = 0;
    uint32_t delta_idx_minus1 = 0;
    uint32_t delta_rps_sign = 0;
    uint32_t abs_delta_rps_minus1 = 0;
    std::vector<uint32_t> used_by_curr_pic_flag;
    std::vector<uint32_t> use_delta_flag;
    uint32_t num_negative_pics = 0;
    uint32_t num_positive_pics = 0;
    std::vector<uint32_t> delta_poc_s0_minus1;
    std::vector<uint32_t> used_by_curr_pic_s0_flag;
    std::vector<uint32_t> delta_poc_s1_minus1;
    std::vector<uint32_t> used_by_curr_pic_s1_flag;

    // helper functions
    void DeriveValues(
        const std::vector<std::unique_ptr<struct StRefPicSetState>>*
            st_ref_pic_set_state_vector,
        const uint32_t RefRpsIdx) noexcept;
  };

  // Unpack RBSP and parse StRefPicSet state from the supplied buffer.
  static std::unique_ptr<StRefPicSetState> ParseStRefPicSet(
      const uint8_t* data, size_t length, uint32_t stRpsIdx,
      uint32_t num_short_term_ref_pic_sets,
      const std::vector<std::unique_ptr<struct StRefPicSetState>>*
          st_ref_pic_set_state_vector,
      uint32_t max_num_pics) noexcept;
  static std::unique_ptr<StRefPicSetState> ParseStRefPicSet(
      h265nal_base::BitBuffer* bit_buffer, uint32_t stRpsIdx,
      uint32_t num_short_term_ref_pic_sets,
      const std::vector<std::unique_ptr<struct StRefPicSetState>>*
          st_ref_pic_set_state_vector,
      uint32_t max_num_pics) noexcept;
};

}  // namespace h265nal
