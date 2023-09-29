import PySimpleGUI as psg

psg.theme('Dark Grey 15')
layout2 = [
    [psg.Text(text='Verdrehung beendet. Scannen starten:',font=('Arial Bold', 18),size=30,expand_x=True,justification='center')],
    [psg.Button("Go!")]
]

window = psg.Window('Cube Solver EidP v1', layout2, size=(900,150), icon=r'Rubiks_cube.ico')


while True:
    event, values = window.read()
    print(event, values)
    if event == "Go!" or event == psg.WIN_CLOSED:
        break

window.close()

