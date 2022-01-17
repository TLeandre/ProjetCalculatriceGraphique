#include<math.h>
#include<stdio.h>

void echelon(float deb, float fin, float pas, float tab[]){

    int val = (fin-deb)/pas; 

    float x = deb;
    
    for( int i = 0; i <= val; i++){
        tab[i] = x;
        x += pas; 
    }

}

void main(){
    float deb = 0;
    float fin = 10;
    float pas = 0.1;
    int val = (fin-deb)/pas; 
    float tab[val];

    echellon(deb, fin, pas, tab);

    for( int i = 0; i <= val; i++){
        printf("%f\n", tab[i]);
    }






    
}
