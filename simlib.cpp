#include "simlib.h"

EntityType::EntityType(int _shape, int _size, uint8_t* _c): 
    shape(_shape), size(_size), color(_c){ }

EntityType::~EntityType(){
    free(color);
}


Entity::Entity(int _x, int _y): x(_x), y(_y){ }

Entity::~Entity(){
    free(iprops);
    free(fprops);
}

void Entity::fd(int step){
    x = x + step; 
}

void Entity::bd(int step){
    x = x - step; 
}

void Entity::up(int step){
    y = y - step; 
}

void Entity::dn(int step){
    y = y + step; 
}

void Entity::assign_iprops(int* _iprops){
    iprops = _iprops;
}

void Entity::assign_fprops(float* _fprops){
    fprops = _fprops;
}

Ground::Ground(int _size){
    size = _size;
    frame2d = (uint8_t*) malloc(size*size);
    clear();
}

Ground::~Ground(){
    free(frame2d);
}

void Ground::createET(int _shape, int _size, uint8_t* _c){
    et[numET] = new EntityType(_shape, _size, _c);
    numET++;
}
        
void Ground::clear(){
    uint8_t* ptr = frame2d;
    for (uint8_t* b = ptr; b < ptr + size*size; b++)
        *b = 0;
}

uint8_t* Ground::ptrxy(int x, int y, int pxsize){
    return frame2d + y*size*pxsize + x*pxsize;
}

int Ground::validate_limit(int x, int y, int _size){
    int j = x;
    if (y > j)
        j = y;

    int k = x;
    if (y < k)
        k = y;

    if (j + _size >= size || k < 0)
        return 0; 

    return _size;
}

void Ground::dot(int x, int y, int entity_num){
    uint8_t* ptr = ptrxy(x, y, 1);
    *ptr = entity_num;
}

void Ground::square(int x, int y, int _sz, int entity_num){
    int _size = validate_limit(x, y, _sz);
    if (_size == 0)
        return;

    uint8_t* ptr = ptrxy(x, y, 1);

    for (uint8_t* yptr = ptr; yptr < ptr + size*_size; yptr += size)
        for (uint8_t* xptr = yptr; xptr < yptr + _size; xptr++)
            *xptr = entity_num;
}

void Ground::diamond(int x, int y, int _sz, int entity_num){
    int _size = validate_limit(x, y, _sz);
    if (_size == 0)
        return;

    uint8_t* ptr = ptrxy(x, y, 1); 
    uint8_t k = 0;

    for (uint8_t* yptr = ptr; yptr < ptr + size*_size; yptr += size){
        if (yptr < ptr + (_size -1)*size/2){
            for (uint8_t* xptr = yptr; xptr < yptr + _size; xptr++)
                if (xptr > yptr + (_size-1)/2 - k && xptr < yptr + _size -1 - (_size - 1)/2 + k)
                    *xptr = entity_num;
            k++;
        }
        else
        {
            for (uint8_t* xptr = yptr; xptr < yptr + _size; xptr++)
                if (xptr > yptr + (_size-1)/2 - k && xptr < yptr + _size -1 - (_size - 1)/2 + k)
                    *xptr = entity_num;
            k--;
        }
    }
}


void Ground::draw(Entity** elist, int num, int etnum){
    if ((*et[etnum-1]).shape == 1)
        for (int i = 0; i < num; i++)
            square((*elist[i]).x, (*elist[i]).y, (*et[etnum-1]).size, etnum);
    else if ((*et[etnum-1]).shape == 2)
        for (int i = 0; i < num; i++)
            diamond((*elist[i]).x, (*elist[i]).y, (*et[etnum-1]).size, etnum);
}

void Ground::captureframe(){
    uint8_t* cframe = (uint8_t*) malloc(3*size*size);

    uint8_t* cptr = cframe;
    uint8_t* ptr = frame2d;
    for (uint8_t* b = ptr; b < ptr + size*size; b++){
        if (*b == 0){
            *cptr = 0; cptr++;
            *cptr = 0; cptr++;
            *cptr = 0; cptr++;
        }
        else
        {
            *cptr = *(et[*b-1]->color + 0); cptr++;
            *cptr = *(et[*b-1]->color + 1); cptr++;
            *cptr = *(et[*b-1]->color + 2); cptr++;
        }
    }

    char fname[] = "frames/frame000000.ppm";
    int n = capture_count;
    for (int i = 17; i >= 12; i--){
        fname[i] = (char) (n%10 + 48);
        n /= 10;
    }

    ofstream imgf;
    imgf.open(fname, ios::out | ios::binary);
            
    imgf<<"P6\n";
    imgf<<size<<' '<<size<<'\n';
    imgf<<"255\n";
    imgf.write((char*) cframe, size*size*3);

    free(cframe);
    capture_count++;
}

float frand(){
    return ((float) rand()) / ((float) RAND_MAX); 
}


