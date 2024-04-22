import serial
import time
import keyboard

ser = serial.Serial('/dev/rfcomm0', 115200)

controle={"r1": '1',
          "r2": '2',
          "g1": '3',
          "g2": '4',
          "b1": '5',
          "b2": '6',
          "ju": 's',
          "jd": 'd',
          "jr": 'w',
          "jl": 'a',
          "bt": 'u',
        }

try:
    # sync package
    while True:
        print('Waiting for sync package...')
        while True:
            data = ser.read(1)
            if data == b'\xff':
                break   
        
        status = ser.read(1)[0]
        btn = ser.read(2).decode('utf-8')
        print (status, btn)
        if status:
            keyboard.press(controle[btn])
        else:
            keyboard.release(controle[btn])

except KeyboardInterrupt:
    print("Program terminated by user")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    ser.close()
