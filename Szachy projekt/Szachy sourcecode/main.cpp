#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include <time.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace std;

class Figure;
class Field;
enum Figura{pion_b,skoczek_b,goniec_b,krolowa_b,krol_b,wieza_b,pion_c,skoczek_c,goniec_c,krolowa_c,krol_c,wieza_c};

class wektor
{
public:
    int x,y;
    bool zbicie=false;
    void define(int x_arg,int y_arg,bool zbicie_arg)
    {
        x=x_arg;
        y=y_arg;
        zbicie=zbicie_arg;
    }
};

class Field
{
public:
    int x;int y;
    int x_1;int y_1;
    Figure *figura;
    sf::Texture tex;
    sf::Sprite spr;
    sf::RectangleShape hitbox;
    Field()
    {
        sf::Vector2f hitboxsize(100,100);
        hitbox.setSize(hitboxsize);
        tex.loadFromFile("Textures/Field.png");
        spr.setTexture(tex);
    }
    void setpositions()
    {
        hitbox.setPosition(x*100,y*100);
        x_1=x*100;y_1=y*100;
        spr.setPosition(hitbox.getPosition());
    }
};

class Figure
{
public:
    int x,y;
    Figura type;
    int counter;
    bool kolor;
    bool first_move=true;
    bool temp=true;
    wektor v;
    vector<wektor>::const_iterator iter;
    vector<wektor>possible_moves;
    Field *field;
    sf::Texture tex;
    sf::Sprite spr;
    sf::RectangleShape hitbox;
    Figure(Figura type_arg,Field &field_arg)
    {
        type=type_arg;
        if(type==pion_b || type==skoczek_b || type==goniec_b || type==krol_b || type==krolowa_b || type==wieza_b) kolor=true; else kolor=false;
        field=&field_arg;
        sf::Vector2f hitboxsize(100,100);
        hitbox.setSize(hitboxsize);
        switch(type)
        {
            case pion_b: tex.loadFromFile("Textures/pion_b.png");break;
            case pion_c: tex.loadFromFile("Textures/pion_c.png");break;
            case goniec_b: tex.loadFromFile("Textures/goniec_b.png");break;
            case goniec_c: tex.loadFromFile("Textures/goniec_c.png");break;
            case skoczek_b: tex.loadFromFile("Textures/kon_b.png");break;
            case skoczek_c: tex.loadFromFile("Textures/kon_c.png");break;
            case krol_b: tex.loadFromFile("Textures/krol_b.png");break;
            case krol_c: tex.loadFromFile("Textures/krol_c.png");break;
            case krolowa_b: tex.loadFromFile("Textures/krolowa_b.png");break;
            case krolowa_c: tex.loadFromFile("Textures/krolowa_c.png");break;
            case wieza_b: tex.loadFromFile("Textures/wieza_b.png");break;
            case wieza_c: tex.loadFromFile("Textures/wieza_c.png");break;
            default: break;
        }
        field->figura=this;
        spr.setTexture(tex);
        hitbox.setPosition(field->x_1,field->y_1);
        x=field->x;
        y=field->y;
        spr.setPosition(hitbox.getPosition());
    }
    void Possible_moves_calculator(Field f[8][8])
    {
        int counter=0;
        if(type==pion_b && first_move==true/* && temp==true*/)
        {
            v.define(field->x,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL && f[v.x][v.y+1].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y-1,true); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false) possible_moves.push_back(v);
            v.define(field->x+1,field->y-1,true); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false) possible_moves.push_back(v);
            temp=false;
        }
        if(type==pion_b && first_move==false/* && temp==true*/)
        {
            v.define(field->x,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y-1,true); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false) possible_moves.push_back(v);
            v.define(field->x+1,field->y-1,true); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false) possible_moves.push_back(v);
            temp=false;
        }
        if(type==pion_c && first_move==true/* && temp==true*/)
        {
            v.define(field->x,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL && f[v.x][v.y-1].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y+1,true); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true) possible_moves.push_back(v);
            v.define(field->x+1,field->y+1,true); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true) possible_moves.push_back(v);
            temp=false;
        }
        if(type==pion_c && first_move==false/* && temp==true*/)
        {
            v.define(field->x,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y+1,true); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true) possible_moves.push_back(v);
            v.define(field->x+1,field->y+1,true); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true) possible_moves.push_back(v);
            temp=false;
        }
        if(type==skoczek_b/* && temp==true*/)
        {
            v.define(field->x-1,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-2,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-1,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-2,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+1,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+2,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+1,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+2,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            temp=false;
        }
        if(type==skoczek_c/* && temp==true*/)
        {
            v.define(field->x-1,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-2,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-1,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-2,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+1,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+2,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+1,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+2,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            temp=false;
        }
        if(type==goniec_b/* && temp==true*/)
        {
            v.define(field->x+1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+2,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL && f[v.x-5][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL && f[v.x-5][v.y+5].figura==NULL && f[v.x-6][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-2,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL && f[v.x+5][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL && f[v.x+5][v.y+5].figura==NULL && f[v.x+6][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x+1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+2,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL && f[v.x-5][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL && f[v.x-5][v.y-5].figura==NULL && f[v.x-6][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-2,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL && f[v.x+5][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL && f[v.x+5][v.y-5].figura==NULL && f[v.x+6][v.y-6].figura==NULL) possible_moves.push_back(v);
        }
        if(type==wieza_b/* && temp==true*/)
        {
            v.define(field->x,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL && f[v.x][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL && f[v.x][v.y+5].figura==NULL && f[v.x][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-2,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL && f[v.x+5][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL && f[v.x+5][v.y].figura==NULL && f[v.x+6][v.y].figura==NULL) possible_moves.push_back(v);

            v.define(field->x,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL && f[v.x][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL && f[v.x][v.y-5].figura==NULL && f[v.x][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x+1,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+2,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL && f[v.x-5][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL && f[v.x-5][v.y].figura==NULL && f[v.x-6][v.y].figura==NULL) possible_moves.push_back(v);
        }
        if(type==goniec_c/* && temp==true*/)
        {
            v.define(field->x+1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+2,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL && f[v.x-5][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL && f[v.x-5][v.y+5].figura==NULL && f[v.x-6][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-2,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL && f[v.x+5][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL && f[v.x+5][v.y+5].figura==NULL && f[v.x+6][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x+1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+2,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL && f[v.x-5][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL && f[v.x-5][v.y-5].figura==NULL && f[v.x-6][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-2,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL && f[v.x+5][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL && f[v.x+5][v.y-5].figura==NULL && f[v.x+6][v.y-6].figura==NULL) possible_moves.push_back(v);
        }
        if(type==wieza_c/* && temp==true*/)
        {
            v.define(field->x,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL && f[v.x][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL && f[v.x][v.y+5].figura==NULL && f[v.x][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-2,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL && f[v.x+5][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL && f[v.x+5][v.y].figura==NULL && f[v.x+6][v.y].figura==NULL) possible_moves.push_back(v);

            v.define(field->x,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL && f[v.x][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL && f[v.x][v.y-5].figura==NULL && f[v.x][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x+1,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+2,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL && f[v.x-5][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL && f[v.x-5][v.y].figura==NULL && f[v.x-6][v.y].figura==NULL) possible_moves.push_back(v);
        }
        if(type==krolowa_b/* && temp==true*/)
        {
            v.define(field->x+1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+2,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL && f[v.x-5][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL && f[v.x-5][v.y+5].figura==NULL && f[v.x-6][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-2,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL && f[v.x+5][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL && f[v.x+5][v.y+5].figura==NULL && f[v.x+6][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x+1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+2,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL && f[v.x-5][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL && f[v.x-5][v.y-5].figura==NULL && f[v.x-6][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-2,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL && f[v.x+5][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL && f[v.x+5][v.y-5].figura==NULL && f[v.x+6][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL && f[v.x][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL && f[v.x][v.y+5].figura==NULL && f[v.x][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-2,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL && f[v.x+5][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL && f[v.x+5][v.y].figura==NULL && f[v.x+6][v.y].figura==NULL) possible_moves.push_back(v);

            v.define(field->x,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL && f[v.x][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL && f[v.x][v.y-5].figura==NULL && f[v.x][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x+1,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+2,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL && f[v.x-5][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL && f[v.x-5][v.y].figura==NULL && f[v.x-6][v.y].figura==NULL) possible_moves.push_back(v);
        }
        if(type==krolowa_c)
        {
            v.define(field->x+1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+2,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL && f[v.x-5][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y+1].figura==NULL && f[v.x-2][v.y+2].figura==NULL && f[v.x-3][v.y+3].figura==NULL && f[v.x-4][v.y+4].figura==NULL && f[v.x-5][v.y+5].figura==NULL && f[v.x-6][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-2,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL && f[v.x+5][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y+1].figura==NULL && f[v.x+2][v.y+2].figura==NULL && f[v.x+3][v.y+3].figura==NULL && f[v.x+4][v.y+4].figura==NULL && f[v.x+5][v.y+5].figura==NULL && f[v.x+6][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x+1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+2,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL && f[v.x-5][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y-1].figura==NULL && f[v.x-2][v.y-2].figura==NULL && f[v.x-3][v.y-3].figura==NULL && f[v.x-4][v.y-4].figura==NULL && f[v.x-5][v.y-5].figura==NULL && f[v.x-6][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-2,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL && f[v.x+5][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y-1].figura==NULL && f[v.x+2][v.y-2].figura==NULL && f[v.x+3][v.y-3].figura==NULL && f[v.x+4][v.y-4].figura==NULL && f[v.x+5][v.y-5].figura==NULL && f[v.x+6][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x,field->y-2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL && f[v.x][v.y+5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y-7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y+1].figura==NULL && f[v.x][v.y+2].figura==NULL && f[v.x][v.y+3].figura==NULL && f[v.x][v.y+4].figura==NULL && f[v.x][v.y+5].figura==NULL && f[v.x][v.y+6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x-1,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-2,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-3,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-4,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-5,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-6,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL && f[v.x+5][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x-7,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x+1][v.y].figura==NULL && f[v.x+2][v.y].figura==NULL && f[v.x+3][v.y].figura==NULL && f[v.x+4][v.y].figura==NULL && f[v.x+5][v.y].figura==NULL && f[v.x+6][v.y].figura==NULL) possible_moves.push_back(v);

            v.define(field->x,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x,field->y+2,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+3,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+4,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+5,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+6,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL && f[v.x][v.y-5].figura==NULL) possible_moves.push_back(v);
            v.define(field->x,field->y+7,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x][v.y-1].figura==NULL && f[v.x][v.y-2].figura==NULL && f[v.x][v.y-3].figura==NULL && f[v.x][v.y-4].figura==NULL && f[v.x][v.y-5].figura==NULL && f[v.x][v.y-6].figura==NULL) possible_moves.push_back(v);

            v.define(field->x+1,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+2,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+3,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+4,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+5,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+6,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL && f[v.x-5][v.y].figura==NULL) possible_moves.push_back(v);
            v.define(field->x+7,field->y,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) if(f[v.x-1][v.y].figura==NULL && f[v.x-2][v.y].figura==NULL && f[v.x-3][v.y].figura==NULL && f[v.x-4][v.y].figura==NULL && f[v.x-5][v.y].figura==NULL && f[v.x-6][v.y].figura==NULL) possible_moves.push_back(v);
        }
        if(type==krol_b)
        {
            /*v.define(field->x,field->y-1,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) for(int i=0;i<7;i++) for(int j=0;j<7;j++) {if(f[i][j].figura!=NULL){counter=0; for(f[i][j].figura->possible_moves.begin();f[i][j].figura->iter!=f[i][j].figura->possible_moves.end();f[i][j].figura->iter++) {if(f[i][j].figura->possible_moves[counter].x!=v.x && f[i][j].figura->possible_moves[counter].y!=v.y) possible_moves.push_back(v);counter++;}}}
            v.define(field->x+1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) for(int i=0;i<7;i++) for(int j=0;j<7;j++) {if(f[i][j].figura!=NULL){counter=0; for(f[i][j].figura->possible_moves.begin();f[i][j].figura->iter!=f[i][j].figura->possible_moves.end();f[i][j].figura->iter++) {if(f[i][j].figura->possible_moves[counter].x!=v.x && f[i][j].figura->possible_moves[counter].y!=v.y) possible_moves.push_back(v);counter++;}}}
            v.define(field->x-1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) for(int i=0;i<7;i++) for(int j=0;j<7;j++) {if(f[i][j].figura!=NULL){counter=0; for(f[i][j].figura->possible_moves.begin();f[i][j].figura->iter!=f[i][j].figura->possible_moves.end();f[i][j].figura->iter++) {if(f[i][j].figura->possible_moves[counter].x!=v.x && f[i][j].figura->possible_moves[counter].y!=v.y) possible_moves.push_back(v);counter++;}}}
            v.define(field->x+1,field->y,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) for(int i=0;i<7;i++) for(int j=0;j<7;j++) {if(f[i][j].figura!=NULL){counter=0; for(f[i][j].figura->possible_moves.begin();f[i][j].figura->iter!=f[i][j].figura->possible_moves.end();f[i][j].figura->iter++) {if(f[i][j].figura->possible_moves[counter].x!=v.x && f[i][j].figura->possible_moves[counter].y!=v.y) possible_moves.push_back(v);counter++;}}}
            v.define(field->x-1,field->y,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) for(int i=0;i<7;i++) for(int j=0;j<7;j++) {if(f[i][j].figura!=NULL){counter=0; for(f[i][j].figura->possible_moves.begin();f[i][j].figura->iter!=f[i][j].figura->possible_moves.end();f[i][j].figura->iter++) {if(f[i][j].figura->possible_moves[counter].x!=v.x && f[i][j].figura->possible_moves[counter].y!=v.y) possible_moves.push_back(v);counter++;}}}
            v.define(field->x,field->y+1,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) for(int i=0;i<7;i++) for(int j=0;j<7;j++) {if(f[i][j].figura!=NULL){counter=0; for(f[i][j].figura->possible_moves.begin();f[i][j].figura->iter!=f[i][j].figura->possible_moves.end();f[i][j].figura->iter++) {if(f[i][j].figura->possible_moves[counter].x!=v.x && f[i][j].figura->possible_moves[counter].y!=v.y) possible_moves.push_back(v);counter++;}}}
            v.define(field->x-1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) for(int i=0;i<7;i++) for(int j=0;j<7;j++) {if(f[i][j].figura!=NULL){counter=0; for(f[i][j].figura->possible_moves.begin();f[i][j].figura->iter!=f[i][j].figura->possible_moves.end();f[i][j].figura->iter++) {if(f[i][j].figura->possible_moves[counter].x!=v.x && f[i][j].figura->possible_moves[counter].y!=v.y) possible_moves.push_back(v);counter++;}}}
            v.define(field->x+1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) for(int i=0;i<7;i++) for(int j=0;j<7;j++) {if(f[i][j].figura!=NULL){counter=0; for(f[i][j].figura->possible_moves.begin();f[i][j].figura->iter!=f[i][j].figura->possible_moves.end();f[i][j].figura->iter++) {if(f[i][j].figura->possible_moves[counter].x!=v.x && f[i][j].figura->possible_moves[counter].y!=v.y) possible_moves.push_back(v);counter++;}}}*/
            v.define(field->x,field->y-1,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+1,field->y,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-1,field->y,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x,field->y+1,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x-1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
            v.define(field->x+1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==false)) possible_moves.push_back(v);
        }
        if(type==krol_c)
        {
            v.define(field->x,field->y-1,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-1,field->y-1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+1,field->y,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-1,field->y,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x,field->y+1,false);   if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x-1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
            v.define(field->x+1,field->y+1,false); if(v.x>=0 && v.x<=7 && v.y>=0 && v.y<=7) if(f[v.x][v.y].figura==NULL || (f[v.x][v.y].figura!=NULL && f[v.x][v.y].figura->kolor==true)) possible_moves.push_back(v);
        }
    }
    void clear_vector()
    {
        possible_moves.clear();
    }
};

int main()
{
    int counter;
    bool tura=true;
    Field f[8][8];
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            f[i][j].figura=NULL;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
           {f[i][j].x=i; f[i][j].y=j;}
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
           {f[i][j].setpositions();}

    Figure figura[32]={Figure(wieza_c,f[0][0]),Figure(skoczek_c,f[1][0]),Figure(goniec_c,f[2][0]),Figure(krolowa_c,f[3][0]),Figure(krol_c,f[4][0]),Figure(goniec_c,f[5][0]),Figure(skoczek_c,f[6][0]),Figure(wieza_c,f[7][0]),
                       Figure(pion_c,f[0][1]), Figure(pion_c,f[1][1]),   Figure(pion_c,f[2][1]),  Figure(pion_c,f[3][1]),   Figure(pion_c,f[4][1]),Figure(pion_c,f[5][1]),  Figure(pion_c,f[6][1]),  Figure(pion_c,f[7][1]),
                       Figure(pion_b,f[0][6]), Figure(pion_b,f[1][6]),   Figure(pion_b,f[2][6]),  Figure(pion_b,f[3][6]),   Figure(pion_b,f[4][6]),Figure(pion_b,f[5][6]),  Figure(pion_b,f[6][6]),  Figure(pion_b,f[7][6]),
                       Figure(wieza_b,f[0][7]),Figure(skoczek_b,f[1][7]),Figure(goniec_b,f[2][7]),Figure(krolowa_b,f[3][7]),Figure(krol_b,f[4][7]),Figure(goniec_b,f[5][7]),Figure(skoczek_b,f[6][7]),Figure(wieza_b,f[7][7])};

    Figure *active;
    active=NULL;

    sf::Vector2i mousePosition;
    sf::RectangleShape mouseHitbox;
    mouseHitbox.setSize(sf::Vector2f(1,1));

    sf::RenderWindow window(sf::VideoMode(800,800),"Szachy");
    while(window.isOpen())
    {
        mousePosition=sf::Mouse::getPosition(window);
        mouseHitbox.setPosition(mousePosition.x,mousePosition.y);

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                 window.close();
        }

        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                {
                    if(f[i][j].figura!=NULL) f[i][j].figura->Possible_moves_calculator(f);
                    /*if(f[i][j].figura!=NULL)
                    {
                        for(unsigned k=0;k<f[i][j].figura->possible_moves.size();k++)
                            if(f[i][j].figura->type==skoczek_b) cout<<f[i][j].figura->possible_moves[k].x<<" "<<f[i][j].figura->possible_moves[k].y<<endl;
                    }*/
                }

        if(tura==true)
        {
            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++)
                    if(mouseHitbox.getGlobalBounds().intersects(f[i][j].hitbox.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && f[i][j].figura!=NULL && f[i][j].figura->kolor==true)
                    {
                        active=f[i][j].figura;
                    }
        }
        else
        {
            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++)
                    if(mouseHitbox.getGlobalBounds().intersects(f[i][j].hitbox.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && f[i][j].figura!=NULL && f[i][j].figura->kolor==false)
                    {
                        active=f[i][j].figura;
                    }
        }

        if(active!=NULL)
        {
            counter=0;
            for(active->iter=active->possible_moves.begin();active->iter!=active->possible_moves.end();active->iter++)
            {
                if(mouseHitbox.getGlobalBounds().intersects(f[active->possible_moves[counter].x][active->possible_moves[counter].y].hitbox.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //if(active->possible_moves[counter].zbicie==true){f[active->possible_moves[counter].x][active->possible_moves[counter].y].figura=NULL;}
                    f[active->x][active->y].figura=NULL;
                    active->x=active->possible_moves[counter].x;
                    active->y=active->possible_moves[counter].y;
                    active->field=&f[active->possible_moves[counter].x][active->possible_moves[counter].y];
                    f[active->possible_moves[counter].x][active->possible_moves[counter].y].figura=active;
                    f[active->possible_moves[counter].x][active->possible_moves[counter].y].figura->hitbox.setPosition(f[active->possible_moves[counter].x][active->possible_moves[counter].y].x,f[active->possible_moves[counter].x][active->possible_moves[counter].y].y);
                    f[active->possible_moves[counter].x][active->possible_moves[counter].y].figura->first_move=false;
                    f[active->possible_moves[counter].x][active->possible_moves[counter].y].figura->spr.setPosition(f[active->possible_moves[counter].x][active->possible_moves[counter].y].hitbox.getPosition());
                    if(tura==true){tura=false;} else if(tura==false){tura=true;}
                    active=NULL;
                    break;
                }
                counter++;
            }
        }

        window.clear();
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                {
                    if(f[i][j].figura==NULL) window.draw(f[i][j].spr);
                    if(f[i][j].figura!=NULL) window.draw(f[i][j].figura->spr);
                }
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(f[i][j].figura!=NULL) f[i][j].figura->clear_vector();
        window.display();
    }
    return 0;
}
