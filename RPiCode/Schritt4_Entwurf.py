import PySimpleGUI as psg


psg.set_options(font=('Arial Bold', 16))
layout2 = [
    [psg.Text("Verdrehung beendet! Scannen starten: ", size=(12,4)),psg.Input(expand_x=True)],
    [psg.Button("Go!")]
    ]
window = psg.Window("Fenster 2", layout2, size=(715,207))
event, values = window.read()
print (event, values)
window.close()
