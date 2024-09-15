# Менеджер паролей  
<p><strong>Task:</strong><br>
В командной строке программа у пользователя запрашивает данные и сохраняет даные в файл.<br>
links&nbsp;&nbsp; | email&nbsp;&nbsp; | login | password - Keys<br>
http://fds | fgd@fgd.ru | admin | fgdfgdf &nbsp;&nbsp;- Values<br>
<strong>Decision:</strong><br>
$ cat PasswordStorage.py<br>
repeat="y"<br>
while repeat == "y":<br>
keys=['links', 'mails', 'logins', 'passwords']<br>
print(keys)&nbsp;<br>
#print(keys[1])<br>
values=[]<br>
#print(values)<br>
link, email, login, password= input("Enter the link: "), input("Enter email: "), input("Enter login: "), input("Enter password: ")<br>
values.append(link)<br>
values.append(email)<br>
values.append(login)<br>
values.append(password)<br>
print(values)<br>
#print(values[2])<br>
row={}<br>
for i in range(len(keys)):<br>
#print(keys[i])<br>
#row[keys[i]] = None<br>
row[keys[i]] = values[i]<br>
print(row)<br>
createfile = input("Create new file? (y/n): ")<br>
if createfile == "y":<br>
namefile = input("Name the file where the passwords will be stored: ")<br>
with open(namefile,'w') as file:<br>
#file.write(str(row))<br>
for key, value in row.items():<br>
#print("Key: " + key)<br>
keyRow="| "+str(key)+" |"<br>
file.write(keyRow)<br>
file.write("\n")<br>
for key, value in row.items():<br>
valueRow="| "+str(value)+" |"<br>
file.write(valueRow)<br>
file.close()<br>
elif createfile == "n":<br>
namefile = input("Write the name of the file in which you want to make changes: ")<br>
with open(namefile,'a') as file:<br>
file.write("\n")<br>
for key, value in row.items():<br>
valueRow="| "+str(value)+" |"<br>
file.write(valueRow)<br>
file.write("\n")<br>
file.close()<br>
repeat = input("Do you want to continue? (y/n): ")<br>
if repeat == "n":<br>
break<br>
while (repeat!="y" and repeat!="n"):<br>
repeat = input("Please enter the correct answer (y/n): ")<br>
$ python PasswordStorage.py<br>
['links', 'mails', 'logins', 'passwords']<br>
Enter the link: 1<br>
Enter email: 2<br>
Enter login: 3<br>
Enter password: 4<br>
['1', '2', '3', '4']<br>
{'links': '1', 'mails': '2', 'logins': '3', 'passwords': '4'}<br>
Create new file? (y/n): y<br>
Name the file where the passwords will be stored: testfile<br>
Do you want to continue? (y/n): 1213wa<br>
Please enter the correct answer (y/n): y<br>
['links', 'mails', 'logins', 'passwords']<br>
Enter the link: 11<br>
Enter email: 22<br>
Enter login: 33<br>
Enter password: 4444444<br>
['11', '22', '33', '4444444']<br>
{'links': '11', 'mails': '22', 'logins': '33', 'passwords': '4444444'}<br>
Create new file? (y/n): n<br>
Write the name of the file in which you want to make changes: testfile<br>
Do you want to continue? (y/n): n<br>
$ cat testfile<br>
| links || mails || logins || passwords |<br>
| 1 || 2 || 3 || 4 |<br>
| 11 || 22 || 33 || 4444444 |<br>
</p>