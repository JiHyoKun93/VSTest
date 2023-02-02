#ifndef __EX_LAYOUT_H__
#define __EX_LAYOUT_H__

#include "stdafx.h"

class ExLayout : public Layout {
public:
	bool arg0 = false; 

	static ExLayout* create();
	virtual bool init();

	Widget* addChildButton(Widget* w, const std::function<void(Ref*)>& clickCallback = 0);
};
#endif 