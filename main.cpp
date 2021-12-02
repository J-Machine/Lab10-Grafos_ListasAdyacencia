#include <bits/stdc++.h>
#include <string>

using namespace std;

template<class V, class E>  
class Edge;                 // prototipo declarado aqui para evitar error al usarlo en Vertex

template<class V, class E>
class Vertex //Clase vertice
{
    public:
        V m_Dato; //Nombre del vertice
        list< Edge <V,E> > m_Aristas; //Lista de objetos aristas que tienen un puntero a otro vertice
    public:
       Vertex(V d):m_Dato{d}{}
       Vertex(){}
       ~Vertex(){}
};

template<class V, class E>
class Edge { //Clase arista 
    public:
        E m_Dato; //Nombre de arista
        Vertex<V,E> * m_pVertex; //Puntero a otro vertice
    public:
        Edge(E name , Vertex<V,E> * p = 0):m_Dato{name} , m_pVertex{p}{}
        Edge(){}
        ~Edge(){
            m_pVertex = 0;
        }
    
};

template<class V, class E>
class Grafo 
{
    private: 
        list<Vertex<V,E>> m_Grafo;
    public:
        Grafo(){}
        /////////////////////CREAR GRAFO////////////////////////        
        void crearGrafo() 
        {
            if(!m_Grafo.empty()) m_Grafo.clear();
            cout<<"Grafo Vacio Creado";
        }
        /////////////////////INSERTAR NODO//////////////////////// 
        void insertarNodo(V valor) 
        {
            Vertex<V,E> newNodo(valor);
            if (!existeNodo(newNodo))
                m_Grafo.push_back(newNodo);
            else
                cout << "No se insertó. El nodo ya existe\n";
        }
        /////////////////////INSERTAR ARISTA//////////////////////// 
        void insertarArista(V a ,V b,E arista) 
        {
            Vertex<V,E> * p  =  existeNodo(a);
            Vertex<V,E> * q  =  existeNodo(b);
            if(p && q){
                p->m_Aristas.push_back(Edge<V,E>(arista,q));
                q->m_Aristas.push_back(Edge<V,E>(arista,p));
            }else if(!p)
            {
                insertarNodo(a);
                p = existeNodo(a);
                p->m_Aristas.push_back(Edge<V,E>(arista,q));
                q->m_Aristas.push_back(Edge<V,E>(arista,p));
            }else{
                insertarNodo(b);
                q = existeNodo(b);
                p->m_Aristas.push_back(Edge<V,E>(arista,q));
                q->m_Aristas.push_back(Edge<V,E>(arista,p));
            }
        }
        /////////////////////BORRAR NODO//////////////////////// 
        void borrarNodo(V x) // si se borra un nodo, se borran las aristas vinculadas -> Jenny
        {
                for(auto it =  m_Grafo.begin(); it != m_Grafo.end() ; it++)
                {
                    if((*it).m_Dato == x) 
                    {
                        for(auto it_2 = (*it).m_Aristas.begin() ; it_2 != (*it).m_Aristas.end() ; ++it_2)
                        {
                            for(auto iman =  m_Grafo.begin(); iman != m_Grafo.end() ; iman++)
                            {
                                if((*iman).m_Dato == (*it_2).m_pVertex->m_Dato) 
                                {
                                    for(auto it_3 = (*iman).m_Aristas.begin() ; it_3 != (*iman).m_Aristas.end() ; ++it_3)
                                    { 
                                            if((*it_3).m_pVertex->m_Dato == x)  {
                                                it_3 = (*iman).m_Aristas.erase(it_3);
                                                break;
                                            }

                                    }
                                    break;
                                }
                            }
                            it_2 = (*it).m_Aristas.erase(it_2);
                        }
                        it  = m_Grafo.erase(it);
                        return;
                    }
                }
                cout<<endl;
        }
        /////////////////////BORRAR ARISTA//////////////////////// 
        void borrarArista(V  a , V  b) 
        {
            Vertex<V,E> * p  =  existeNodo(a);
            Vertex<V,E> * q  =  existeNodo(b);
            if(p && q)
            {
                for(auto it_3 = p->m_Aristas.begin() ; it_3 != p->m_Aristas.end(); it_3++)
                {
                    if((*it_3).m_pVertex->m_Dato == b)  {
                        it_3 = p->m_Aristas.erase(it_3);
                        break;
                    }
                }

                for(auto it_4 = q->m_Aristas.begin() ; it_4 != q->m_Aristas.end(); it_4++)
                {
                    if((*it_4).m_pVertex->m_Dato == a)  {
                        it_4 = p->m_Aristas.erase(it_4);
                        break;
                    }
                }
            }
        }
        /////////////////////ES VACIO//////////////////////// 
        bool esVacio()
        {
            if(m_Grafo.empty()) 
                return true;
            return false;
            
        }
        /////////////////////EXISTE NODO//////////////////////// 
        bool existeNodo(Vertex<V,E>  p)
        {
            for(auto it = m_Grafo.begin() ; it != m_Grafo.end() ; it++)
            {
                if((*it).m_Dato == p.m_Dato) return true;
            }
            return false;
        }

        Vertex<V,E> * existeNodo( V p )
        {
            for(auto it =  m_Grafo.begin(); it != m_Grafo.end() ; it++)
            {
                if((*it).m_Dato == p) return &(*it); 
            }
        }

        /////////////////////SON ADYACENTES//////////////////////// 
        bool sonAdyacentes(V  a,V b) // si existe una arista entre 2 nodos
        {
            for(auto it = m_Grafo.begin() ; it != m_Grafo.end() ; it++)
            {
                if((*it).m_Dato==a){

                    for(auto it_2 = (*it).m_Aristas.begin() ; it_2 != (*it).m_Aristas.end() ; ++it_2)
                    {
                        if((*it_2).m_pVertex->m_Dato==b){
                            return true;
                        }
                    }  
                    return false;  
                }
            }
        }
        /////////////////////VER ADYACENCIAS//////////////////////// 
        void verAdyacencia() // Imprime matriz o lista de adyacencias
        {
            for(auto it = m_Grafo.begin() ; it != m_Grafo.end() ; it++)
            {
                cout<<(*it).m_Dato<<"->";
                for(auto it_2 = (*it).m_Aristas.begin() ; it_2 != (*it).m_Aristas.end() ; ++it_2)
                {
                    cout<<(*it_2).m_pVertex->m_Dato<<"("<<(*it_2).m_Dato<<")->";
                }
                cout<<endl;
            }
        }

        /////////////////////GRAFICAR GRAFO//////////////////////// 
        void graficar()
        {
            ofstream arch;
            arch.open("grafo_adyacencia.dot");
            if(arch.is_open()){
                arch<<"strict graph A { \n";
                for(auto it = m_Grafo.begin() ; it != m_Grafo.end() ; it++)
                {
                    arch<<(*it).m_Dato<<endl;
                    for(auto it_2 = (*it).m_Aristas.begin() ; it_2 != (*it).m_Aristas.end() ; ++it_2)
                    {
                        arch<<(*it).m_Dato<<"--"<<(*it_2).m_pVertex->m_Dato<<"[label="<<(*it_2).m_Dato<<"]"<<endl;
                    }
                }
                arch<<"}\n";
                arch.close();
                system("dot -Tpng grafo_adyacencia.dot -o grafo_adyacencia.png ");
            }else {
                cout<<"error al crear archivo";
            }
        }

};

int main() 
{
   Grafo<string, int> G;
   /////// Zona de Pruebas //////////
   G.crearGrafo();
   G.insertarNodo("Arequipa");
   G.insertarNodo("Lima");
   G.insertarNodo("Cuzco");
   G.insertarNodo("Puno");
   G.insertarNodo("Ica");
   G.insertarArista("Arequipa","Cuzco",250);
   G.insertarArista("Arequipa","Puno",200);
   G.insertarArista("Lima","Ica",100);
   G.insertarArista("Lima","Arequipa",160);
   cout<<(G.sonAdyacentes("Lima","Ica") ? "Adyacentes" : "No Adyacentes") << endl;
   cout<<(G.esVacio() ? "El grafo esta vacio" : "El grafo no esta vacio") << endl;
   G.borrarArista("Arequipa","Cuzco");
   G.verAdyacencia();
   //G.graficar();
   /////////////// Fin Zona de Pruebas //////////////

    cout<<"-----------"<<endl;
    
    string r, s;
    string ciud;
    string v1, v2;
    string vErase;
    string nodo_ciud;
    int a,b;
    do
    {
        cout<<endl;
        cout << "\nMENU\n";
        cout << "1) Crear grafo\n"; // grafo vacío
        cout << "2) Insertar nodo \n";
        cout << "3) Insertar arista \n";
        cout << "4) Borrar nodo \n";
        cout << "5) Comprobar si grafo está vacío \n";
        cout << "6) Comprobar si existe nodo \n";
        cout << "7) Comprobar si 2 nodos son adyacentes \n";
        cout << "8) Ver adyacencias \n";
        cout << "9) Graficar grafo \n";
        cout << "10) SALIR\n";
        cout << "\nIngrese la opcion: ";
        cin >> a;
        switch (a)
        {
            case 1:
                G.crearGrafo();
                cout <<"- Se creó el grafo vacío\n";
                break;
            case 2:
                
                cout << "- Inserte el valor del vértice:"; // string
                cin >> ciud;
                G.insertarNodo(ciud);
                break;
            case 3: // Insertar arista
                
                cout <<"- Ingrese primer vertice: "; cin>>v1;
                cout <<"- Ingrese segundo vertice: ";cin>>v2;
                int e;
                cout << "- Inserte el valor de la arista: "; // int
                cin>>e;
                G.insertarArista(v1, v2, e);
                break;
            case 4:
                
                cout << "- Ingrese el valor de vertice a eliminar: "; // string
                cin>>vErase;
                G.borrarNodo(vErase);
                break;
            case 5:
                cout << (G.esVacio()) ? "- El grafo está vacío\n" :"- El grafo no está vacío\n" ;
                break;
            case 6: // Existe nodo
                cout << "- Ingrese el valor de nodo a comprobar: "; cin >>nodo_ciud;
                cout << G.existeNodo(nodo_ciud) ? "- Si existe\n" :"- No existe\n" ;
                break;
            case 7:
                cout<<"- Ingrese primer vertice: ";cin>>r;
                cout<<"- Ingrese segundo vertice: ";cin>>s;
                cout<<(G.sonAdyacentes(r,s) ? "* Son adyacentes" : "* No son a7dyacentes") << endl;
                break;
            case 8:
                cout<<"LISTAS DE ADYACENCIA";cin>>r;
                G.verAdyacencia();               
                break;
            case 9:
                G.graficar();
                break;
            case 10:
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
    
    return 0;
}