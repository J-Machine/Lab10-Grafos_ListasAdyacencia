#include <iostream>
using namespace std;

int main()
{
    // Hash<int,string> table;
    cout<<"-----------"<<endl;
    int x;
    int a, b;
    string gen;
    do
    {
        cout<<endl;
        cout << "\nMENU\n";
        cout << "1) Leer archivo e insertar datos\n";
        cout << "2) Imprimir \n";
        cout << "3) Buscar\n";
        cout << "4) Eliminar registro\n";
        cout << "5) SALIR\n";
        cout << "\nIngrese la opcion: ";
        cin >> a;
        switch (a)
        {
            case 1:
                
                break;
                
            case 5:
                cout << endl;
                cout << "\n- Seguro que quiere salir?(SI=1)(NO=0) :";
                cin >> b;
                cout << endl;
                if (b == 1)
                    a = 0;
                else if(b == 0)
                    break;
        }
    } while (a != 0);
    
}