import PySimpleGUI as psg

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

