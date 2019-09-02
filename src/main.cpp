#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <chrono>
#include <iomanip>
#include "math.h"

#include "rectangle.hpp"

using namespace std::chrono;

struct System {
  double w ;
  double h ;
  double mu_d;
};

struct Temp{
  double dt;
  int print_freq;
  int max_iter;
  int n;
};


void readInput(System &st, Temp &tmp, std::vector<Rectangle> &lClass ){
    double m, wr, hr, x, y, vx, vy;
    double dt, print_freq, max_iter;
    int n;
    
    std::cin >> st.w;  
    std::cin >> st.h;
    std::cin >> st.mu_d;

    std::cin >> tmp.n;
    for(int i = 0; i < tmp.n; ++i){
        std::cin >> m;
        std::cin >> wr;
        std::cin >> hr;
        std::cin >> x ;
        std::cin >> y;
        std::cin >> vx;
        std::cin >> vy;
        lClass.push_back(Rectangle(m, wr, hr, x, y, vx, vy));
    }
    
    std::cin >> tmp.dt; 
    std::cin >> tmp.print_freq; 
    std::cin >> tmp.max_iter;
    
    if(!std::cin.eof())
        throw "Invalid File Format Data\n"; 
}


void printState(std::vector<Rectangle> lClass, int itr){
    std::cout << itr << std::endl;

    
    for(auto e: lClass)
        std::cout << e.x  << " "
                  << e.y  << " "
                  << e.vx << " "
                  << e.vy 
                  << "\n--------"
                  <<std::endl;
}

int main(int argc, const char *argv[]){
    //std::cout << std::fixed;
    //std::cout << std::setprecision(2);
    
    System st;
    Temp   tmp;

    bool collision = false;
    bool wall = false;
    
    std::vector<Rectangle> lClass;
    std::vector<std::pair<double, double>> new_position;

    auto timeStart = high_resolution_clock::now(); 

    //Read input 
    try{readInput(st, tmp, lClass);}
    catch(const char* e){std::cout << e;}
    
    
    //Run System
    for(int itr = 0; itr < tmp.max_iter; ++itr){  
        new_position.clear();
        
        //Move Rectangles
        for (auto e = lClass.begin() ; e != lClass.end(); ++e)
            new_position.push_back(e->move(tmp.dt, st.h, st.w, st.mu_d));
        

        for (int i=0; i<tmp.n; ++i){       
            //Wall Collision
            if(std::get<0>(new_position[i]) + lClass[i].wr >= st.w || std::get<0>(new_position[i]) < 0)
            {
                wall = true;
                lClass[i].vx = -lClass[i].vx;    
            }
                
            
            if(std::get<1>(new_position[i]) >= st.h || std::get<1>(new_position[i]) - lClass[i].hr  < 0 )
            {   
                wall = true;
                lClass[i].vy = -lClass[i].vy;
            }
            
            if(wall){
                wall = false;
                continue;
            }

            if(tmp.n == 1){
                lClass[i].x = std::get<0>(new_position[i]);
                lClass[i].y = std::get<1>(new_position[i]);     
            }
            
            //Rectangle Collision
            for (int j= i+1; j<tmp.n; ++j){

                double new_x = std::get<0>(new_position[i]);
                double new_y = std::get<1>(new_position[i]);

                double new_x2 = std::get<0>(new_position[j]);
                double new_y2 = std::get<1>(new_position[j]);
                    
                //Rigth      
                if ((new_x + lClass[i].wr > new_x2 &&  new_x + lClass[i].wr < new_x2 + lClass[j].wr) &&
                    (new_y <= new_y2  && new_y - lClass[i].hr >= new_y2 - lClass[j].hr) ||
                    (new_y > new_y2  && new_y - lClass[i].hr < new_y2 - lClass[j].hr))
                
                    {collision = true;}

                //Left
                else if(new_x < new_x2 + lClass[j].wr && new_x < new_x2 && 
                   new_y < new_y2  && new_y - lClass[i].hr > new_y2 - lClass[j].hr ||
                   new_y > new_y2  && new_y - lClass[i].hr < new_y2 - lClass[j].hr)
                
                    {collision = true;}


                //Top
                else if(new_y > new_y2 - lClass[j].hr && new_y < new_y2 &&
                   new_x <= new_x2  && new_x - lClass[i].wr >= new_x2 - lClass[j].wr ||
                   new_x > new_x2  && new_x - lClass[i].wr < new_x2 - lClass[j].wr)
                 
                    {collision = true;}

                //Botton
                else if(new_y - lClass[i].hr < new_y2 && new_y - lClass[i].hr > new_y2 - lClass[i].hr &&
                   new_x <= new_x2  && new_x - lClass[i].wr >= new_x2 - lClass[j].wr ||
                   new_x > new_x2  && new_x - lClass[i].wr < new_x2 - lClass[j].wr)
                
                    {collision = true;}

                else    
                    {collision = false;}
                

                if(collision){
                    double new_vx = ( lClass[i].vx* (lClass[i].m - lClass[j].m) + 2 * lClass[j].vx *  lClass[j].m ) / (lClass[i].m + lClass[j].m);
                    double new_vy = ( lClass[i].vy* (lClass[i].m - lClass[j].m) + 2 * lClass[j].vy *  lClass[j].m ) / (lClass[i].m + lClass[j].m);  
                    
                    double new_vx2 = ( lClass[j].vx* (lClass[j].m - lClass[i].m) + 2 * lClass[i].vx *  lClass[i].m ) / (lClass[j].m + lClass[i].m);  
                    double new_vy2 = ( lClass[j].vy* (lClass[j].m - lClass[i].m) + 2 * lClass[i].vy *  lClass[i].m ) / (lClass[j].m + lClass[i].m);  

                    lClass[i].vx = new_vx;  lClass[i].vy = new_vy;           
                    lClass[j].vx = new_vx2; lClass[j].vy = new_vy2;
                
                }
                
                else{
                    lClass[i].x = std::get<0>(new_position[i]);
                    lClass[i].y = std::get<1>(new_position[i]);
                    
                    lClass[j].x = std::get<0>(new_position[j]);
                    lClass[j].y = std::get<1>(new_position[j]);
                } 
            }
        }

        if(itr % tmp.print_freq == 0 || itr == tmp.max_iter - 1)
            printState(lClass, itr);


        //check system stop
        double sum = 0;
        for(auto e = lClass.begin() ; e != lClass.end(); ++e){
            sum += sqrt(pow(e->vx, 2) + pow(e->vy, 2)); 
            if(sum > 0.0001)
                break;
        }
        
        if(sum < 0.0001)    
            break;
    }
    auto timeEnd = duration_cast<duration<double>>(high_resolution_clock::now() - timeStart).count();
    std::cout << "Runtime: " << timeEnd;

}