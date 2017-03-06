/******************************************************************************
* Copyright (C) 2017, Divideon. All rights reserved.
* No part of this code may be reproduced in any form
* without the written permission of the copyright holder.
******************************************************************************/

#ifndef XVC_DEC_LIB_XVCDEC_H_
#define XVC_DEC_LIB_XVCDEC_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

  enum xvc_dec_return_code {
    XVC_DEC_OK = 0,
    XVC_DEC_NO_DECODED_PIC,
    XVC_DEC_NOT_CONFORMING,
    XVC_DEC_INVALID_ARGUMENT,
    XVC_DEC_FRAMERATE_OUT_OF_RANGE,
    XVC_DEC_BITDEPTH_OUT_OF_RANGE,
    XVC_DEC_BITSTREAM_VERSION_HIGHER_THAN_DECODER,
    XVC_DEC_NO_SEGMENT_HEADER_DECODED,
    XVC_DEC_BITSTREAM_BITDEPTH_TOO_HIGH,
    XVC_DEC_INVALID_PARAMETER,
  };

  enum xvc_dec_chroma_format {
    // Using naming and IDs from FOURCC
    XVC_DEC_CHROMA_FORMAT_MONOCHROME = 0,
    XVC_DEC_CHROMA_FORMAT_420 = 1,
    XVC_DEC_CHROMA_FORMAT_422 = 2,
    XVC_DEC_CHROMA_FORMAT_444 = 3,
    XVC_DEC_CHROMA_FORMAT_UNDEFINED = 255,
  };

  typedef struct xvc_dec_pic_stats {
    uint32_t nal_unit_type;
    uint32_t poc;
    uint32_t doc;
    uint32_t soc;
    uint32_t tid;
    int32_t l0[5];
    int32_t l1[5];
    int32_t bitdepth;
    int32_t bitstream_bitdepth;
    int32_t width;
    int32_t height;
    int32_t qp;
    xvc_dec_chroma_format chroma_format;
    double framerate;
    double bitstream_framerate;
  } xvc_dec_pic_stats;

  typedef struct xvc_decoded_picture {
    char* bytes;
    size_t size;
    xvc_dec_pic_stats stats;
  } xvc_decoded_picture;

  typedef struct xvc_decoder xvc_decoder;

  typedef struct xvc_decoder_parameters {
    int output_width;
    int output_height;
    xvc_dec_chroma_format output_chroma_format;
    int output_bitdepth;
    double max_framerate;
  } xvc_decoder_parameters;

  typedef struct xvc_decoder_api {
    xvc_decoder_parameters* (*parameters_create)();
    xvc_dec_return_code(*parameters_destroy)(
      xvc_decoder_parameters *param_api);
    xvc_dec_return_code(*parameters_set_default)(
      xvc_decoder_parameters *param_api);
    xvc_dec_return_code(*parameters_check)(xvc_decoder_parameters *param_api);

    xvc_decoder* (*decoder_create)(xvc_decoder_parameters *decoder_api);
    xvc_dec_return_code(*decoder_destroy)(xvc_decoder *decoder_api);
    xvc_dec_return_code(*decoder_decode_nal)(xvc_decoder *decoder_api,
                                             uint8_t *nal_unit,
                                             size_t nal_unit_size);
    xvc_dec_return_code(*decoder_get_picture)(xvc_decoder *decoder_api,
                                              xvc_decoded_picture *pic_bytes);
    xvc_dec_return_code(*decoder_flush)(xvc_decoder *decoder_api,
                                        xvc_decoded_picture *pic_bytes);
    xvc_dec_return_code(*decoder_check_conformance)(xvc_decoder *decoder_api,
                                            int *num);
  } xvc_decoder_api;


  const xvc_decoder_api* xvc_decoder_api_get();

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // XVC_DEC_LIB_XVCDEC_H_

