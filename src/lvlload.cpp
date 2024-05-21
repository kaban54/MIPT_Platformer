#include <fstream>
#include <string>
#include "../include/DSL.hpp"
#include "../include/graphics.hpp"
#include "../include/level.hpp"
#include "../include/load.hpp"

const std::string SIGNATURE = "JIJALVL_VER4";

Camera readCam(std::ifstream &stream);
Background readBackground(std::ifstream &stream, SpriteManager& sprite_man);

// static Player* parsePlayer(EventManager& ev_man, std::vector<std::string>& table, std::ifstream &stream);

void Level::load(const std::string& filename, const ObjectManager& obj_man, SpriteManager& sprite_man) {
    std::ifstream inStream(filename);

    std::string curString;
    std::string signature;

    inStream >> signature;
    if (signature != SIGNATURE) {
        MESSAGE("SIGNATURE ERROR at (%s)", filename.c_str());
        abort();
    }
    MSG("SIGNATURE: PASSED, SUKA")

    inStream >> curString;
    if ("Name:" != curString) {
        MESSAGE("Syntax ERROR at (%s)", filename.c_str());
        abort();
    }
    lvl_name = readString(inStream);
    MSG("NAME: PASSED, SUKA")

    inStream >> curString;
    if ("Background:" != curString) {
        MESSAGE("Syntax ERROR at (%s)", filename.c_str());
        abort();
    }
    bg = readBackground(inStream, sprite_man);
    MSG("BACKGROUND: PASSED, SUKA")

    inStream >> curString;
    if ("Gravity:" != curString) {
        MESSAGE("Syntax ERROR at (%s)", filename.c_str());
        abort();
    }
    grav_acc = readVec(inStream);
    MSG("GRAVITY: PASSED, SUKA")

    inStream >> curString;
    if ("Bounds:" != curString) {
        MESSAGE("Syntax ERROR at (%s)", filename.c_str());
        abort();
    }
    bounds = readRect(inStream);
    MSG("BOUNDS: PASSED, SUKA")

    inStream >> curString;
    if ("Camera:" != curString) {
        MESSAGE("Syntax ERROR at (%s)", filename.c_str());
        abort();
    }
    cam = readCam(inStream);
    MSG("CAMERA: PASSED, SUKA")

    inStream >> curString;
    if ("Player:" != curString) {
        MESSAGE("Syntax ERROR at (%s)", filename.c_str());
        abort();
    }
    // Player* newPlayer = parsePlayer(event_man, texture_name_table, inStream);
    // entities.push_back(newPlayer);
    // drawable.push_back(newPlayer);
    // cam.target = newPlayer;
    // MSG("PLAYER: PASSED, SUKA")

    inStream >> curString;
    if (curString != "Objects:") {
        MESSAGE("Syntax ERROR at (%s)", filename.c_str());
        abort();
    }
    parskip(inStream);
    if (inStream.peek() != '{') {
        MESSAGE("Syntax ERROR at (%s)", filename.c_str());
        abort();
    }

    parskip(inStream);
    while (inStream.peek() != '}') {
        std::string obj_name;
        inStream >> obj_name;
        if (!obj_man.contains(curString)) {
            MESSAGE("Unknown object (\"%s\")", obj_name.c_str());
            abort();
        }
        ObjInfo obj_info = obj_man.getInfo(obj_name);
        Drawable* obj = obj_info.create_obj_f();
        parskip(inStream);
        obj -> load(inStream);
        parskip(inStream);

        uint64_t id = sprite_man.getSize();
        obj -> setTextureID(id);
        sprite_man.loadTexture(id, obj_info.texture_file_name);
    }
    MESSAGE("LEVEL(%s) LOADED SUCESSFULLY!", filename.c_str());
}



// static Player* parsePlayer(EventManager& ev_man, std::vector<std::string>& table, std::ifstream &stream) {
//     CHECK_DELIM('{')
//         Vec2 pos = readVec(stream);
//         CHECK_DELIM(',')

//         double side = readNum(stream);
//         CHECK_DELIM(',')

//         Vec2 velocity = readVec(stream);
//         CHECK_DELIM(',')

//         double mass = readNum(stream);
//         CHECK_DELIM(',')

//         SpriteInfo spInfo = readSpriteInfo(table, stream);
//     CHECK_DELIM('}')

//     // MESSAGE("Player size = (%lg, %lg)", side, side);

//     return new Player(ev_man, spInfo, pos, Vec2(side, side), velocity, mass, 100);
// }

Camera readCam(std::ifstream &stream) {
    CHECK_DELIM('{')
        Vec2 size = readVec(stream);
        CHECK_DELIM(',')

        Vec2 pfp = readVec(stream);
        CHECK_DELIM(',')

        Vec2 pfs = readVec(stream);
    CHECK_DELIM('}')

    return Camera(size, pfp, pfs);
}

Background readBackground(std::ifstream &stream, SpriteManager& sprite_man) {
    CHECK_DELIM('{')
    CHECK_DELIM('(')
        Vec2 pos = readVec(stream);
        CHECK_DELIM(',')
        Vec2 size = readVec(stream);
        CHECK_DELIM(',')
        std::string texture = readString(stream);
    CHECK_DELIM(')')
    CHECK_DELIM('}')

    uint64_t id = sprite_man.getSize();
    sprite_man.loadTexture(id, texture);
    SpriteInfo spInfo(id, pos, size);
    return Background(spInfo.textureID, spInfo.spriteSize);
}

