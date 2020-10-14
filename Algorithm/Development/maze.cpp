/** compile: g++ -Wall -pedantic maze.cpp                  **/
/** run: ./a.out                                           **/

#include <iostream>
#include <fstream>
#include <cstdlib>

#define INF 99999

using namespace std;

/** stucture 4 field coordinates                           **/
class Point
{
  public:
         int x;
         int y;
  Point(){x=y=0;}
};

/** structure 4 fields-objects                             **/
class Object
{
      public:
             int no; // no 4 fields
             int value;
             int key;
             int tick; //was there=1, was not there=0
             int path;
      Object(){no=value=key=tick=0;path=INF;}
};

/** models a BOARD                                         **/

class Board
{
    private:
            int k;
    public:
     Object **Tab;
     int lines,columns;

Board()
{
     k=1;
     ifstream file;

     file.open("maze007a.txt");

     if(file.good()==true)
      {
       file>>lines>>columns;
       if(lines<=0 || columns<=0)
         { cout<<"wrong data in the txt file!!"<<endl;
             getchar(); exit(-7);}
       Tab=new Object *[lines];
       for (int i=0;i<lines;i++)
        Tab[i]=new Object[columns];


       for(int i=0;i<lines;i++)
       {
        for(int j=0;j<columns;j++)
        {
         file>>Tab[i][j].value;
                     if(Tab[i][j].value!=1 && Tab[i][j].value!=0)
                     { cout<<"wrong data in the txt file!!"<<endl; getchar(); exit(-2);}
        }
       }

     file.close();
     }
     else
     {
       cout<<"no access in to the txt file!!!"<<endl;
        getchar();
       exit(-1);
     }

     for(int i=0;i<lines;i++)
     {
      for(int j=0;j<columns;j++)
       {
         if(Tab[i][j].value==0)
          Tab[i][j].key=k++;
       }
      }

     PrintBvalues();
     PrintMaze();
}

virtual ~Board()
{
    for(int i=0;i<lines;++i)
    delete[]Tab[i];
    delete[]Tab;
}

void  PrintBvalues()
{
      cout<<"dim = "<<lines<<" x "<<columns<<endl<<endl;
      cout<<"Board: "<<endl;
       for(int i=0;i<lines;i++)
        {
        for(int j=0;j<columns;j++)
         {
          cout<<Tab[i][j].value<<" ";
         }
         cout<<" "<<endl;
        }
}

void PrintMaze()
{
         cout<<" "<<endl;cout<<" "<<endl;
      for(int i=0;i<lines;i++)
        {
        for(int j=0;j<columns;j++)
         {
                if(Tab[i][j].value==1){cout<<char(-37);}
                else cout<<" ";
         }
         cout<<" "<<endl;
        }
        cout<<" "<<endl;cout<<" "<<endl;
}

};

/** models a TREE we want to create                        **/
/** constructor asks for and reads start and finish        **/
/** coordinates                                            **/
/** algorithm methods:                                     **/
/** Search - calls Check 4 times to check all directiones  **/
/**          down, right, up, left                         **/
/** Check - checks where it is possible to go and calls    **/
/**         Search                                         **/
/** and print the coordinates of the shortest path         **/
class Tree
{
      private:
             Board B;
             Point S,M,D, *route66, *route66_cp;
             int length;


      public:
            int Min_L, counter;

Tree()
{
       do
       {
         do
          {
            D.x=-1;M.x=-1;
             while(D.x<0 || D.x>=B.lines || D.y<0 || D.y>=B.columns){
              cout<<"Enter start point coordinates"<<endl;
              cin>>D.x;
              cin>>D.y;}
             while(M.x<0 || M.x>=B.lines || M.y<0 || M.y>=B.columns){
              cout<<"Enter finish point coordinates"<<endl;
              cin>>M.x;
              cin>>M.y;}
               if(D.x==M.x && D.y==M.y){
                cout<<"coordinates can not be equal!"<<endl;}
           }while(D.x==M.x && D.y==M.y);

         if(B.Tab[D.x][D.y].value!=0 || B.Tab[M.x][M.y].value!=0)
         {cout<<"wrong coordinates, you cant start or finish at the wall"<<endl;}

       }while(B.Tab[D.x][D.y].value!=0 || B.Tab[M.x][M.y].value!=0 );

        counter=0;
        length=0;

        Min_L=(B.lines-1)*(B.columns-1);
        route66 = new Point[(B.lines-1)*(B.columns-1)];
        route66_cp = new Point[(B.lines-1)*(B.columns-1)];
}

void cp()
{
    for(int i=0;i<length;i++)
     {
        route66_cp[i].x=route66[i].x;
        route66_cp[i].y=route66[i].y;
     }
}

/** THE ALGORITHM                                           */

void Search()
{
    Check(0,-1);
    Check(1,0);
    Check(0,1);
    Check(-1,0);
     counter++;
}

void Check(int h, int v)
{
    ///////////////////////////////////////////////////////////////////
    //tuning1 this is thinking
    if(abs(M.x-D.x)+abs(M.y-D.y)+length>=Min_L){return;}
    ///////////////////////////////////////////////////////////////////

    if(B.Tab[D.x+h][D.y+v].value==1 || B.Tab[D.x+h][D.y+v].tick==1 ){return;}

    if((B.Tab[D.x+h][D.y+v].value==0 || B.Tab[D.x+h][D.y+v].value==2) && B.Tab[D.x+h][D.y+v].tick==0 )
     {
        ///////////////////////////////////////////////////////////////
        //tuning3 this is thinking
        if(length<B.Tab[D.x+h][D.y+v].path)
        {B.Tab[D.x+h][D.y+v].path=length;}
        else{return;}
        //
        //////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////
        //tuning2 this is thinking
        if(length>Min_L){return;}
        //
        //////////////////////////////////////////////////////////////

                 D.x=D.x+h;
                 D.y=D.y+v;
                 route66[length].x=D.x;
                 route66[length].y=D.y;
                 B.Tab[D.x][D.y].tick=1;
                 length++;
                 if(D.x==M.x && D.y==M.y)
                 {
                  if(length<Min_L)
                  {
                   cp();
                   Min_L=length;
                  }
                 }

                 Search();


                 length--;
                 route66[length].x=0;
                 route66[length].y=0;
                 B.Tab[D.x][D.y].tick=0;
                 D.x=D.x-h;
                 D.y=D.y-v;

    }
}

void  PrintTree()
{
      cout<<"The board: "<<endl;
       for(int i=0;i<B.lines;i++)
        {
        for(int j=0;j<B.columns;j++)
         {
          if(B.Tab[i][j].path==INF){cout<<char(-37);}
          else{ cout<<B.Tab[i][j].path;}
         }
         cout<<" "<<endl;
        }
}

void PrintPathCoordinates()
{
          for(int i=0;i<Min_L;i++)
          {
                  cout<<i+1<<"->";
                  cout<<"("<<route66_cp[i].x<<","<<route66_cp[i].y<<")"<<endl;
          }
}


};

int main()
{
    Tree Maze;

    Maze.Search();

    cout<<"shortest path length: "<<Maze.Min_L<<endl;
    cout<<"algorithm recurention's amout: "<<Maze.counter<<endl;
    cout<<endl;

    cout<<"the shortest path coordinates: "<<endl;
    Maze.PrintPathCoordinates();

        getchar();
        getchar();
    cout<<" "<<endl;
    cout<<"\n\n\n\nmaskotkys..."<<endl;

}

