/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include <iostream>
#include <fstream>
#include <sstream>
#include "Users.h"
#include "Software.h"
#include "Juego.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

void log();
vector<Users> readUsers();
vector<Software*> softwares(vector<Users>);
bool loggin(vector<Users>);
void readMe(vector<Users>, vector<Software*>);
bool menu(Users,vector<Users>);

// Función para convertir una cadena a minúsculas
string toLowerCase(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return result;
}

int main()
{
    cout<<"Hola 2"<<endl;
    vector<Users> listUsers = readUsers();
    vector<Software*> listSofts = softwares(listUsers);
    log();
    /*for(Users s:listUsers){
        s.toString();
    }*/
    bool login=loggin(listUsers);
    int fail=0;
    string intentar;
    while(login==false){
        fail++;
        if(fail<3){
            login=loggin(listUsers);
        }
        else{
            cout<<"*** Se ha equivocado en 3 oportunidades ***"<<endl;
            cout<<"** 1) Volver a intentar \n**2) Cerrar Programa "<<endl;
            cin>>intentar;
            if(intentar=="1"){
                fail=-1;
            }
            else{
                return 0;
            }
                
            
        }
    }
    /*for(Software* x:listSofts){
        x->toString();
    }*/
    readMe(listUsers,listSofts);
    cout<<"La longitud vector: "<<listSofts.size()<<endl;
    return 0;
}

void log(){
	ofstream log;
	log.open("log.txt",ios::out);
	log<<"-Registro de cambios"<<endl<<"El usuario <x> ha instalado chrome.exe en equipo ";
	log.close();
};

void readMe(vector<Users> u, vector<Software*> s){
	ofstream readme;
	readme.open("ReadMe.txt",ios::out);
    for(Users users:u){
        readme<<(users.toString())<<endl;
    }
    for(Software* soft:s){
        readme<<(soft->toString())<<endl;
    }
	readme.close();
};

vector<Users> readUsers(){
	ifstream users;
	users.open("users.txt",ios::in);
	string line;
    vector<Users> userVector;
    while (getline(users, line)) {
        // Usamos un stringstream para dividir la l�nea en partes usando ","
        stringstream ss(line);
        string tipo, username, password, edad, email;
        int age;
        // Utilizamos getline con ',' como delimitador para separar las partes
        getline(ss, tipo, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, edad, ',');
        age= stoi(edad);
        if(tipo=="Admin" or tipo=="Normal"){
            getline(ss, email, ',');
            Users user(tipo, username, password, age, email);
            userVector.push_back(user);
        }
        else{
            Users user(tipo, username, password, age);
            userVector.push_back(user);
        }
        // Ahora puedes hacer lo que quieras con estas variables
        
    }
	users.close();
    return(userVector);
};

vector<Software*> softwares(vector<Users> u){
    ifstream softs;
	softs.open("softwares.txt",ios::in);
	string line;
    vector<Software*> s;
    while (getline(softs, line)) {
        stringstream ss(line);
        string tipo, name, dev, edad, precio, cantidad_users;
        int control_edad;
        int cant_u;
        float price;
        getline(ss, tipo, ',');
        getline(ss, name, ',');
        getline(ss, dev, ',');
        getline(ss, edad, ',');
        control_edad= stoi(edad);
        getline(ss,precio,',');
        price= stof(precio);
        if(tipo=="Juego"){
            string category,username;
            getline(ss,category,',');
            Software* soft= new Juego(tipo,name,dev,control_edad,price,category);
            getline(ss,cantidad_users,',');
            cant_u= stoi(cantidad_users);
            getline(ss,username,',');
            while(cant_u!=0){
                getline(ss,username,',');
                for(Users x:u){
                    if(x.getName()==username){
                        soft->setUsers(x);
                        cant_u--;
                        break;
                    }
                }
            }
            s.push_back(soft);   
        }
    }
    return s;
};

bool loggin(vector<Users> users){
    string username;
    string password;
    bool terminar;
    cout<<"*****************\n* Inicie Sesion *\n*****************"<<endl;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;
    for(Users s:users){
        if(toLowerCase(s.getName()) == toLowerCase(username)){
            //cout<<"Nombre de usuario valido"<<endl;
            if(s.getPassword()==password){
                //cout<<"pass correct"<<endl;
                terminar= menu(s,users);
                return(terminar);
            }
            else{
                cout<<"|/|/ Password incorrect |/|/"<<endl;
                return(false);
            }
        }
    };
    cout<<"|/|/ Username incorrect |/|/"<<endl;
    return(false);
};
bool menu(Users s,vector<Users> users){
    string option;
    cout<<"*****************************\n     Bienvenido "<<s.getName()<<"     \n*****************************"<<endl;
    cout<<"2) LogOut"<<endl;
    cin>>option;
    if(option=="2"){
        cout<<"|/|/|/|/Sesion cerrada con exito|/|/|/|/|"<<"\n1) Volver a iniciar sesion\n2) Cerrar Programa"<<endl;
        cin>>option;
        if(option=="1"){
            return(false);
        }
        else{
            return(true);
        }
        
    }
    return false;
};
/*int main(int argc, char** argv) {
	return 0;
}*/
