#ifndef JIJA_GUI_HPP
#define JIJA_GUI_HPP

#include "background.hpp"
#include "widget.hpp"

const uint64_t GUI_BG_TEXTURE_ID = UINT64_MAX - 2;

class Gui {
    public:
    explicit Gui(EventManager& global_event_man, unsigned int w, unsigned int h);

    EventManager& getEventMan();
    RootWid& getRoot();
    const RootWid& getRoot() const;
    const Background& getBg() const;

    private:
    Background bg;
    EventManager event_man;
    RootWid root;
};


#endif