#ifndef _PIN_H
#define _PIN_H
#include <pin.h>
#endif

#include <Keyboard.h>

DigitalPin password(4, INPUT), taskmanager(3, INPUT), lock(2, INPUT);

void pressKey(unsigned char key)
{
    Keyboard.press(key);
    delay(5);
    Keyboard.releaseAll();
}

void setup()
{
    //Initialize Arduino
    Keyboard.begin();
}

void loop()
{
    //MAIN
    if(password.posEDGE())
    {
        Keyboard.print("username");
        pressKey(KEY_TAB);
        Keyboard.print("password");
        pressKey(KEY_TAB);
        pressKey(KEY_RETURN);
    }

    if(taskmanager.posEDGE())
    {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_ESC);
        delay(5);
        Keyboard.releaseAll();
    }

    if(lock.posEDGE())
    {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.print("l");
        delay(5);
        Keyboard.releaseAll();
    }

    delay(100);
}