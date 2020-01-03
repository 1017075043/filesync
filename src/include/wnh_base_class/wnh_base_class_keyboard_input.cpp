#include "wnh_base_class.h"

static struct termios stored_settings;

void wnh_base_class::set_keypress (void)
{
    struct termios new_settings;

    tcgetattr (0, &stored_settings);

    new_settings = stored_settings;

    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr (0, TCSANOW, &new_settings);
    return;
}

void wnh_base_class::reset_keypress (void)
{
    tcsetattr (0, TCSANOW, &stored_settings);
    return;
}

string wnh_base_class::get_keyboard_input_string()
{
    int c = 0;
    char chr;
    set_keypress();
    int i = 0;
    while(1)
    {
        c = getchar();
        if(c == 27)
        {
            i = 1;
            //WNHINFO(i);
            continue;
        }
        if(i == 1)
        {
            if(c == 91)
            {
                i = 2;
                //WNHINFO(i);
                continue;
            }
            if(c == 79)
            {
                i = 3;
                //WNHINFO(i);
                continue;
            }
            //else
            //{
            //    printf("\n\n%c,%d\n\n",c, c);
            //}
            i = 0;
            //WNHINFO(i);
        }
        if(i == 2)
        {
            if(c == 65)
            {
                reset_keypress();
                return "up";
            }
            else if(c == 66)
            {
                reset_keypress();
                return "down";
            }
            else if(c == 67)
            {
                reset_keypress();
                return "right";
            }
            else if(c == 68)
            {
                reset_keypress();
                return "lift";
            }
            else if(c == 49)
            {
                i = 4;
                continue;
            }
            else if(c == 50)
            {
                i = 6;
                continue;
            }
            else if(c == 51)
            {
                reset_keypress();
                c = getchar();
                return "delete";
                i = 5;
                continue;
            }
            else if(c == 126)
            {
                reset_keypress();
                c = getchar();
                return "insert";
            }
            //else
            //{
            //    printf("\n\n%c,%d\n\n",c, c);
            //}
            i = 0;
            //WNHINFO(i);
            continue;
        }
        if(i == 3)
        {
            if(c == 80)
            {
                reset_keypress();
                return "F1";
            }
            else if(c == 81)
            {
                reset_keypress();
                return "F2";
            }
            else if(c == 82)
            {
                reset_keypress();
                return "F3";
            }
            else if(c == 83)
            {
                reset_keypress();
                return "F4";
            }
            //else
            //{
            //    printf("\n\n%c,%d\n\n",c, c);
            //}
            i = 0;
            //WNHINFO(i);
            continue;
        }
        else if(i == 4)
        {
            if(c == 53)
            {
                reset_keypress();
                c = getchar();
                return "F5";
                i = 0;
                continue;
            }
            if(c == 55)
            {
                reset_keypress();
                c = getchar();
                return "F6";
                i = 0;
                continue;
            }
            if(c == 56)
            {
                reset_keypress();
                c = getchar();
                return "F7";
                i = 0;
                continue;
            }
            if(c == 57)
            {
                reset_keypress();
                c = getchar();
                return "F8";
                i = 0;
                continue;
            }
            //else
            //{
            //    printf("\n\n%c,%d\n\n",c, c);
            //}
            i = 0;
            //WNHINFO(i);
            continue;
        }
        else if(i == 5)
        {
            i = 0;
            //WNHINFO(i);
            continue;
        }
        else if(i == 6)
        {
            if(c == 48)
            {
                reset_keypress();
                c = getchar();
                return "F9";
                i = 0;
                continue;
            }
            if(c == 49)
            {
                reset_keypress();
                c = getchar();
                return "F10";
                i = 0;
                continue;
            }
            if(c == 51)
            {
                reset_keypress();
                c = getchar();
                return "F11";
                i = 0;
                continue;
            }
            if(c == 52)
            {
                reset_keypress();
                c = getchar();
                return "F12";
                i = 0;
                continue;
            }
            //else
            //{
            //    printf("\n\n%c,%d\n\n",c, c);
            //}
            i = 0;
            //WNHINFO(i);
            continue;
        }
        else if(i == 0)
        {
            if(c == 8)
            {
                return "backspace";
            }
            if(c == 10)
            {
                return "enter";
            }
            else
            {
                chr = c;
                string temp_s;
                temp_s = temp_s + chr;
                reset_keypress();
                return temp_s;
                //printf("%c", chr);
            }
        }
    }
    reset_keypress();
    return "";
}
