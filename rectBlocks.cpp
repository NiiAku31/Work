// ICP LAB !!
// Aaron Adom-Malm
// Nii Kwaku Adjei Aku

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm> 

#define PI 3.14


using namespace std;





class rectBlocks{
    public:
    int Width;
    int Height;
    int Length;
    int Diameter;

    rectBlocks(){
        Width = 0;
        Height = 0;
        Length = 0;
    }

    rectBlocks(int aWidth, int aHeight, int aLength){
        Width = aWidth;
        Height = aHeight;
        Length = aLength;
    }
};

class sqrBaseRectBlocks :public rectBlocks{
    public:
    sqrBaseRectBlocks(){
        Width = 0;
        Height = 0;
        Length = 0;
        }

    sqrBaseRectBlocks(int aWidth, int aLength){
        Width = aWidth;
        Height = aWidth;
        Length = aLength;
    }
};

class cuboidBlocks : public sqrBaseRectBlocks{
    public:
    cuboidBlocks(){
        Width = 0;
        Height = 0;
        Length = 0;
        }

    cuboidBlocks(int aWidth){
        Width = aWidth;
        Height = aWidth;
        Length = aWidth;
    }
};

class cylindricalBlocks : public sqrBaseRectBlocks{
    public:
    int Diameter;
    cylindricalBlocks(int aDiameter, int aLength){
        Diameter = aDiameter;
        Length = aLength;
    }
};


class sphericalBlocks : public cuboidBlocks{
    public:
    int Diameter;
    sphericalBlocks(int aDiameter){
        Diameter = aDiameter;
    }
};



// FUNCTIONS

double  surfaceOfcylinder(int Diameter, int Length){
    return PI*Diameter*Length + (PI*Diameter*Diameter)/2;
}


double surfaceOfsphere(int Diameter){
    return PI*Diameter*Diameter;
}

double volumeOfsphere(int Diameter){
    return (PI*Diameter*Diameter*Diameter)/6;
}


int main(){
    vector<rectBlocks> rectblocks;
    vector<sqrBaseRectBlocks> squarebaseblocks;
    vector<cuboidBlocks> cuboidblocks;
    vector<sphericalBlocks> sphericalblocks;
    vector<cylindricalBlocks> cylindricalblocks;

    int Width1;
    int Height1;
    int Length1;

    ifstream infile;
    infile.open("dataBlocks.dat");
    infile >> Width1 >> Height1 >> Length1;

    while(infile >> Width1 >> Height1 >> Length1){
        rectBlocks block= rectBlocks(Width1,Height1,Length1);
        rectblocks.push_back(block);
    }

    for(int n = 0; n<rectblocks.size(); n++){
        int Width1 = rectblocks[n].Width;
        int Height1 = rectblocks[n].Height;
        int Length1 = rectblocks[n].Length;
    

        if(Width1 == Height1){
            sqrBaseRectBlocks sqrbase = sqrBaseRectBlocks(Width1, Length1);
            cylindricalBlocks cylbase = cylindricalBlocks(Width1, Length1);

            squarebaseblocks.push_back(sqrbase);
            cylindricalblocks.push_back(cylbase);

            if( Height1 == Length1){
                cuboidBlocks cuboid = cuboidBlocks(Length1);
                sphericalBlocks sphere = sphericalBlocks(Length1);

                cuboidblocks.push_back(cuboid);
                sphericalblocks.push_back(sphere);
            }
        }
    }
    

    sort(sphericalblocks.begin(), sphericalblocks.end(), [](sphericalBlocks ONE, sphericalBlocks TWO){
        return ONE.Diameter < TWO.Diameter;
    });

    sort(cylindricalblocks.begin(), cylindricalblocks.end(), [](cylindricalBlocks THREE, cylindricalBlocks FOUR){
        return THREE.Diameter < FOUR.Diameter;
    });

    cout << endl << "The Spherical Blocks Computation is as follows:" << endl;
    cout<<"Diameter      "<<"Volume      "<<"Surface Area"<<endl;
    cout<<"---------------------------------------------- "<<endl;

    for(int i = 0; i<sphericalblocks.size();i++){
        cout << sphericalblocks[i].Diameter<< " "<<surfaceOfsphere(sphericalblocks[i].Diameter) << "  " << volumeOfsphere(sphericalblocks[i].Diameter) << endl;

    }

    cout << endl;

    cout << "The Cylindrical Blocks Computation is as follows:" << endl;
    cout<<"Diameter      "<<"Volume      "<<"Surface Area"<<endl;
    cout<<"----------------------------------------------"<<endl;

    for(int a = 0; a<cylindricalblocks.size();a++){
        cout << cylindricalblocks[a].Diameter << " " << surfaceOfcylinder(cylindricalblocks[a].Diameter,cylindricalblocks[a].Length) << " "<< cylindricalblocks[a].Length;
    }

    infile.close();
    cin.get();
    cout << "End of Program!";
    return 0;
}