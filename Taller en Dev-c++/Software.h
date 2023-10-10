#pragma once
#include <iostream>
#include <vector>
#include "Users.h"
using namespace std;
class Software{
	private:
		string tipo, name, dev;
		int control_edad;
		vector<Users> users_software;
		float price;

	public:
	Software(string, string, string, int, float);
	void setUsers(Users);
	string toString();
};

Software::Software(string tipo, string name, string dev, int control_edad,float price){
	this -> tipo= tipo;
	this -> name= name;
	this -> dev= dev;
	this -> control_edad= control_edad;
	
}
void Software::setUsers(Users user){
	users_software.push_back(user);
}
string Software::toString(){
	return("Tipo: "+tipo+" Nombre: "+name);
}
