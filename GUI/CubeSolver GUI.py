import PySimpleGUI as psg
import serial
import time


ser = serial.Serial(port="/dev/ttyAMA0", baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)

psg.theme('Dark Grey 15')
ergebnis = ''
empfangen = ''
layout = [
    [psg.Text(text='Zu auszuführende Verdrehung:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center'), psg.Button("i", font= 'courier')],
    [psg.Text(key ='Ergebnis', expand_x=True,size=30, justification="left", font=('Arial Bold', 15),background_color='black')],
    [psg.Button("Vorne (F)",key ='F'), psg.Button("Links (L)", key='L'), psg.Button("Rechts (R)", key ='R'), psg.Button("Unten (D)", key='D'), psg.Button("Hinten (B)", key='B'), psg.Button("Oben (U)", key='U'), psg.Button("Start!",expand_x=True, expand_y=True), psg.Button("Not-Aus", button_color='red')],
    [psg.Text(key ='Testbox', expand_x=True,size=30, justification="left", font=('Arial Bold', 15),background_color='black')],
]

window = psg.Window('Cube Solver EidP v1', layout, size=(715,450), icon=r'Rubiks_cube.ico')
while True:
    event, values = window.read()
    print(event, values)
    if event =="F":
        ergebnis = ergebnis + 'F'
    if event =="L":
        ergebnis = ergebnis + 'L'
    if event =="R":
        ergebnis = ergebnis + 'R'
    if event =="D":
        ergebnis = ergebnis + 'D'
    if event =="U":
        ergebnis = ergebnis + 'U'
    if event =="B":
        ergebnis = ergebnis + 'B'        
    
    if event == 'i':
        psg.popup("Hier würden schlaue Erklärungen stehen\ntest", title="Hilfe", icon=r'information.ico')
        
    if event == 'Not-Aus':
        break
    
    if event == 'Start!':
        ser.write(ergebnis.encode())
        time.sleep(2)
        testser = ser.readline()
        empfangen = testser.decode()
    if event in (None, 'Exit'):
        break
    window['Ergebnis'].update(ergebnis)
    window['Testbox'].update(empfangen)
window.close()
