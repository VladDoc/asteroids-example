#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H


struct ControlState
{
    bool isLeftHeld{};
    bool isRightHeld{};
    bool isUpHeld{};
    bool isDownHeld{};

    bool leftMouseButton{};
    bool rightMouseButton{};
    bool middleMouseButton{};
};

#endif // CONTROLSTATE_H
