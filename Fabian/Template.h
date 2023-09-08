#pragma once
#include "pch.h"

template<typename TRet, typename ...TParams>
using TCallbackFunc = function<TRet(TParams...)>;