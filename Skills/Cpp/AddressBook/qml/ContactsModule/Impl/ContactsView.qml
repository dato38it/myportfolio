import QtQuick 2.0
import ContactsModule.Base 1.0
import Contacts 1.0
BaseListView {
    /*model: ListModel {
        id: root
        ListElement {
            name: "Test1"
            surname: "Testing1"
            phoneNumber: "7952023323"
        }
        ListElement {
            name: "Test2"
            surname: "Testing2"
            phoneNumber: "7456346564"
        }
        ListElement {
            name: "Test3"
            surname: "Testing3"
            phoneNumber: "7690460406"
        }
    }*/
    id:root
    model: ContactsModel {
    }
    delegate: ContactDelegate {
        width: root.width
        height: 100
    }
}
