#ifndef JIJA_WIDGET_HPP
#define JIJA_WIDGET_HPP

#include <list>
#include <vector>
#include "drawable.hpp"
#include "event.hpp"

const uint64_t NO_TEXTURE_ID = UINT64_MAX;
const uint64_t BUTTON_TEXTURE_ID = UINT64_MAX - 1;
const uint64_t TEXT_ID = UINT64_MAX - 2;

class Widget : public Drawable {
    public:

    explicit Widget(SpriteInfo info, Vec2 pos_, Vec2 size_):
        Drawable(info, pos_, size_)
        {}

    virtual bool onMousePress  (const MouseContext mouseContext);
    virtual void onMouseRelease(const MouseContext mouseContext);
    virtual bool onMouseMove   (const MouseContext mouseContext);

    void  pushBackSubWidget(Widget *subWidget);
    void pushFrontSubWidget(Widget *subWidget);

    std::list<Widget*>& getList();
    const std::list<Widget*>& getList() const;
    bool mouseOnWidget (const Vec2& mousepos) const;

    virtual ~Widget();

    virtual ObjType getType() const override {return WIDGET;}
    virtual void load(std::ifstream &stream) {}
    virtual void save(std::ofstream &stream) const {};

    private:

    bool passMousePress  (const MouseContext mouseContext);
    void passMouseRelease(const MouseContext mouseContext);
    bool passMouseMove   (const MouseContext mouseContext);

    std::list<Widget*> subWidgets;
};

class Menu : public Widget {
    public:
    explicit Menu():
        Widget(SpriteInfo(NO_TEXTURE_ID, Vec2(0, 0), Vec2(0, 0)), Vec2(0, 0), Vec2(0, 0)) {}
};

class RootWid : public Menu {
    public:

    explicit RootWid():
        Menu() {}

    void mousePress  (MouseContext context);
    void mouseRelease(MouseContext context);
    void mouseMove   (MouseContext context);
};

class Button : public Widget {
    public:

    Button(Vec2 pos_, Vec2 size_):
        Widget(SpriteInfo(BUTTON_TEXTURE_ID, Vec2(0, 0), Vec2(400, 50)), pos_, size_)
        {}

    bool   onMousePress(const MouseContext mouseContext);
    void onMouseRelease(const MouseContext mouseContext);
    bool    onMouseMove(const MouseContext mouseContext);

    template<typename T>
    void  addPressingHandler(T& obj, void(T::*method)()) { buttonPressed.addHandler(new EventHandler<T>(obj, method)); }

    template<typename T>
    void addReleasingHandler(T& obj, void(T::*method)()) { buttonReleased.addHandler(new EventHandler<T>(obj, method)); }

  private:

    bool isPressed = false;

    Event<> buttonPressed;
    Event<> buttonReleased;
};

class Text : public Widget {
    public: 
    explicit Text(Vec2 pos_, const std::string& txt_, uint8_t char_size_):
        Widget(SpriteInfo(TEXT_ID, Vec2(), Vec2()), pos_, Vec2()),
        txt (txt_),
        char_size (char_size_) {}

    void setTxt(const std::string& str) {
        txt = str;
    }

    void setCharSize(uint8_t sz) {
        char_size = sz;
    }

    const std::string& getTxt() const {
        return txt;
    }

    uint8_t getCharSize() const {
        return char_size;
    }

    private:
    std::string txt;
    uint8_t char_size;
};

#endif