#ifndef __XLANG_H__
#define __XLANG_H__

#include "stdafx.h"

void setCurrentLanguage(char* lang);
const char* getCurrentLanguage();
std::string getString(const char* key);
#endif