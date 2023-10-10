#pragma once
#include <iostream>
#include "Software.h"
using namespace std;
class Juego:public Software{
    private:
    string category;
    public:
    Juego(string, string, string, int,float,string);
};
Juego::Juego(string tipo, string name, string dev, int control_edad,float price,string category) : Software(tipo,name,dev,control_edad,price){
    this ->category=category;
};