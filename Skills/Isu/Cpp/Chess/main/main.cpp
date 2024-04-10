#include <iostream>
using namespace std;
int main() {
    /*
    Task:
    The chess rook moves horizontally or vertically. Given two different cells of the chessboard, determine whether the rook can get from 
    the first cell to the second one in one move. The program receives four numbers from 1 to 8 each, specifying the column number and row 
    number first for the first cell, then for the second cell. The program should output YES if it is possible to get into the second cell 
    from the first cell by the move of the rook, or NO otherwise.
    Шахматная ладья ходит по горизонтали или вертикали. Даны две различные клетки шахматной доски, определите, может ли ладья попасть с 
    первой клетки на вторую одним ходом. Программа получает на вход четыре числа от 1 до 8 каждое, задающие номер столбца и номер строки 
    сначала для первой клетки, потом для второй клетки. Программа должна вывести YES, если из первой клетки ходом ладьи можно попасть во
    вторую или NO в противном случае.
    */
    /*int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    if(x1==x2 || y1==y2){
        cout<<"YES";
    }else{
        cout<<"NO";
    }
    return 0;*/
    /*
    Task:
    The chess king moves horizontally, vertically and diagonally, but only by 1 square. Given two different squares of the chessboard, 
    determine whether the king can get from the first square to the second one in one move. The program receives four numbers from 1 to 8 
    each, specifying the column number and row number first for the first cell, then for the second cell. The program should output YES if
    it is possible to get to the second square from the first square by the king's move, or NO otherwise.
    Шахматный король ходит по горизонтали, вертикали и диагонали, но только на 1 клетку. Даны две различные клетки шахматной доски, 
    определите, может ли король попасть с первой клетки на вторую одним ходом. Программа получает на вход четыре числа от 1 до 8 каждое, 
    задающие номер столбца и номер строки сначала для первой клетки, потом для второй клетки. Программа должна вывести YES, если из первой 
    клетки ходом короля можно попасть во вторую или NO в противном случае.
    */
    /*int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    if((x2==x1-1 && y2==y1-1)
            || (x2==x1-1 && y2==y1)
            || (x2==x1-1 && y2==y1+1)
            || (x2==x1 && y2==y1-1)
            || (x2==x1 && y2==y1)
            || (x2==x1 && y2==y1+1)
            || (x2==x1+1 && y2==y1-1)
            || (x2==x1+1 && y2==y1)
            || (x2==x1+1 && y2==y1+1)
            ){
        cout<<"YES";
    }else{
        cout<<"NO";
    }*/
    /*
    Task:
    The chess bishop moves diagonally. Given two different cells of the chessboard, determine whether the bishop can get from the first cell
    to the second one in one move. The program receives four numbers from 1 to 8 each, specifying the column number and row number first for
    the first cell, then for the second cell. The program should output YES if it is possible to get to the second cell from the first cell 
    by the bishop's move, or NO otherwise.
    Шахматный слон ходит по диагонали. Даны две различные клетки шахматной доски, определите, может ли слон попасть с первой клетки на 
    вторую одним ходом. Программа получает на вход четыре числа от 1 до 8 каждое, задающие номер столбца и номер строки сначала для первой 
    клетки, потом для второй клетки. Программа должна вывести YES, если из первой клетки ходом слона можно попасть во вторую или NO в 
    противном случае.
    */
    /*int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    if(x1-x2==y1-y2 || x2-x1==y2-y1){
        cout<<"YES";
    }else{
        cout<<"NO";
    }*/
    /*
    Task:
    The chess queen moves diagonally, horizontally or vertically. Given two different cells of the chessboard, determine whether the queen
    can get from the first cell to the second one in one move. The program receives four numbers from 1 to 8 each, specifying the column 
    number and row number first for the first cell, then for the second cell. The program should output YES if it is possible to get into 
    the second cell from the first cell by the move of the queen, or NO otherwise.
    Шахматный ферзь ходит по диагонали, горизонтали или вертикали. Даны две различные клетки шахматной доски, определите, может ли ферзь 
    попасть с первой клетки на вторую одним ходом. Программа получает на вход четыре числа от 1 до 8 каждое, задающие номер столбца и номер 
    строки сначала для первой клетки, потом для второй клетки. Программа должна вывести YES, если из первой клетки ходом ферзя можно попасть
    во вторую или NO в противном случае.
    */
    /*int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    if(x1-x2==y1-y2 || x2-x1==y2-y1 || x1==x2 || y1==y2){
        cout<<"YES";
    }else{
        cout<<"NO";
    }*/
    /*
    Task:
    The chess knight moves with the letter “G” — two squares vertically in any direction and one square horizontally, or vice versa. Given
    two different squares of the chessboard, determine whether the knight can get from the first square to the second one in one move. The
    program receives four numbers from 1 to 8 each, specifying the column number and row number first for the first cell, then for the 
    second cell. The program should output YES if it is possible to get to the second square from the first square by the knight's move, or 
    NO otherwise.
    Шахматный конь ходит буквой “Г” — на две клетки по вертикали в любом направлении и на одну клетку по горизонтали, или наоборот. Даны две 
    различные клетки шахматной доски, определите, может ли конь попасть с первой клетки на вторую одним ходом. Программа получает на вход 
    четыре числа от 1 до 8 каждое, задающие номер столбца и номер строки сначала для первой клетки, потом для второй клетки. Программа должна 
    вывести YES, если из первой клетки ходом коня можно попасть во вторую или NO в противном случае.
    */
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    if(x1-x2==y1-y2 || x2-x1==y2-y1 || x1==x2 || y1==y2){
        cout<<"YES";
    }else{
        cout<<"NO";
    }
    return 0;
}
