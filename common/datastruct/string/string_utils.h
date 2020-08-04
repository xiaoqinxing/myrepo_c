/*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*******************************************************************************/

#ifndef MMCAM_LOG_UTILS_H
#define MMCAM_LOG_UTILS_H

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "logprint.h"

namespace mmcam_utils
{

#undef MMCAM_LOGE
#undef MMCAM_LOGW
#undef MMCAM_LOGI
#undef MMCAM_LOGV
#undef MMCAM_LOGB
#undef MMCAM_ASSERT
#undef MMCAM_ASSERT_FAILED
#undef MMCAM_ASSERT_PRE
#undef MMCAM_ASSERT_POST
#undef MMCAM_ASSERT_INVARIANT

void PrintByteStream(const char *str, size_t size, const char *comment);

class string
{
private:
    string(string const &); // prevent accidental copy
    string& operator=(const string&); // prevent assignment
    string();

public:
    string(const char* str);
    string(int32_t capacity);
    ~string();
    size_t length() const;
    size_t size() const;
    size_t capacity() const;
    const char* data() const;
    char& operator[] (size_t pos);

    void clear();

    string& append(const string& str);
    string& append(const char* str, size_t len);
    string& append(size_t len, char val);

    string& assign(const string& str);
    string& assign(const char* str, size_t len);

    string& replace(size_t pos, size_t len, const string& str);
    string& replace(size_t pos, size_t len, const char *str);

protected:
    char       *buf;
    size_t      buf_len;     // current string length
    size_t      buf_capacity; // total buf capacity

};

};

#endif // MMCAM_LOG_UTILS_H
