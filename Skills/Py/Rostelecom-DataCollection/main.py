from PyQt5 import QtWidgets, QtCore
from design import Ui_MainWindow
import sys
class mywindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(mywindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        #Здесь мы вносим изменения
        '''self.ui.lineEdit.setPlaceholderText("ip address1")
        self.ui.checkBox.stateChanged.connect(self.selected)
    def selected(self):
        value=True
        if self.ui.checkBox.isChecked():
            value=True
            self.ui.label_result.clear()
        else:
            value=False
            self.ui.label_result.setText("{}".format(self.ui.lineEdit.text()))
        self.ui.lineEdit.setEnabled(value)'''
        self.ui.lineEdit.setPlaceholderText("ip address1")
        self.ui.lineEdit_2.setPlaceholderText("ip address2")
        self.ui.lineEdit_3.setPlaceholderText("station name")
        self.ui.lineEdit_4.setPlaceholderText("station number")
        self.ui.lineEdit_5.setPlaceholderText("transmitter number")
        self.ui.checkBox.stateChanged.connect(self.writeF)
    def writeF(self):
    #def replData(ip1, ip2, sName, sNumb, tNumb):
        # список ключей, которые нужно будет заменить в файле template
        keys=['_ip1_', '_ip2_', '_sName_', '_sNumb_', '_tNumb_']
        #print(keys) 
        #Создаем список значений, на которые нужно будет заменить
        values=[]
        ip1 = self.ui.lineEdit.text()
        ip2 = self.ui.lineEdit_2.text()
        sName = self.ui.lineEdit_3.text()
        sNumb = self.ui.lineEdit_4.text()
        tNumb = self.ui.lineEdit_5.text()
        values.append(ip1)
        values.append(ip2)
        values.append(sName)
        values.append(sNumb)
        values.append(tNumb)
        #print(values)
        #Создаем словарь. в качестве ключей (keys) это будут список значений, в 
            #котором надо будет заменить в файле template, а в качестве значений 
            #(values) - список значений, на которые нужно будет заменить
        dictionary={}
        for i in range(len(keys)):
            dictionary[keys[i]] = values[i]
            search_text = dictionary[keys[i]]
            replace_text = keys[i]
            #print(search_text)
            #print(replace_text)
        value=True
        if self.ui.checkBox.isChecked():
            value=True
            #Считываем файл template, и меняем значения
            with open(r'template.txt', 'r') as oFile:
                rFile = oFile.read()
                for key, val in dictionary.items():
                    rFile = rFile.replace(key, str(val))
            #print(rFile) 
            #Запишем изменения в файл output
            with open(r'output.txt', 'a') as wFile:
                wFile.write('\n')
                wFile.write('\n')
                wFile.write('\n')
                wFile.write(rFile) 
            self.ui.lineEdit.clear()
            self.ui.lineEdit_2.clear()
            self.ui.lineEdit_3.clear()
            self.ui.lineEdit_4.clear()
            self.ui.lineEdit_5.clear()
        #else:
        #    value=False
        #    self.ui.label_result.setText("{}".format(self.ui.lineEdit.text()))
        #    self.ui.label_result.setText("{}".format(ip1))
        self.ui.lineEdit.setEnabled(value)
    '''
    repeat="y"
    while repeat == "y":
        #ip1, ip2, sName, sNumb, tNumb = 1111, 2222, 3333, 4444, 5555
        #ip1, ip2, sName, sNumb, tNumb = input("Enter the IP address1: "), input("Enter the IP address2: "), input("Enter the station name: "), input("Enter the station number: "), input("Enter the transmitter number: ")    
        replData(ip1, ip2, sName, sNumb, tNumb)
        #Если нужно повторить:
        repeat = input("Do you want to continue? (y/n): ")
        if repeat == "n":
            break
        while (repeat!="y" and repeat!="n"):
            repeat = input("Please enter the correct answer (y/n): ")
    '''
app = QtWidgets.QApplication([])
application = mywindow()
application.show() 
sys.exit(app.exec())

