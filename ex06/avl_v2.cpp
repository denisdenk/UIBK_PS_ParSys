#include <iostream>
#include <vector>
#include <map>
using namespace std;

// search position to insert i in tree based on starting position
// direction is an array with two entries based on the previous moves

// find a position to insert i into the tree, the search starts from a starting position
void search_full(unsigned i, int *position, int *direction, map<int, unsigned> &tree){

    int success = 0;    // check if the program is finished

    while(success == 0){

        
        if (tree.count(position[0]) == 0){success = 1;} // position is empty so we can fill it

        else {

            // send to new position and note direction
            
            // left 
            if (i < tree[position[0]]){ position[0] = 2 * position[0] + 1; direction[0]=direction[1]; direction[1]=-1;}

            // right
            else if (i > tree[position[0]]){ position[0] = 2 * position[0] + 2; direction[0]=direction[1]; direction[1]=1;}

            // duplicate, set position to -1, leave direction unchanged and exit
            else {position[0] = -1; success = 1;}

        }


    }


}

// insert the unsigned at given position in the tree, check for imbalance, if yes restructure the tree correctly
void insert(unsigned i, int *position, int *direction, map<int, unsigned> &tree){

    tree[position[0]] = i; // insert
    int success = 0;    // check if program should finish
    

    while (success == 0){

        

        // check if this is the first entry 

        if (direction[0] == 0){success = 1;} 

        // check for imbalance depending on direction

        // mother node is right of child
        else if (direction[1] == -1){

            // check if mother node has right child

            // has child 
            if (tree.count(position[0] + 1) != 0){success = 1;}

            // has no child
            else{

                // check if grandmother node is right or left and if it exists

                // grandmother node does not exist (we are in the second level) -> no imbalance                   
                if (direction[0] == 0){success = 1;}

                // gm node is right
                else if (direction[0] == -1){

                    // check if right child of gmn exists
                    if (tree.count((position[0] + 1)/2) != 0){ success = 1;} 

                    // child does not exist -> restructure nodes
                    else {

                        // save values in nodes
                        unsigned values[3];
                        values[0] = tree[position[0]];
                        values[1] = tree[(position[0] - 1)/2];
                        values[2] = tree[(position[0] - 3)/4];

                        // assign values correctly
                        tree.erase(position[0]);
                        tree[(position[0] - 1)/2] = values[0];
                        tree[(position[0] - 3)/4] = values[1];
                        tree[(position[0] + 1)/2] = values[2];

                        success = 1;

                    }
                }
                   
                // gm node is left
                else {   

                    // check if left child of gmn exists
                    if (tree.count((position[0] - 3)/2) != 0){ success = 1;} 
                  
                    // child does not exist -> restructure nodes
                    else{

                        // save values in nodes
                        unsigned values[2];
                        values[0] = tree[position[0]];
                        values[1] = tree[(position[0] - 5)/4];

                        // assign values correctly
                        tree.erase(position[0]);
                        tree[(position[0] - 5)/4] = values[0];
                        tree[(position[0] - 3)/2] = values[1];

                        success = 1;

                    }
                    
                }
            
            }
        }

        // mother node is left of child
        else {

            // check if mother node has left child

            // has child 
            if (tree.count(position[0] - 1) != 0){success = 1;}

            // has no child
            else{

                // check if grandmother node is right or left and if it exists

                // grandmother node does not exist (we are in the second level) -> no imbalance                   
                if (direction[0] == 0){success = 1;}

                // gm node is rigth 
                if (direction[0] == -1){

                    // check if right child of gmn exists
                    if (tree.count(position[0]/2) != 0){ success = 1;} 

                    // child does not exist -> restructure nodes                    
                    else{

                        // save values in nodes
                        unsigned values[2];
                        values[0] = tree[position[0]];
                        values[1] = tree[(position[0] - 4)/4];
                            

                        // assign values correctly
                        tree.erase(position[0]);
                        tree[position[0]/2] = values[1];
                        tree[(position[0] - 4)/4] = values[0];
                            

                        success = 1;

                    }
                }
                   
                // gm node is left
                else {

                    // check if left child of gmn exists
                    if (tree.count((position[0] - 4)/2) != 0){ success = 1;} 

                    // child does not exist -> restructure nodes                    
                    else{   

                        // save values in nodes
                        unsigned values[3];
                        values[0] = tree[position[0]];
                        values[1] = tree[(position[0] - 2)/2];
                        values[2] = tree[(position[0] - 6)/4];

                        // assign values correctly
                        tree.erase(position[0]);
                        tree[(position[0] - 2)/2] = values[0];
                        tree[(position[0] - 6)/4] = values[1];
                        tree[(position[0] - 4)/2] = values[2];

                        success = 1;

                    }
                }

            }
        }
    }
}    



int main(){

    // test sequential functions of the program on a custom array of unsigned integers
    unsigned testarray[15];

    testarray[0] = 4;
    testarray[1] = 8;
    testarray[2] = 7;
    testarray[3] = 11;
    testarray[4] = 5;
    testarray[5] = 10;
    testarray[6] = 23;
    testarray[7] = 8;
    testarray[8] = 2;
    testarray[9] = 12;
    testarray[10] = 9;
    testarray[11] = 16;
    testarray[12] = 13;
    testarray[13] = 6;
    testarray[14] = 0;


    for (int i = 0; i<15; i++){

        cout << testarray[i] << "   ";
    }
    cout << endl;
    
    // create tree

    map<int, unsigned> avl;

    // set first entry

    int pos[1] = {0};
    int dir[2] = {0};

    insert(testarray[0], pos, dir, avl);
    // go through other elements

    for (int i=1; i<15; i++){

        cout << testarray[i] << endl;

        
        pos[0] = 0;
        dir[0] = 0;
        dir[1] = 0;

        search_full(testarray[i], pos, dir, avl);
        //cout << pos[0] << endl;
        //cout << dir[0] << dir[1] << endl;
        //cout << pos[0]/2 + 1 << " " << avl.count(pos[0]/2 + 1) << endl;
        if (pos[0] != -1){insert(testarray[i], pos, dir, avl);}
        for (const auto& elem : avl){cout << elem.first << " ";}
        cout << endl;
        for (const auto& elem : avl){cout << elem.second << " ";}
        cout << endl;
        
    }


  
    return 0;
}