#include "../include/gui.hpp"


Gui::Gui(EventManager& global_event_man, unsigned int w, unsigned int h):
    bg (GUI_BG_TEXTURE_ID, Vec2(w, h))
    {
        global_event_man.addSubManager(event_man);
        event_man.CreateMousePressHandler  (root, &RootWid::mousePress  );
        event_man.CreateMouseReleaseHandler(root, &RootWid::mouseRelease);
        event_man.CreateMouseMoveHandler   (root, &RootWid::mouseMove   );
    }

EventManager& Gui::getEventMan() {
    return event_man;
}

const RootWid& Gui::getRoot() const {
    return root;
}

RootWid& Gui::getRoot() {
    return root;
}

const Background& Gui::getBg() const {
    return bg;
}