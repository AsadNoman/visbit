#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<fstream>
#include<math.h>

using namespace std;
//shape  = 1 for square, 2 for diamond
//size   = integer     , odd integer
//color  = assign rgb using malloc uint8_t
//iprops = extra integer properties (array, if many)
//fprops = extra float properties (array, if many)

class EntityType{
    public:
        int shape;
        int size;
        uint8_t* color;

        EntityType(int _shape, int _size, uint8_t* _c); 

        ~EntityType();

};

class Entity{
    public:
        int x = 0, y = 0;
        int* iprops;
        float* fprops;

        Entity(int _x, int _y);

        ~Entity();

        void fd(int step);

        void bd(int step);

        void up(int step);

        void dn(int step);

        void assign_iprops(int* _iprops);

        void assign_fprops(float* _fprops);
};

class Ground{
    private:
        uint8_t* frame2d;
        int size;
        EntityType* et[10];
        int numET = 0;
        int capture_count = 0;

    public:
        Ground(int _size);

        ~Ground();

        void createET(int _shape, int _size, uint8_t* _c);
        
        void clear();

        uint8_t* ptrxy(int x, int y, int pxsize);

        int validate_limit(int x, int y, int _size);

        void dot(int x, int y, int entity_num);

        void square(int x, int y, int _sz, int entity_num);

        void diamond(int x, int y, int _sz, int entity_num);


        void draw(Entity** elist, int num, int etnum);

        void captureframe();
        
};


float frand();

