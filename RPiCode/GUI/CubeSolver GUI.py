import PySimpleGUI as psg
import serial
import time


t=1

#Serielle Verbindung öffnen
ser = serial.Serial(port="/dev/ttyAMA0", baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)

psg.theme('Dark Grey 15')
ergebnis = ''
ScanErgebnis = 'Scannen...'

#Layouts erstellen für die GUI
layout1 = [
    [psg.Button("Reset"),psg.Text(text='Zu auszuführende Verdrehung:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center'), psg.Button("i", font= 'courier')],
    [psg.Text(key ='Ergebnis', expand_x=True,size=30, justification="left", font=('Arial Bold', 15),background_color='black')],
    [psg.Button("Vorne (F)",key ='F'), psg.Button("Links (L)", key='L'), psg.Button("Rechts (R)", key ='R'), psg.Button("Unten (D)", key='D'), psg.Button("Hinten (B)", key='B'), psg.Button("Oben (U)", key='U'), psg.Button("Start!",expand_x=True, expand_y=True)],
]


layout2 = [[psg.Text(text='Verdrehung beendet. Scannen starten:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
           
           [psg.Button("Go!")]
]

layout3 = [[psg.Text(key = 'ScanBox', expand_x=True, size=30, justification= "left", background_color='black')],
           [psg.Button("TestSer")],
           ]

#layouts zusammenfügen
layout = [[psg.Column(layout1, key='-COL1-'), psg.Column(layout2, visible=False, key='-COL2-'), psg.Column(layout3, visible=False, key ='-COL3-')]]
#GUI Fenster initialisieren
window = psg.Window('Cube Solver EidP v1', layout, size=(715,150), icon=r'Rubiks_cube.ico')
#GUI Schleife für Aktionen

layout = 1

while True:
    event, values = window.read()
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
    
    if event == 'Reset':
        ergebnis = ''
    
    if event == 'Start!':
        ser.write(ergebnis.encode())
        time.sleep(0.5)
        while (ser.in_waiting == 0):      #Warten auf Bereit Signal des ESP32
            #Schleife kann nicht leer sein
            i = 0
        
        #nächstes Layout laden und altes entfernen    
        window[f'-COL{layout}-'].update(visible=False)
        if layout < 5:
            layout += 1
            window[f'-COL{layout}-'].update(visible=True)
        if layout == 2:
            event, values = window.read()
            if event == psg.WIN_CLOSED:
                break
            if event == "Go!":
                bereit = 'GO'
                ser.write(bereit.encode())      #ESP32 scannen lassen
                window[f'-COL{layout}-'].update(visible=False)
                if layout < 5:
                    layout += 1
                    window[f'-COL{layout}-'].update(visible=True)

        if layout == 3:
            event, values = window.read()
            ser.flushInput()
            ser.flushOutput()
            time.sleep(1)
            print("NACH FLUSH")
            
            if t == 1:
                print("IN IF BED ANFANG")
                while (ser.in_waiting == 0):
                    i=0
                temp = ser.readline()
                ScanErgebnis = temp.decode()
                t = 2
                print("ENDE DER WAITING SCHLEIFE")
            print("NACH IF BEDINGUNG")
            if event == psg.WIN_CLOSED:
                break
            if event == "TestSer":
                print("IN TEST SER BUTTON VOR SERIAL")
                temp = ser.readline()
                ScanErgebnis = temp.decode()
            #if event == "Lösen starten!":
            #    window[f'-COL{layout}-'].update(visible=False)
            #    if layout < 5:
            #        layout +=1
            #        window[f'-COL{layout}-'].update(visible=True)  
                              
                    
                    
        
    if event in (None, 'Exit'):
        break
    window['Ergebnis'].update(ergebnis)
    window['ScanBox'].update(ScanErgebnis)
    
    
window.close()
