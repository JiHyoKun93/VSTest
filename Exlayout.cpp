#include "stdafx.h"
#include "Exlayout.h"

ExLayout* ExLayout::create(){
	auto ret = new ExLayout();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool ExLayout::init() {
	if (!Layout::init()) return false;

	return true;
}

Widget* ExLayout::addChildButton(Widget* w, const std::function<void(Ref*)>& clickCallback) {
	this->addChild(w);
	w->addClickEventListener(clickCallback);
	return w;
}
