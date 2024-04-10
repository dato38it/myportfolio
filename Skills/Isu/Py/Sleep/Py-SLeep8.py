#Для должного погружения tkinter в сон потребуется использовать after():
import tkinter
class MyApp:
    def __init__(self, parent):
        self.root = parent
        self.root.geometry("400x400")
        self.frame = tkinter.Frame(parent)
        self.frame.pack()
        self.root.after(3000, self.delayed)
    def delayed(self):
        print('Я задержался')
if __name__ == "__main__":
    root = tkinter.Tk()
    app = MyApp(root)
    root.mainloop()
