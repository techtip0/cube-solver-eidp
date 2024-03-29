import PySimpleGUI as psg
import serial
import twophase.solver as sv
import time as time



t=1

#Serielle Verbindung öffnen
ser = serial.Serial(port="/dev/ttyAMA0", baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=5)

psg.theme('Dark Grey 15')
ergebnis = ''
ScanErgebnis = 'Scannen...'

#Layouts erstellen für die GUI

layout1 = [
    [psg.Text("    ", size=8), psg.Text("EidP Cube Solver", expand_x=True, size=30, justification='c', font=('Arial Bold', 20)), psg.Button("i", font= 'courier')],
    [psg.Text("    ", size=8), psg.Text("Kalibrieren stark empfohlen. Kann übersprungen werden.", expand_x=True, size= 25, justification='c',font=('Arial', 10))],
    [psg.Text("    ", size=8), psg.Button("Kalibrieren", size= 20, key ='calib'), psg.Text("               ", size=20), psg.Button("Überspringen", size=20, key='skip')]
    ]



layout2 = [
    [psg.Button("Reset"),psg.Text(text='Zu auszuführende Verdrehung:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center'), psg.Button("i", font= 'courier')],
    [psg.Text(key ='Ergebnis', expand_x=True,size=30, justification="left", font=('Arial Bold', 15),background_color='black')],
    [psg.Button("Vorne (F)",key ='F'), psg.Button("Links (L)", key='L'), psg.Button("Rechts (R)", key ='R'), psg.Button("Unten (D)", key='D'), psg.Button("Hinten (B)", key='B'), psg.Button("Oben (U)", key='U'), psg.Button("Start!",expand_x=True, expand_y=True)],
]


layout3 = [[psg.Text(text="Verdrehung beendet.",font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
           [psg.Button("Scan beginnen", key ='go')]
]

layout4 = [
            [psg.Text(text='Gescannter Würfel:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
            [psg.Text(key = 'ScanBox', expand_x=True, size=40, font=('Arial Bold', 15), justification= "left", background_color='black')],
            [psg.Button("Lösen!", size=30)],
           ]

layout5 = [
            [psg.Text(text="Lösen...",font=('Arial Bold', 18),size=30,expand_x=True,justification='center', key= "Endbox")],
            [psg.Button("Programm beenden", key='Ende', size=30), psg.Text("           ", size= 30), psg.Button("Programm neu starten", key='nochmal', size=30) ]
           ]

#layouts zusammenfügen
layout = [[psg.Column(layout1, key='-COL1-'), psg.Column(layout2, visible=False, key='-COL2-'), psg.Column(layout3, visible=False, key ='-COL3-'), psg.Column(layout4, visible=False, key ='-COL4-'), psg.Column(layout5, visible=False, key ='-COL5-')]]
#GUI Fenster initialisieren
window = psg.Window('Cube Solver EidP v1', layout, size=(680,150), icon=r'Rubiks_cube.ico')
#GUI Schleife für Aktionen

layout = 1

while True:
    event, values = window.read()
    
    if layout == 1:
        if event =="calib":
            calib = "calib"
            ser.write(calib.encode())
            while (ser.in_waiting == 0):      #Warten auf Bereit Signal des ESP32
                #Schleife kann nicht leer sein
                i = 0
            
            #nächstes Layout laden und altes entfernen    
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout += 1
                window[f'-COL{layout}-'].update(visible=True)
        if event == "skip":
            skip = "skip"
            ser.write(skip.encode())
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout += 1
                window[f'-COL{layout}-'].update(visible=True)
        
        if event == 'i':
            psg.popup("Hier würden schlaue Erklärungen stehen\ntest", title="Hilfe", icon=r'information.ico')
    
    
    if layout == 2:
        
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
            time.sleep(2)
            while (ser.in_waiting == 0):      #Warten auf Bereit Signal des ESP32
                #Schleife kann nicht leer sein
                i = 0
            
            #nächstes Layout laden und altes entfernen    
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout += 1
                window[f'-COL{layout}-'].update(visible=True)
    if layout == 3:
        if event == psg.WIN_CLOSED:
            break
        if event == "go":
            bereit = 'GO'
            ser.write(bereit.encode())      #ESP32 scannen lassen
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout += 1
                window[f'-COL{layout}-'].update(visible=True)
                #event, values = window.read()

    if layout == 4:
        #print("IN LAYOUT3 IF BEDINGUNG")
        #event, values = window.read()
        ser.reset_input_buffer()
        ser.reset_output_buffer()
        #print("NACH FLUSH")
            
        if t == 1:
            #print("IN IF BED ANFANG")
            while (ser.in_waiting == 0):
                #print("ICH BIN IN SCHLEIFE LESEN")
                i=0
            #time.sleep(0.5)
            temp = ser.readline()
            temp2 = temp.decode()
            ScanErgebnis = temp2.strip()
            t = 2
            #ser.readline
            #print(temp)
            #print(ScanErgebnis)
            #print("ENDE DER WAITING SCHLEIFE")
        #print("NACH IF BEDINGUNG")
        if event == psg.WIN_CLOSED:
            break
        if event == "Lösen!":
            solutiontemp = sv.solve(ScanErgebnis,19,2)
            solution = solutiontemp + 'P'
            print(solution)
            ser.write(solution.encode())
            time.sleep(2)
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout +=1
                window[f'-COL{layout}-'].update(visible=True) 
    
    if layout == 5:       
        while (ser.in_waiting == 0):
            i=0
        window['Endbox'].update("Würfel ist gelöst!")
        if event == "nochmal":
            window[f'-COL{layout}-'].update(visible=False)
            layout = 1
            t=1
            window[f'-COL{layout}-'].update(visible=True) 
            
        if event == "Ende":
            break
        
                    
        
    if event in (None, 'Exit'):
        break
    window['Ergebnis'].update(ergebnis)
    window['ScanBox'].update(ScanErgebnis)
    
    
    
window.close()
