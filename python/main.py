import serial
import uinput

ser = serial.Serial('/dev/rfcomm0', 115200)

# Create new mouse device
buttons = [uinput.KEY_W]
axes = [uinput.ABS_X, uinput.ABS_Y]
device = uinput.Device(buttons + axes)



def emulate_controller(button, value):
        print(value )
        device.emit(uinput.KEY_W, 1)



try:
    # sync package
    while True:
        print('Waiting for sync package...')
        while True:
            data = ser.read(1)
            if data == b'\xff':
                break

        # Read 4 bytes from UART
        #int.from_bytes(data, byteorder='big')
        data = ser.read(2)
        value = data[0]
        button=data[1]
        emulate_controller(button, value)
        #print (data)
        #print("")
        
        #axis, value = parse_data(data)
        #move_mouse(axis, value)

except KeyboardInterrupt:
    print("Program terminated by user")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    ser.close()
