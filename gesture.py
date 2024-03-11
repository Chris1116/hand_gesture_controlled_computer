import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui

ArduinoSerial = serial.Serial('/dev/cu.usbmodem11401',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 seconds for the communication to get established

while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and print it as line
    print (incoming)
    
    if 'Play/Pause' in incoming:         
        pyautogui.typewrite(['space'], 0.2)
    '''
    if 'Rewind' in incoming:
        pyautogui.hotkey('ctrl', 'left')  

    if 'Forward' in incoming:
        pyautogui.hotkey('ctrl', 'right')  
    '''
    if 'Rewind' in incoming:
        pyautogui.press('left')  

    if 'Forward' in incoming:
        pyautogui.press('right')  

    if 'Vup' in incoming:
        pyautogui.hotkey('command', 'up')
           
    if 'Vdown' in incoming:
        pyautogui.hotkey('command', 'down')

    if 'next' in incoming:
        pyautogui.hotkey('command', 'right')
    
    if 'back' in incoming:
        pyautogui.hotkey('command', 'left')
    
    if 'change_L' in incoming:
        pyautogui.hotkey('ctrl', 'left')
        
    if 'change_R' in incoming:
        pyautogui.hotkey('ctrl', 'right')
    
    incoming = "" #refresh the incoming data