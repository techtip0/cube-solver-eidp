import PySimpleGUI as psg

#Hier sind die GUI's für Schritt 4 und 7, auch schon zusammengeschaltet
def open_window2():

#Hier ist der GUI für Schritt 7

    psg.theme('Dark Grey 15')
    layout4 = [
        [psg.Text(text='Würfel gelöst:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
        [psg.Button("Erneut scannen")], [psg.Button("Hurra!")]
        ]

    window = psg.Window('Cube Solver EidP v1', layout4, size=(900,150), icon=r'Rubiks_cube.ico')


    while True:
        event, values = window.read()
        print(event, values)
        if event == "Hurra!" or event == psg.WIN_CLOSED:
            break
        
    window.close()

#Hier ist ein Test-GUI für Schritt 4
def main2():
    
    psg.theme('Dark Grey 15')
    layout3 = [
        [psg.Text(text='Scan abgeschlossen:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
        [psg.Button("Lösen starten!")]
        ]

    window = psg.Window('Cube Solver EidP v1', layout3, size=(900,150), icon=r'Rubiks_cube.ico')

    while True:
        event, values = window.read()
        print(event, values)
        if event == "Lösen starten!":
            open_window2()
        if event == psg.WIN_CLOSED:
            break
        window.close()
main2()




