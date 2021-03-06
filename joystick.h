// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

#ifndef __JOYSTICK_HH__
#define __JOYSTICK_HH__

#include <string>
#include <vector>
#include <linux/input.h> //EV_KEY, EV_ABS
#include <map>

#define JS_EVENT_BUTTON 0x01 // button pressed/released
#define JS_EVENT_AXIS   0x02 // joystick moved
#define JS_EVENT_INIT   0x80 // initial state of device

class LuaStick {
public:
    std::string name;
    std::string lua_name;
    int index=-1;
    int wiimote=-1;
    int vendor_id=-1;
    int product_id=-1;
};

/**
 * Represents a joystick device. Allows data to be sampled from it.
 */
class Joystick {
private:
    struct libevdev *dev = nullptr;
    int _fd = -1;
    uint64_t buttonFlags = 0;				//Curent values of all buttons
    std::vector<int> axesData; //Current values of all axis
    std::string name;
    std::string lua_name;
    std::string path;
    std::vector<int> axisMappings;
    std::vector<int> buttonMappings;
    std::map<int,int> axisMappingsRev;
    std::map<int,int> buttonMappingsRev;
    LuaStick stick;

    void initMaps();


public:
    ~Joystick();

    std::string getPath();

    /**
     * Initializes an instance of Joystick, using arguments from lua
     */
    Joystick(LuaStick, std::map<int,std::string> &wiimoteList);


    /**
    * Returns true if the joystick was found and may be used, otherwise false.
    */
    bool isFound();

    void closeJoy(std::map<int,std::string> &wiimoteList);

    std::string getName() { return name; };

    std::string getLuaName() { return lua_name; };

    struct libevdev *get_dev() { return dev; }

    unsigned int get_num_buttons();

    unsigned int get_num_axes();

    int get_axis_index(int);

    int get_button_index(int);

    int get_button_status(int);

    int get_axis_status(int);

    int get_axis_min(int _type);

    int get_axis_max(int _type);

    int get_button_type(int _index);

    int get_axis_type(int _index);

    void handleEvent(input_event ev);

    void set_led_state(unsigned int index, bool state);

    void init(std::map<int,std::string> &wiimoteList);
};

#endif
