#include "../include/widget.hpp"

bool Widget::onMousePress(const MouseContext mouseContext) {
    return passMousePress(mouseContext);
}

void Widget::onMouseRelease(const MouseContext mouseContext) {
    passMouseRelease(mouseContext);
}

bool Widget::onMouseMove(const MouseContext mouseContext) {
    return passMouseMove(mouseContext);
}


void Widget::pushBackSubWidget(Widget *subWidget) {
    subWidgets.push_back (subWidget);
}

void Widget::pushFrontSubWidget(Widget *subWidget) {
    subWidgets.push_front(subWidget);
}

std::list<Widget*>& Widget::getList() {
    return subWidgets;
}


const std::list<Widget*>& Widget::getList() const {
    return subWidgets;
}

bool Widget::mouseOnWidget (const Vec2& mousepos) const {
    return getRect().contains(mousepos);
}


bool Widget::passMousePress(const MouseContext mouseContext) {
    for (auto subwid : subWidgets) {
        if (subwid -> onMousePress(mouseContext)) return true;
    }
    return false;
};

void Widget::passMouseRelease(const MouseContext mouseContext) {
    for (auto subwid : subWidgets) {
        subwid -> onMouseRelease(mouseContext);
    }
};

bool Widget::passMouseMove(const MouseContext mouseContext) {
    for (auto subwid : subWidgets) {
        if (subwid -> onMouseMove(mouseContext)) return true;
    }
    return false;
};

Widget::~Widget() {
    for (auto subwid : subWidgets) delete subwid;
}


void RootWid::mousePress(MouseContext context) {
    for (auto subwid : getList()) {
        if (subwid -> onMousePress(context)) return;
    }
}

void RootWid::mouseRelease(MouseContext context) {
    for (auto subwid : getList()) {
        subwid -> onMouseRelease(context);
    }
}

void RootWid::mouseMove(MouseContext context) {
    for (auto subwid : getList()) {
        if (subwid -> onMouseMove(context)) return;
    }
}


bool Button::onMousePress(const MouseContext mouseContext) {
    if (!mouseOnWidget(mouseContext.position)) return false;
    if (mouseContext.button != MouseButton::Left) return false;

    setFrame(Vec2(0, 1));
    isPressed = true;

    buttonPressed();
    return true;
}

void Button::onMouseRelease(const MouseContext mouseContext) {
    if (!isPressed) return;

    setFrame(Vec2(0, 0));
    isPressed = false;

    buttonReleased();
}

bool Button::onMouseMove(const MouseContext mouseContext) {
    if (mouseOnWidget(mouseContext.position)) return true;
    else return false;
}