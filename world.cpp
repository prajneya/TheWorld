#include<bits/stdc++.h>
using namespace std;

int n = 30;

struct gene{
    int x1;
    int y1;
};

struct animal{
    char a;
    gene dna;
    int energy;
};

animal world[30][30]; //world size

animal temp; //default world element

void move(animal a, int placerx, int placery);

void printW(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << world[i][j].a << " ";
        }
        cout << endl;
    }
}


//Initiating the World
void setW(){
    temp.a = '0';
    temp.energy = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            world[i][j] = temp;
        }
    }

}

//Drops food whenever called
void dropFood(){
    int xcor = rand() % 30;
    int ycor = rand() % 30;
    world[xcor][ycor].energy++;
}

//Asexual Reproduction
void reproduce(animal a, int xcor, int ycor){
    if(a.energy>5){
        //No existence of parent
        world[xcor][ycor] = temp;

        //Two daughters
        animal childa, childb;

        static int movem[] = {-1,  1, 0};

        //First Child is Born
        int movex = rand() % 3;
        int movey = rand() % 3;
        while(xcor+movem[movex]<0 || xcor+movem[movex]>=n || ycor+movem[movey]<0 || ycor+movem[movey]>=n || (movem[movey]==0 && movem[movex]==0)){
            movex = rand() % 3;
            movey = rand() % 3;
        }

        childa.a = a.a+1;
        childa.energy = a.energy/2;
        world[xcor+movem[movex]][ycor+movem[movey]] = childa;

        //Second Child is Born
        int movex2 = rand() % 3;
        int movey2 = rand() % 3;
        while(xcor+movem[movex2]<0 || xcor+movem[movex2]>=n || ycor+movem[movey2]<0 || ycor+movem[movey2]>=n || (movem[movey2]==0 && movem[movex2]==0) || (movex==movex2 && movey==movey2)){
            movex2 = rand() % 3;
            movey2 = rand() % 3;
        }

        childb.a = a.a+2;
        childb.energy = a.energy/2;
        world[xcor+movem[movex2]][ycor+movem[movey2]] = childb;

        //Both daughters start moving
        move(childa, xcor+movem[movex], ycor+movem[movey]);
        move(childb, xcor+movem[movex2], ycor+movem[movey2]);

        //Change World Map
        _sleep(100);
        system("cls");
        _sleep(100);
        printW();
    }
    else{
        return;
    }
}

//World Processes takes place
void move(animal a, int placerx, int placery){
    //Check Kill Switch of Animal
    if(a.energy<=0){
        world[placerx][placery] = temp;
        return;
    }

    //Movement Process
    static int movem[] = {-1,  1, 0};
    int movex = rand() % 3;
    int movey = rand() % 3;
    while(placerx+movem[movex]<0 || placerx+movem[movex]>=n || placery+movem[movey]<0 || placery+movem[movey]>=n || (movem[movey]==0 && movem[movex]==0)){
        movex = rand() % 3;
        movey = rand() % 3;
    }
    //Animal leaves old cell
    world[placerx][placery] = temp;
    //Animal enters new cell
    world[placerx+movem[movex]][placery+movem[movey]] = a;
    //Eats Food
    a.energy+=world[placerx+movem[movex]][placery+movem[movey]].energy;
    //Food is eaten
    world[placerx+movem[movex]][placery+movem[movey]].energy = 0;
    //Energy Lost in Movement
    a.energy--;
    //Updating coordinates
    placerx += movem[movex];
    placery += movem[movey];

    //Change the World Map
    _sleep(100);
    system("cls");
    _sleep(100);
    printW();

    //Check if Animal can Reproduce
    reproduce(a, placerx, placery);



    //Drop Food again
    dropFood();

    //Move Again
    move(a, placerx, placery);
}

int main(){

    //Initializing the world
    setW();
    bool running = true;

    //Initializing the place of Adam
    int placerx = rand() % 10;
    int placery = rand() % 10;

    //Creating Adam
    animal adam;
    adam.a = 'A';
    adam.energy = 10;
    //Placing Adam and first Food
    world[placerx][placery] = adam;
    dropFood();

    //BIG BANG
    printW();


    //Game starts here -->> (ADAM STARTS LIVING)
    move(adam, placerx, placery);
}
