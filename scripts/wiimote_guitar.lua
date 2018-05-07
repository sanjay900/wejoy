--Physical devices to use (type lsusb in terminal to list your connected devices)
devices =
{
    d0 = {
        name = "Nintendo Wii Remote Guitar",
        index = 0
    },
    d1 = {
        name = "Nintendo Wii Remote Accelerometer",
        index = 0
    }
}

--Virtual devices to create, current limit is maximum 54 (0 to 53) buttons and 19 (0 to 18) axes. Note that not every button or axis is fully tested to work.
--Creating more than one virtual devices is possible, making room for more buttons and axes.
v_devices =
{
    v0 =
    {
        buttons = 9,
        axes = 6
    }
}

function scale(x, in_min, in_max, out_min, out_max)
    return math.floor((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
end

function main()
    devices.d0.min = {}
    devices.d0.max = {}
    for i=0,get_axis_count(0) do
        devices.d0.min[i+1] = get_axis_min(0,i);
        devices.d0.max[i+1] = get_axis_max(0,i);
    end
    devices.d1.min = {}
    devices.d1.max = {}
    for i=0,get_axis_count(1) do
        devices.d1.min[i+1] = get_axis_min(1,i);
        devices.d1.max[i+1] = get_axis_max(1,i);
    end
end

function axis_event(device, axis, value)
    if device == "d0" then
        send_axis_event(0, axis, scale(value, devices.d0.min[axis+1], devices.d0.max[axis+1], MIN_ABS_VAL, MAX_ABS_VAL))
    end
    if device == "d1" then
        send_axis_event(0, axis+3, scale(value, devices.d1.min[axis+1], devices.d1.max[axis+1], MIN_ABS_VAL, MAX_ABS_VAL))
    end
end

function button_event(device, button, value)
    if device == "d0" then
        if button >= 2 then
            send_button_event(0, button-2, value)
        else
            send_button_event(0, button+7, value)
        end
    end
end