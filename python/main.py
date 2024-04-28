import serial
import keyboard
import alsaaudio

import alsaaudio
import subprocess

def set_brightness(level):
    level = max(0, min(100, level))
    brightness_value = level / 100.0
    subprocess.run(["xrandr", "--output", "eDP-1", "--brightness", str(brightness_value)])

def set_volume(volume):
    mixer = alsaaudio.Mixer()
    mixer.setvolume(volume)


ser = serial.Serial('/dev/rfcomm0', 115200)
#ser = serial.Serial('/dev/ttyACM0', 115200)
mixer = alsaaudio.Mixer()
mixer.setmute(0) 


controle={"r1": '1',
          "r2": '2',
          "g1": '3',
          "g2": '4',
          "b1": '5',
          "b2": '6',
          "ju": 'w',
          "jd": 's',
          "jr": 'd',
          "jl": 'a',    
          "bt": 'u',
        }

    # sync package
while True:
    try:
        print('Waiting for sync package...')
        while True:
            data = ser.read(1)
            if data == b'\xff':
                break   
        val = ser.read(1)[0]
        btn = ser.read(2).decode('utf-8')
        print (val, btn)
        if (btn[0] != 'P'):
            if val == 1:
                keyboard.press(controle[btn])
            else:
                keyboard.release(controle[btn])
        else:
            # VOLUME
            if btn[1] == '1':
                set_volume(val)
            elif btn[1] == '2':
                set_brightness(val)
    except:
        print('Paconte com erro')

ser.close()
    
        

""" except KeyboardInterrupt:
    print("Program terminated by user")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    ser.close() """
