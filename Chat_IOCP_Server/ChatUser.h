#pragma once
#include "NetUser.h"
class AChatUser : public ANetUser , public AObjectPool<AChatUser>
{
};

