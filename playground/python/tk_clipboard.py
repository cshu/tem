

import tkinter
s = tkinter.Tk()
#close window
s.withdraw()
s.clipboard_clear()
#set
s.clipboard_append('foo bar')
#get
print(s.selection_get(selection='CLIPBOARD'))
s.destroy()




