import socket
import os

HOST = ''
PORT = 5050

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind((HOST,PORT))
s.listen(1)

conn , addr = s.accept()

def password_validation(text):
    num_upp = 0
    num_number = 0
    num_length = 0
    for i in text:
        if i.isupper():
            num_upp += 1
        elif i.isdigit():
            num_number += 1

        num_length += 1

    if num_upp > 0 and num_number > 0 and num_length > 8:
        return 1
    return 0
    

while True:

    message = conn.recv(1024)
    message = message.decode('utf-8')

    l = message.split(':')
    if l[0] == '1':
        print("User is trying to login")

        f = open("passwords.txt","r+")

        message1 = ""

        if os.stat("passwords.txt").st_size == 0:
            print("Login failed\n")
            message1 = "Username doesnt exist"

        else:
            message = f.read()
            users = message.strip().split('\n')

            user_and_pass = {}

            for u in users:
                (user,passw) = u.split(',')
                user_and_pass[user] = passw

            if l[1] in user_and_pass.keys():

                if user_and_pass[l[1]] != l[2]:
                    print("Login failed\n")
                    message1 = "Incorrect password"
            
                else:
                    print("Login succeeded\n")
                    message1 = "Login successful"
            
            else:
                print("Login failed\n")
                message1 = "Username doesnt exist"

        conn.sendall(message1.encode('utf-8'))

        f.close()

    elif l[0] == '2':
        print("User is trying to sign up")

        message1 =""

        f = open("passwords.txt","r+")

        if os.stat("passwords.txt").st_size == 0:
            f.close()
        
        else:
            message = f.read()
            users = message.strip().split('\n')

            user_and_pass = {}

            for u in users:
                (user,passw) = u.split(',')
                user_and_pass[user] = passw
            
            if l[1] in user_and_pass.keys():
                print("Account exists. Login instead\n")
                message1 = "Username already exists. Account not created"
                f.close()
                conn.sendall(message1.encode('utf-8'))

                continue


        f = open("passwords.txt","a+")

        flag = password_validation(l[2])

        if flag == 0:
            print("Unable to create account\n")
            message1 = "Password not secure enough"

        else:

            if l[2] != l[3]:
                print("Unable to create account\n")
                message1 = "Passwords do not match"

            else:
                print("Account successfully created\n")
                str = l[1] + ',' + l[2]
                f.write(str + '\n')
            
                message1 = "Account has been created"

        conn.sendall(message1.encode('utf-8'))    
        
        f.close()

    elif l[0] == '3':
        print("User has forgetten his password")
        f = open("passwords.txt","r+")

        message1 = ""

        if os.stat("passwords.txt").st_size == 0:
            print("Cant find account\n")
            message1 = "0:Username doesnt exist"

        else:
            message = f.read()
            users = message.strip().split('\n')

            user_and_pass = {}

            for u in users:
                (user,passw) = u.split(',')
                user_and_pass[user] = passw

            if l[1] in user_and_pass.keys():

                message1 = "1:Username exists. Now you can change your password"
                conn.sendall(message1.encode('utf-8'))
                
                message = conn.recv(1024)
                message = message.decode('utf-8')

                user_and_pass[l[1]] = message
                f.close()

                flag = password_validation(message)
                if flag == 0:
                    print("Password not changed\n")
                    message1 = "Password not secure enough"
                    conn.sendall(message1.encode('utf-8'))

                    continue
                

                f = open("passwords.txt","w+")
                for i in user_and_pass:
                    str = i + ',' + user_and_pass[i]
                    f.write(str + '\n')

                f.close()

                print("Password has been changed\n")

                message1 = "Password changed successfully"
                conn.sendall(message1.encode('utf-8'))

                continue


            
            else:
                print("Cant find account\n")
                message1 = "0:Username doesnt exist"

        conn.sendall(message1.encode('utf-8'))

        f.close()

        

    elif l[0] == '4':
        print("User wants to quit")
        conn.close()
        break

s.close()