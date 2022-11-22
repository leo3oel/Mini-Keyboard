#ifndef _PIN_H
#define _PIN_H
#include <pin.h>
#endif

#include <Keyboard.h>
#include <Mouse.h>
#include "password.h"

#define CODELENGTH 6

extern String password;
extern String username;

short code[CODELENGTH] = {1, 2, 1, 3, 0, 1};

// Inputs
DigitalPin enterpassword(5, INPUT), taskmanager(3, INPUT), lock(2, INPUT), massaker(4, INPUT);
// Outputs
DigitalPin codeledhigh(7, OUTPUT);

bool checkcode(short code[], DigitalPin ledhigh, DigitalPin switch0, DigitalPin switch1, DigitalPin switch2, DigitalPin switch3)
{
    while (switch0.isHIGH() || switch1.isHIGH() || switch2.isHIGH() || switch3.isHIGH())
    {
    }
    bool allstates = 0;
    short number = 0;
    ledhigh.setOut(HIGH);
    for (short i = 0; i < CODELENGTH; i++) // compare input with code
    {
        // wait for input
        while (true)
        {
            number = 0;
            if (switch0.posEDGE())
            {
                number = 0;
                break;
            }
            else if (switch1.posEDGE())
            {
                number = 1;
                break;
            }
            else if (switch2.posEDGE())
            {
                number = 2;
                break;
            }
            else if (switch3.posEDGE())
            {
                number = 3;
                break;
            }
            else
            {
                // do nothing
            }
        }
        if (number == code[i] && i == CODELENGTH - 1) // input finished and ok
        {
            for (int j = 0; j < 3; j++)
            {
                ledhigh.setOut(LOW);
                delay(100);
                ledhigh.setOut(HIGH);
                delay(200);
            }
            ledhigh.setOut(LOW);
            return true;
        }
        else if (number == code[i]) // current input ok
        {
            ledhigh.setOut(LOW);
            delay(100);
            ledhigh.setOut(HIGH);
            delay(100);
        }
        else // wrong input
        {
            for (int j = 0; j < 8; j++)
            {
                ledhigh.setOut(LOW);
                delay(50);
                ledhigh.setOut(HIGH);
                delay(50);
            }
            ledhigh.setOut(LOW);
            return false;
        }
    }
}

void pressKey(unsigned char key)
{
    Keyboard.press(key);
    delay(5);
    Keyboard.releaseAll();
}

void setup()
{
    // Initialize Arduino
    Keyboard.begin();
    Mouse.begin();
}

void loop()
{
    // MAIN
    if (enterpassword.posEDGE())
    {
        if (checkcode(code, codeledhigh, enterpassword, massaker, taskmanager, lock))
        {
            Keyboard.print(username);
            pressKey(KEY_TAB);
            Keyboard.print(password);
            pressKey(KEY_TAB);
            pressKey(KEY_RETURN);
        }
    }

    if (taskmanager.posEDGE())
    {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_ESC);
        delay(5);
        Keyboard.releaseAll();
    }

    if (lock.posEDGE())
    {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.print("l");
        delay(5);
        Keyboard.releaseAll();
    }

    if(massaker.posEDGE())
    {
        while(massaker.isHIGH())
        {
            // wait till low
        } 
        while(massaker.isLOW())
        {
            bool pos = rand()%2;
            if(pos)
                Mouse.move((rand()%25), (rand()%5),0);
            else
                Mouse.move(-(rand()%15), -(rand()%15),0);
            if(millis()%3000<40)
            {
                short random = rand()%4;
                switch (random)
                {
                case 0: break;
                case 1: Mouse.click(MOUSE_LEFT); break;
                case 2: Mouse.click(MOUSE_RIGHT); break;
                case 3: Mouse.click(MOUSE_MIDDLE); break;
                }
            }

            delay(50);
        }
        while(massaker.isHIGH()){} // wait till low again
    }
    delay(100);
}