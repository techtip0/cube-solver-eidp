#importieren wichtiger Bibliotheken
import PySimpleGUI as psg
import serial
import twophase.solver as sv
import time


#t wird benutzt um Code in der while True Schleife nur einmalig ausgeführt wird pro Programmdurchlauf
t=1

#Serielle Verbindung öffnen. Musste vorher durch raspi-config konfiguriert werden. 9600 Baud-Rate gleich auf dem ESP32
ser = serial.Serial(port="/dev/ttyAMA0", baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=5)

psg.theme('Dark Grey 15')       #Theme ausgewählt damit es schön aussieht :)
ergebnis = ''
ScanErgebnis = 'Scannen...'     #Platzhalter während des Scannens

#Einzelne layouts erstellen für die GUI


layout1 = [
    [psg.Text("    ", size=8), psg.Text("EidP Cube Solver", expand_x=True, size=30, justification='c', font=('Arial Bold', 20)), psg.Button("i", font= 'courier',key="i1")],                #Text, Infobutton
    [psg.Text("    ", size=8), psg.Text("Kalibrieren notwendig. Kann übersprungen werden, wird aber nicht empfohlen.", expand_x=True, size= 25, justification='c',font=('Arial', 10))],     #Text
    [psg.Text("    ", size=8), psg.Button("Kalibrieren", size= 20, key ='calib'), psg.Text("               ", size=20), psg.Button("Überspringen", size=20, key='skip')]                    #Buttons zum Kalibrieren Ja/Nein
    ]



layout2 = [
    [psg.Button("Reset"),psg.Text(text='Zu auszuführende Verdrehung:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center'), psg.Button("i", font= 'courier', key="i2")],       #Resetbutton der Verdrehung, Text, Infobutton
    [psg.Text(key ='Ergebnis', expand_x=True,size=30, justification="left", font=('Arial Bold', 15),background_color='black')],                                                                 #Text
    [psg.Button("Vorne (F)",key ='F'), psg.Button("Links (L)", key='L'), psg.Button("Rechts (R)", key ='R'), psg.Button("Unten (D)", key='D'), psg.Button("Hinten (B)", key='B'), psg.Button("Oben (U)", key='U'), psg.Button("Start!",expand_x=True, expand_y=True)],  #Buttons zum Auswählen der Verdrehungen und Starten
]


layout3 = [[psg.Text(text="Verdrehung beendet.",font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],     #Text
           [psg.Button("Scan beginnen", key ='go')]     #Button zum Starten
]

layout4 = [
            [psg.Text(text='Gescannter Würfel:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')], #Text
            [psg.Text(key= "ScanBox", expand_x=True, size=40, font=('Arial Bold', 11), justification= "left", background_color='black')],   #Text, der mit dem gescannten Würfel geupdatet wird
            [psg.Button("Lösen!", size=30)],    #Button zum Lösen
           ]

layout5 = [
            [psg.Text(text="Lösen...",font=('Arial Bold', 18),size=30,expand_x=True,justification='center', key= "Endbox")],    #Text
            [psg.Button("Programm beenden", key='Ende', size=30), psg.Text("           ", size= 30), psg.Button("Programm neu starten", key='nochmal', size=30) ]   #Buttons zum neustarten oder beenden des Programmes
           ]

#layouts zusammenfügen über Columns
layout = [[psg.Column(layout1, key='-COL1-'), psg.Column(layout2, visible=False, key='-COL2-'), psg.Column(layout3, visible=False, key ='-COL3-'), psg.Column(layout4, visible=False, key ='-COL4-'), psg.Column(layout5, visible=False, key ='-COL5-')]]
#GUI Fenster initialisieren. Icon muss im Ordner mit Programm sein
window = psg.Window('Cube Solver EidP v2', layout, size=(680,150), icon=r'Rubiks_cube.png')


layout = 1 #Start mit erstem layout
#GUI Schleife. Wenn diese beendet wird, schließt das Programm
while True:
    event, values = window.read()
    
    if layout == 1:
        if event =="calib":
            calib = "calib"
            ser.write(calib.encode())         #Sendet Kalibirierungssignal  
            while (ser.in_waiting == 0):      #Warten auf Bereit Signal des ESP32
                pass
            
            #nächstes Layout laden und altes entfernen    
            window[f'-COL{layout}-'].update(visible=False)  #setzt momentes Layout auf unsichtbar
            if layout < 6:
                layout += 1 #Falls noch Layouts vorhanden sind, wird es um 1 erhöht
                window[f'-COL{layout}-'].update(visible=True)   #Nächstes Layout wird sichtbar
        if event == "skip":
            skip = "skip"
            ser.write(skip.encode())
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout += 1
                window[f'-COL{layout}-'].update(visible=True)
        
        if event == 'i1':
            psg.popup("Nach einigen Tests hat sich Kalibrieren als stark empfohlen nach JEDEM Durchgang herausgestellt\n\nÜberspringen auf eigene Verantwortung", title="Hilfe", icon=r'information.png') #Popup als PySimpleGUI Funktion erstellt ein simples Popup mit Informationen
    
    
    if layout == 2:
        #Buttons addieren die gewählte Verdrehung zum gesamten String
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
        
        if event == 'i2':
            psg.popup("Empfohlen sind über ~25 Verdrehungen\nDer Roboter löst immer in unter 21 Schritten", title="Hilfe", icon=r'information.png')
        
        if event == 'Reset':
            ergebnis = ''
        
        if event == 'Start!':
            ser.write(ergebnis.encode())    #In Python ist es wichtig serielle Daten zuerst zu encoden, bevor sie versandt werden können
            time.sleep(2)
            ser.reset_input_buffer()        #ohne Zurücksetzen bleiben Daten zu Lange im Buffer und aktivieren die Schleifen die auf ein Signal warten
            while (ser.in_waiting == 0):
                pass
               
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout += 1
                window[f'-COL{layout}-'].update(visible=True)
    if layout == 3:
        if event == "go":
            bereit = 'GO'
            ser.write(bereit.encode())      #ESP32 scannen lassen
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout += 1
                window[f'-COL{layout}-'].update(visible=True)
                window['ScanBox'].update(ScanErgebnis)      


    if layout == 4:      
        
        ser.reset_input_buffer()
        ser.reset_output_buffer()
        
        if t == 1:
            while (ser.in_waiting == 0):
                pass
            temp = ser.readline()
            temp2 = temp.decode()   #empfangene Daten müssen zuerst decoded werden
            ScanErgebnis = temp2.strip()    #strip entzieht \n und andere Anhänge vom String
            window['ScanBox'].update(ScanErgebnis) #Updatet die Textbox mit gescanntem Würfel
            print(ScanErgebnis)
            t = 2   #t wird 2 gesetzt, damit dieser Code nur einmalig abläuft
            
            #Prüfen, ob alle Seiten neun mal im Scan vertreten sind. Theoretisch kann auch der Fehler aufkommen, dass Seiten so vertauscht werden, dass sie trotzdem 9 bleiben.
            #Dieser Fehler ist in den zahlreichen Tests aber nie aufgetreten.
            if (ScanErgebnis.count('F') or ScanErgebnis.count('R') or ScanErgebnis.count('L') or ScanErgebnis.count('B') or ScanErgebnis.count('U') or ScanErgebnis.count('D')) != 9:   
                #Error Popup agiert ähnlich zum normalen Popup, hat aber einen vorgefertigten Button
                psg.popup_error("SCANFEHLER!\n\nBitte Lichtverhältnisse und Motorenposition prüfen\n\nBeim drücken auf Error wird der Würfel automatisch zurück gedreht und das Programm neu gestartet", title="Fehler!", icon=r'Error.png')
                Pruefung = "NOK"
                ser.write(Pruefung.encode())
                time.sleep(2)
                ergebnisreverse = ergebnis[::-1]    #String umdrehen
                ser.write(ergebnisreverse.encode()) 
                window[f'-COL{layout}-'].update(visible=False)  #Momentanes Layout unsichtbar machen und zurück auf das erste springen
                layout = 1
                t=1             #Einmaliger Code kann wieder durchlaufen werden
                ergebnis = ''   #Variable ergebnis löschen, für neue Eingabe
                window[f'-COL{layout}-'].update(visible=True) 
                time.sleep(3)
                ser.reset_input_buffer()
                ser.reset_output_buffer()       #Resets wichtig für zuverlässige Übertragung der Lösung
                
            else:
                Pruefung = "OK"
                ser.write(Pruefung.encode())

        if event == "Lösen!":
            solutiontemp = sv.solve(ScanErgebnis,19,2)      #sv.solve Berechnet anhand des gescannten Würfels die Lösung in 19 moves. Falls die Berechnung länger als 2s dauert, wird eine leicht längere genommen
            solution = solutiontemp + 'P'                   #P dient als Signal zum Ende des Strings
            print(solution)
            ser.write(solution.encode())
            window[f'-COL{layout}-'].update(visible=False)
            if layout < 6:
                layout +=1
                window[f'-COL{layout}-'].update(visible=True) 
    
    if layout == 5:       
        while (ser.in_waiting == 0):
            pass
        window['Endbox'].update("Würfel ist gelöst!")
        if event == "nochmal":
            window[f'-COL{layout}-'].update(visible=False)
            layout = 1
            t=1
            ergebnis = ''
            window[f'-COL{layout}-'].update(visible=True) 
            ser.reset_input_buffer()
            ser.reset_input_buffer()
            
        if event == "Ende":
            break
        
        
    if event in (None, 'Exit'):
        break
    window['Ergebnis'].update(ergebnis)
    window['ScanBox'].update(ScanErgebnis)
    
    
window.close()  #schließt das Fenster
