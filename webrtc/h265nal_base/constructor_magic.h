/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef H265NAL_BASE_CONSTRUCTOR_MAGIC_H_
#define H265NAL_BASE_CONSTRUCTOR_MAGIC_H_

// Put this in the declarations for a class to be unassignable.
#define H265NAL_DISALLOW_ASSIGN(TypeName) \
  TypeName& operator=(const TypeName&) = delete

// A macro to disallow the copy constructor and operator= functions. This should
// be used in the declarations for a class.
#define H265NAL_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;          \
  H265NAL_DISALLOW_ASSIGN(TypeName)

// A macro to disallow all the implicit constructors, namely the default
// constructor, copy constructor and operator= functions.
//
// This should be used in the declarations for a class that wants to prevent
// anyone from instantiating it. This is especially useful for classes
// containing only static methods.
#define H265NAL_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName() = delete;                               \
  H265NAL_DISALLOW_COPY_AND_ASSIGN(TypeName)

#endif  // H265NAL_BASE_CONSTRUCTOR_MAGIC_H_
