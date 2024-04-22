import serial
import time
import keyboard

ser = serial.Serial('/dev/rfcomm0', 115200)

wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

def emulate():
    print(1)
    keyboard.press('w')
    time.sleep(0.1)
    keyboard.release('w')
    #pyautogui.keyup('w')


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
        emulate()
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
