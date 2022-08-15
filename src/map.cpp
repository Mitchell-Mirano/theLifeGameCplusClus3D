#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

class GameMap{

    private:
        const int max_x_ncells=100;
        const int max_y_ncells=100;
        int x_ncells;
        int y_ncells;
        int cellNeighborsNumber;
        vector<vector<int>>mapState;
        
    public:

        GameMap(){
            this->x_ncells=20;
            this->y_ncells=20;
            this->mapState.assign(this->y_ncells,vector<int>(this->x_ncells,0));
        }

        GameMap(int x_ncells, int y_ncells){
            
            if(x_ncells<=max_x_ncells){
                 this->x_ncells = x_ncells;
            }else{
                cout<<"The number of cells in x must be less or equal to: "<<max_x_ncells<<endl;
            }

            if(y_ncells<=max_y_ncells){
                 this->y_ncells = y_ncells;
            }else{
                cout<<"The number of cells in y must be less or equal to:"<<max_y_ncells<<endl;
            }

            this->mapState.assign(this->y_ncells,vector<int>(this->x_ncells,0));
        }

        int getCellsAlive(){
            int cellsAlive=0;
            for(int i=0;i<this->y_ncells;i++){
                for(int j=0;j<this->x_ncells;j++){
                    if(this->mapState[i][j]==1){
                        cellsAlive++;
                    }
                }
            }
            return cellsAlive;
        }

        void setMapValue(int row, int column,int value){
            this->mapState[row][column] = value;
        }

        int getMapValue(int row, int column){
            return this->mapState[row][column];
        }

        void updateMapValue(int row, int column){
            if (row >= 0 && row < this->y_ncells && column >= 0 && column < this->x_ncells)
            {
                if (this->mapState[row][column] == 0)
                {
                    this->mapState[row][column] = 1;
                }
                else
                {
                    this->mapState[row][column] = 0;
                }
            }
            else
            {
                if (this->mapState[y_ncells-1][x_ncells-1] == 0)
                {
                    this->mapState[y_ncells-1][x_ncells-1] = 1;
                }
                else
                {
                    this->mapState[y_ncells-1][x_ncells-1] = 0;
                }
            }
        }

        void readMapFromFile(string filepath){
            string line;
            ifstream gameMapTxt(filepath);

            if(gameMapTxt.is_open()) {
                for(int j=0; j<this->y_ncells; j++) {
                    getline(gameMapTxt,line);
                    for(int i=0; i<this->x_ncells; i++) {
                        line[i]=='0'? this->mapState[j][i]=0:this->mapState[j][i]=1;
                    }
                }
            }
        }

        void drawMap(){
            for (int j = 0; j<this->y_ncells; j++){
                for (int i = 0;i<this->x_ncells; i++){
                    cout <<this->mapState[j][i]<< " "; //
                }
                cout <<endl;
    
            }
        }

        int getcellNeighbors(int y, int x){

            int n1=this->getMapValue((this->y_ncells+y-1)%this->y_ncells,(this->x_ncells+x-1)%this->x_ncells);
            int n2=this->getMapValue((this->y_ncells+y-1)%this->y_ncells,(this->x_ncells+x)%this->x_ncells);
            int n3=this->getMapValue((this->y_ncells+y-1)%this->y_ncells,(this->x_ncells+x+1)%this->x_ncells);

            int n4=this->getMapValue((this->y_ncells+y)%this->y_ncells,(this->x_ncells+x-1)%this->x_ncells);
            int n5=this->getMapValue((this->y_ncells+y)%this->y_ncells,(this->x_ncells+x+1)%this->x_ncells);

            int n6=this->getMapValue((this->y_ncells+y+1)%this->y_ncells,(this->x_ncells+x-1)%this->x_ncells);
            int n7=this->getMapValue((this->y_ncells+y+1)%this->y_ncells,(this->x_ncells+x)%this->x_ncells);
            int n8=this->getMapValue((this->y_ncells+y+1)%this->y_ncells,(this->x_ncells+x+1)%this->x_ncells);


            int numberOfNeighbors=n1+n2+n3+n4+n5+n6+n7+n8;

            return numberOfNeighbors;
        
        }

        void updateMapState(){

            vector<vector<int>>newMapState;

            newMapState.assign(this->y_ncells,vector<int>(this->x_ncells,0));

            for(int j=0;j<this->y_ncells;j++){
                for(int i=0;i<this->x_ncells;i++){

                    if(this->mapState[j][i]==0){
                       if(this->getcellNeighbors(j,i)==3){
                        newMapState[j][i]=1;
                       }
                    }else{
                        if(this->getcellNeighbors(j,i)==2 || this->getcellNeighbors(j,i)==3 ){
                            newMapState[j][i]=1;
                        }else{
                            newMapState[j][i]=0;
                        }
                    }

                }
            }
            
            mapState=newMapState;
    
    }
        

        

};