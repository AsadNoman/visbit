#include "simlib.h"

const int scrnsize = 800;
const int numframes = 300;

void evolve1(Entity* e){
    float prob =  ((float) rand()) / ((float) RAND_MAX);
    if (prob > *(e->fprops))
        e->fd(2);
    else if (prob > *(e->fprops + 1))
        e->bd(2);
    else if (prob > *(e->fprops + 2))
        e->up(2);
    else
        e->dn(2);

    
}


int main(){
    srand(time(NULL));

    Ground grnd(scrnsize);

    uint8_t* c1 = (uint8_t*) malloc(3);
    uint8_t* c2 = (uint8_t*) malloc(3);
    *c1 = 250; *(c1 + 1) = 30; *(c1 + 2) = 50;
    *c2 = 50; *(c2 + 1) = 30; *(c2 + 2) = 250;

    grnd.createET(2, 9, c1); //diamond
    grnd.createET(1, 4, c2); //square

    const int numcreatures = 20;
    const int numfood = 50;

    Entity* creatures[numcreatures];
    Entity* food[numfood];

    for (int i = 0; i < numcreatures; i++){ // coords between 0-200 and 600-800
        creatures[i] = new Entity(frand() < 0.5 ? (int)(frand()*200) : 600 + (int)(frand()*200), rand()%scrnsize);

        float* fprops = (float*) malloc(4); //movement probabilities
        *fprops     = frand(); //forward
        *(fprops+1) = frand() * *(fprops); //backward 
        *(fprops+2) = frand() * *(fprops+1); //up 
        *(fprops+3) = frand() * *(fprops+2); //down 

        (*creatures[i]).fprops = fprops;

    }

    for (int i = 0; i < numfood; i++) //assign random coords to food
        food[i] = new Entity(200 + (int)(frand()*400), rand()%scrnsize);

    // loop
    for (int i = 0; i < numframes; i++){
        //std::cout<<"\033[2J\033[1;1H";
        grnd.draw(creatures, numcreatures, 1);
        grnd.draw(food, numfood, 2);

        for (int j = 0; j < numcreatures; j++)
            evolve1(creatures[j]); 

        grnd.captureframe();
        grnd.clear();
    }
    
    return 0;
}
