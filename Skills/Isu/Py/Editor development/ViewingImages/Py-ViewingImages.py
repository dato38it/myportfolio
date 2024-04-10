import tkinter as tk
from PIL import Image, ImageTk
from resizeimage import resizeimage
win=tk.Tk()
win.title("Image Viewer")
win.geometry("300x300")
path=r'/home/user/Документы/.Git/Py/Py-ViewingImages/img/test.jpg'
resized_image=resizeimage.resize_cover(Image.open(path), [300, 300])
render_pic=ImageTk.PhotoImage(resized_image)
img=tk.Label(win,image=render_pic)
img.pack()
win.mainloop()
