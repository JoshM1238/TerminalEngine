#include "Controller.h"


// ********** CHANGE THE PARAMETERS OF THIS TO A SINGLE ARRAY/VECTOR ONCE THE FUNCTION TO PARSE THE CONFIG FILE IS WRITTEN **********
Controller::Controls Controller::setControls(const char up, const char down, const char left, const char right) {

    // ********** REWRITE THIS TO WORK WITH A CONFIG FILE LATER **********
    Controls controls;

    controls.up = up;
    controls.down = down;
    controls.left = left;
    controls.right = right;

    return controls;
}

std::array<int, 2> Controller::getInput(const Controls& control){
    
    // The variables "moveX" and "moveY" store the amount that the object will be moved, and in which direction.
    // A movement of 1 for X means that the object will move one space to the right.
    // A movement of -1 for X moves to the left.
    // For Y, a movement of 1 moves one line downward, and a movement of -1 moves one line upward

    int moveX = 0;
    int moveY = 0;


    if (GetAsyncKeyState(control.up) & 0x8000) {
        moveY -= 1;
    }

    if (GetAsyncKeyState(control.down) & 0x8000) {
        moveY += 1;
    }

    if (GetAsyncKeyState(control.left) & 0x8000) {
        moveX -= 1;
    }

    if (GetAsyncKeyState(control.right) & 0x8000) {
        moveX += 1;
    }

    return { moveX, moveY };
}
