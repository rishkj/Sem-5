import socket

HOST = '192.168.1.6'
PORT = 5050

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: 

    s.connect((HOST,PORT))    

    while 1:    
        
        print("What would you like to do?","1 - Login","2 - Signup","3 - Forgot password. Want to change it","4 - Exit",sep = '\n')
        choice = int(input())

        if choice == 1:
            user = input("Enter your username\n")
            passw = input("Enter your password\n")
            
            message = "1:" + user.strip() + ":" + passw.strip()

            
            s.sendall(message.encode('utf-8'))

            message1 = s.recv(1024)
            message1 = message1.decode('utf-8')
            print(message1 + "\n")

        elif choice == 2:
            user = input("Enter desired username\n")
            passw = input("Enter password. Should have atleast one uppercase letter, number and be more than 8 characters\n")
            passw1 = input("Enter password again\n")

            message = "2:" + user.strip() + ":" + passw.strip() + ":" + passw1.strip()

            s.sendall(message.encode('utf-8'))

            message1 = s.recv(1024)
            message1 = message1.decode('utf-8')
            print(message1 + "\n")

        elif choice == 3:
            user = input("Enter username\n")
            message = "3:" + user.strip()
            s.sendall(message.encode('utf-8'))

            message1 = s.recv(1024)
            message1 = message1.decode('utf-8')
            l = message1.split(':')
            
            if l[0] == '0':
                print(l[1])

            else:
                print(l[1])
                
                passw = input("Enter new password.  Should have atleast one uppercase letter, number and be more than 8 characters\n")
                s.sendall(passw.encode('utf-8'))
                
                message1 = s.recv(1024)
                message1 = message1.decode('utf-8')
                print(message1 + "\n")  
            
        
        elif choice == 4:
            message = "4"
            s.sendall(message.encode('utf-8'))
            break
        


s.close()


# # import socket

# # from tkinter import *
# # from tkinter.ttk import *

# # selected = IntVar()

# # window = Tk()
# # window.geometry('350*200')

# # main_page = Frame(window)
# # login = Frame(window)
# # signup = Frame(window)
# # fp = Frame(window)
# # fp1 = Frame(window)
# # ex = Frame(window)


# # def clicked():
# #     choice = selected.get()

# #     if choice == 1:
# #         init_Login_Page()
# #         login.tkraise()

# #     elif choice == 2:


        


# # def init_Main_Page():
# #     #main_page.title("Login and Signup")


# #     text = Label(main_page,text = "What would you like to do?").grid(row=0,column=0)

# #     rad1 = Radiobutton(main_page,text='Login', value=1, variable=selected).grid(row=2,column=0)
# #     rad2 = Radiobutton(main_page,text='Signup', value=2, variable=selected).grid(row=3,column=0)
# #     rad3 = Radiobutton(main_page,text='Forgot password. Change it', value=3, variable=selected).grid(row=4,column=0)
# #     rad4 = Radiobutton(main_page,text='Exit', value=4, variable=selected).grid(row=5,column=0)

# #     btn = Button(main_page,text="Submit",command=clicked)


# # def init_Login_Page():
# #     #login.title("Login")
# #     def login_clicked():
# #         message = "1:" + text1.get().strip() + ":" + text2.get().strip()
# #         s.sendall(message.encode('utf-8'))


# #     label1 = Label(login,text = "Username").grid(row=0,column=0)
# #     label2 = Label(login,text = "Password").grid(row=1,column=0)

# #     text1 = Entry(login).grid(row=0,column=1)
# #     text2 = Entry(login).grid(row=1,column=1)

# #     btn = Button(login,text="Submit",command=login_clicked)  


# # def init_Signup():
# #     #signup.title("Signup")

# #     label1 = Label(signup,text = "Username").grid(row=0,column=0)
# #     label2 = Label(signup,text = "Password").grid(row=1,column=0)
# #     label3 = Label(signup,text = "Confirm Password").grid(row=2,column=0)

# #     text1 = Entry(signup).grid(row=0,column=1)
# #     text2 = Entry(signup).grid(row=1,column=1)
# #     text3 = Entry(signup).grid(row=2,column=1)

# #     btn = Button(signup,text="Submit",command="") 


# # def init_FP():

# #     label1 = Label(fp,text = "Username").grid(row=0,column=0)

# #     text1 = Entry(fp).grid(row=0,column=1)

# #     btn = Button(fp,text="Submit",command="")


# # def init_FP1():
# #     label1 = Label(fp1,text = "Enter new password").grid(row=0,column=0)

# #     text1 = Entry(fp1).grid(row=0,column=1)

# #     btn = Button(fp1,text="Submit",command="")







  


# # # def clicked():
# # #     choice = selected.get()

# # #     for item in window.winfo_children():
# # #         item.destroy()
    
    
# # #     if choice == 1:
# # #         window.title("Login Page")
        
# # #         label1 = Label(window,text = "Username").grid(row=0,column=0)
# # #         label2 = Label(window,text = "Password").grid(row=0,column=0)

# # #         text1 = Entry(window).grid(row=0,column=1)
# # #         text2 = Entry(window).grid(row=1,column=1)

# # #         btn = Button(window,text="Submit",command="")





# # # def init_options_page():
    
# # #     window.title("Login and Signup")
    
# # #     text = Label(window,text = "What would you like to do?").grid(row=0,column=0)

# # #     rad1 = Radiobutton(window,text='Login', value=1, variable=selected).grid(row=2,column=0)
# # #     rad2 = Radiobutton(window,text='Signup', value=2, variable=selected).grid(row=3,column=0)
# # #     rad3 = Radiobutton(window,text='Forgot password. Change it', value=3, variable=selected).grid(row=4,column=0)
# # #     rad4 = Radiobutton(window,text='Exit', value=4, variable=selected).grid(row=5,column=0)

# # #     btn = Button(window,text="Submit",command=clicked)

# # #     window.mainloop()



# # HOST = '192.168.1.6'
# # PORT = 5050

# # with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: 

# #     s.connect((HOST,PORT))

# #     init_Main_Page()
# #     main_page.tkraise()  
# #     window.mainloop()  

# #     while 1:    
        
# #         # print("What would you like to do?","1 - Login","2 - Signup","3 - Forgot password. Want to change it","4 - Exit",sep = '\n')
# #         choice = int(input())

# #         if choice == 1:
# #             user = input("Enter your username\n")
# #             passw = input("Enter your password\n")
            
# #             message = "1:" + user.strip() + ":" + passw.strip()

            
# #             s.sendall(message.encode('utf-8'))

# #             message1 = s.recv(1024)
# #             message1 = message1.decode('utf-8')
# #             print(message1 + "\n")

# #         elif choice == 2:
# #             user = input("Enter desired username\n")
# #             passw = input("Enter password\n")
# #             passw1 = input("Enter password again\n")

# #             message = "2:" + user.strip() + ":" + passw.strip() + ":" + passw1.strip()

# #             s.sendall(message.encode('utf-8'))

# #             message1 = s.recv(1024)
# #             message1 = message1.decode('utf-8')
# #             print(message1 + "\n")

# #         elif choice == 3:
# #             user = input("Enter username\n")
# #             message = "3:" + user.strip()
# #             s.sendall(message.encode('utf-8'))

# #             message1 = s.recv(1024)
# #             message1 = message1.decode('utf-8')
# #             l = message1.split(':')
            
# #             if l[0] == '0':
# #                 print(l[1])

# #             else:
# #                 print(l[1])
                
# #                 passw = input("Enter new password\n")
# #                 s.sendall(passw.encode('utf-8'))
                
# #                 message1 = s.recv(1024)
# #                 message1 = message1.decode('utf-8')
# #                 print(message1 + "\n")  
            
        
# #         elif choice == 4:
# #             message = "4"
# #             s.sendall(message.encode('utf-8'))
# #             break
        


# # s.close()


# import socket

# import tkinter as tk                # python 3
# from tkinter import font  as tkfont # python 3

# HOST = '192.168.1.6'
# PORT = 5050

# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# s.connect((HOST,PORT))

# selected = int()

# class init_page(tk.Tk):

#     def __init__(self, *args, **kwargs):
#         tk.Tk.__init__(self, *args, **kwargs)

#         self.title_font = tkfont.Font(family='Helvetica', size=18, weight="bold", slant="italic")

#         # the container is where we'll stack a bunch of frames
#         # on top of each other, then the one we want visible
#         # will be raised above the others
#         container = tk.Frame(self)
#         container.pack(side="top", fill="both", expand=True)
#         container.grid_rowconfigure(0, weight=1)
#         container.grid_columnconfigure(0, weight=1)

#         self.frames = {}
#         for F in (MainPage, LoginPage, SignupPage):
#             page_name = F.__name__
#             frame = F(parent=container, controller=self)
#             self.frames[page_name] = frame

#             # put all of the pages in the same location;
#             # the one on the top of the stacking order
#             # will be the one that is visible.
#             frame.grid(row=0, column=0, sticky="nsew")

#         self.show_frame("MainPage")

#     def show_frame(self, page_name):
#         '''Show a frame for the given page name'''
#         frame = self.frames[page_name]
#         frame.tkraise()


# class MainPage(tk.Frame):

#     def __init__(self, parent, controller):
#         tk.Frame.__init__(self, parent)
#         self.controller = controller
#         label = tk.Label(self, text="What would you like to do?", font=controller.title_font)
#         label.pack(side="top", fill="x", pady=10)

#         rad1 = tk.Radiobutton(self,text='Login', value=1, variable=selected).pack()


#         button1 = tk.Button(self, text="Go to Page One",
#                             command=lambda: controller.show_frame("PageOne"))
#         button2 = tk.Button(self, text="Go to Page Two",
#                             command=lambda: controller.show_frame("PageTwo"))
#         button1.pack()
#         button2.pack()


# class LoginPage(tk.Frame):

#     def __init__(self, parent, controller):
#         tk.Frame.__init__(self, parent)
#         self.controller = controller
#         label = tk.Label(self, text="This is page 1", font=controller.title_font)
#         label.pack(side="top", fill="x", pady=10)
#         button = tk.Button(self, text="Go to the start page",
#                            command=lambda: controller.show_frame("StartPage"))
#         button.pack()


# class SignupPage(tk.Frame):

#     def __init__(self, parent, controller):
#         tk.Frame.__init__(self, parent)
#         self.controller = controller
#         label = tk.Label(self, text="This is page 2", font=controller.title_font)
#         label.pack(side="top", fill="x", pady=10)
#         button = tk.Button(self, text="Go to the start page",
#                            command=lambda: controller.show_frame("StartPage"))
#         button.pack()




# begin = init_page()
# begin.mainloop()












