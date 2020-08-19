#pragma once
#ifndef _DATA_H_
#define _DATA_H_
#include "../EventSystem/EventSystem.h"


_declspec(selectany) int score = 0;
_declspec(selectany) Event<int> score_changed;

_declspec(selectany) int player_money = 0;
_declspec(selectany) Event<int> player_money_changed;

#endif