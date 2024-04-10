#Метод after() — Погружение в сон для Tkinter
import tkinter
import time
class MyApp:
    def __init__(self, parent):
        self.root = parent
        self.root.geometry("400x400")
        self.frame = tkinter.Frame(parent)
        self.frame.pack()
        b = tkinter.Button(text="click me", command=self.delayed)
        b.pack()
    def delayed(self):
        time.sleep(3)
if __name__ == "__main__":
    root = tkinter.Tk()
    app = MyApp(root)
    root.mainloop()
