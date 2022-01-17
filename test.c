float fonction(float x){
    float a = 1;
    float b = 1;
    float c = 0;
    return a*x*x+b*+c
}

void Draw(){
    float tab[10] = {1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F};
    for(int i = 1; i < 10; i++){
        line(tab[i-1],fonction(tab[i-1]),tab[i],fonction(tab[i]))
    }
    
}