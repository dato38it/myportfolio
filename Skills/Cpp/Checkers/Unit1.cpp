//---------------------------------------------------------------------------
#include <string.h>
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
String a=0; // zapis peremen
int x=0, y=0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Form1->StringGrid1->Cells[0][0] = 1;
        Form1->StringGrid1->Cells[2][0] = 1;
        Form1->StringGrid1->Cells[4][0] = 1;
        Form1->StringGrid1->Cells[6][0] = 1;
        Form1->StringGrid1->Cells[1][1] = 1;
        Form1->StringGrid1->Cells[3][1] = 1;
        Form1->StringGrid1->Cells[5][1] = 1;
        Form1->StringGrid1->Cells[7][1] = 1;
        Form1->StringGrid1->Cells[0][2] = 1;
        Form1->StringGrid1->Cells[2][2] = 1;
        Form1->StringGrid1->Cells[4][2] = 1;
        Form1->StringGrid1->Cells[6][2] = 1;
        Form1->StringGrid1->Cells[1][7] = 2;
        Form1->StringGrid1->Cells[3][7] = 2;
        Form1->StringGrid1->Cells[5][7] = 2;
        Form1->StringGrid1->Cells[7][7] = 2;
        Form1->StringGrid1->Cells[0][6] = 2;
        Form1->StringGrid1->Cells[2][6] = 2;
        Form1->StringGrid1->Cells[4][6] = 2;
        Form1->StringGrid1->Cells[6][6] = 2;
        Form1->StringGrid1->Cells[1][5] = 2;
        Form1->StringGrid1->Cells[3][5] = 2;
        Form1->StringGrid1->Cells[5][5] = 2;
        Form1->StringGrid1->Cells[7][5] = 2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
        //a = Form1->StringGrid1->Cells[ACol][ARow]; // mi klikmuli - on zapomnil,
        if(Form1->StringGrid1->Cells[ACol][ARow] == ""){      //hod
               Form1->StringGrid1->Cells[ACol][ARow] = a;
               Form1->StringGrid1->Cells[x][y] = "";


               int delX = 0;
               int delY = 0;
               delX = (ACol-x)/2;
               delY = (ARow-y)/2;
               Form1->Edit1->Text = delX;
               Form1->Edit2->Text = delY;
               Form1->StringGrid1->Cells[x+delX][y+delY]="";

        }
        else{
                a = Form1->StringGrid1->Cells[ACol][ARow];
                x=ACol;
                y=ARow;

        }
        bool win1 = true;
        for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                        if(Form1->StringGrid1->Cells[i][j]=="2"){
                                win1=false;
                                break;
                        }

                }
        }
        if(win1) {
                Form1->Label1->Visible=true;
        }


}
//---------------------------------------------------------------------------


