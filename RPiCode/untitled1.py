import PySimpleGUI as psg

#Layouts erstellen:
psg.theme('Dark Grey 15')
ergebnis = ''
layout1 = [[psg.Text(text='Zu auszuführende Verdrehung:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center'), psg.Button("i", font= 'courier')],
[psg.Text(key ='Ergebnis', expand_x=True,size=30, justification="left", font=('Arial Bold', 15),background_color='black')],
[psg.Button("Vorne (F)",key ='F'), psg.Button("Links (L)", key='L'), psg.Button("Rechts (R)", key ='R'), psg.Button("Unten (D)", key='D'), psg.Button("Hinten (B)", key='B'), psg.Button("Oben (U)", key='U'), psg.Button("Start!",expand_x=True, expand_y=True), psg.Button("Not-Aus", button_color='red')]]

layout2 = [[psg.Text(text='Verdrehung beendet. Scannen starten:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
[psg.Button("Go!")]]

layout3 = [[psg.Text(text='Scan abgeschlossen:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
[psg.Button("Lösen starten!")]]

layout4 = [[psg.Text(text='Würfel gelöst:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
[psg.Button("Erneut scannen")], [psg.Button("Hurra!")]]

# ----------- Create actual layout using Columns and a row of Buttons
layout = [[psg.Column(layout1, key='-COL1-'), psg.Column(layout2, visible=False, key='-COL2-'), psg.Column(layout3, visible=False, key='-COL3-'), psg.Column(layout4, visible=False, key='-COL4-')]]
          
window = psg.Window('Cube Solver EidP v1', layout, size=(900,150), icon=r'Rubiks_cube.ico')

#window = psg.Window('Dynamic Window', layout)

layout = 1  # The currently visible layout
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

    if event in (None, 'Exit'):
        break
    window['Ergebnis'].update(ergebnis)
    #window.close()
    if event == 'Start!':
        print(layout)
        window[f'-COL{layout}-'].update(visible=False)
        #if layout ==1:
        #    name = values['-NAME-']        
        if layout < 4:
            layout += 1  
            window[f'-COL{layout}-'].update(visible=True)
        if layout == 2:
            #window['-INSTRUCTIONS-'].update('Thanks for registering '+name) 
            event, values = window.read()
            print(event, values)
            if event == psg.WIN_CLOSED:
                break
            if event == "Go!":
                window[f'-COL{layout}-'].update(visible=False)
                if layout < 4:
                    layout += 1  
                    window[f'-COL{layout}-'].update(visible=True)
        if layout == 3:
            while True:
                event, values = window.read()
                print(event, values)
                if event == psg.WIN_CLOSED:
                    break
                if event == "Lösen starten!":
                    window[f'-COL{layout}-'].update(visible=False)
                    if layout < 5:
                        layout +=1
                        window[f'-COL{layout}-'].update(visible=True)
        if layout == 4:
            while True:
                event, values = window.read()
                print(event, values)
                if event == "Hurra!" or event == psg.WIN_CLOSED:
                    break
                            
                        
            #window.close
            
    
window.close()

















