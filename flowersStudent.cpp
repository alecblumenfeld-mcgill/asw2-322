#include "flowers.h"
#include <math.h>
Fraction getApproximation(ContinuedFraction &fr, unsigned int n) {
    Fraction toRet; // will be returned
    std::vector<int> temp;
    //make a new vector list for the length of n
    if (fr.fixedPart.size()!=0) {
        
  
    if (fr.fixedPart.front()==0) {
        std::vector<int>::iterator it = fr.periodicPart.begin();
        while (n>1) {
            temp.push_back(*it);
            n--;
            if (it == fr.periodicPart.end() ) {
                it = fr.periodicPart.begin() ;
            }
        }
        

    }
          }
    else if (fr.fixedPart.size()!=0) {

        for (std::vector<int>::iterator it = fr.fixedPart.begin() ; it != fr.fixedPart.end(); ++it){
            temp.push_back(*it);
            n--;
            if (n<1) {
                break;
                
            }
        }
    }
    //recurse though periodic part for new list
    if (fr.periodicPart.size()!=0) {
    
        std::vector<int>::iterator it = fr.periodicPart.begin();
        while (n>1) {
            temp.push_back(*it);
            n--;
            if (it == fr.periodicPart.end() ) {
                it = fr.periodicPart.begin() ;
            }
        }
    }
 
    toRet.numerator=1;
    toRet.denominator=temp.back();
    temp.pop_back();
    temp.pop_back();
    for (std::vector<int>::iterator it = temp.end()+1 ; it != temp.begin(); --it){
        int num = ((*it)*toRet.denominator);

        toRet.numerator+=num;
        num=toRet.numerator;
        toRet.numerator = toRet.denominator;
        toRet.denominator= num;
        //std::cout << toRet.denominator << " " << toRet.numerator << std::endl;

        
    }
    int num = temp[0]*toRet.denominator;
    toRet.numerator+= num;
    
    return toRet;
}

ContinuedFraction ignoreInt(ContinuedFraction input){
    if (input.fixedPart.size()>0) {
        input.fixedPart[0] = 0;
    }
    return input;
}
int spitSqrt8(int index){
    //fi indexing
    if (index%2) return 1;
    return 4;

}
unsigned int spitEulerSquare(unsigned int index) {
    // TODO : add code here
    if (index==0) return 7;
    if (index%5 == 2|| index%5 == 3) {
        return 1;
    }
    else if (index%5 == 1) {
        return 2 + ((index/5)*3);
    }
    else if (index%5 == 4) {
        return 3 + ((index/5)*3);
    }
    
    return 18 + (((index/5)-1)*12);

}




double getAngle(ContinuedFraction &theta, int k) {
    Fraction angleApprox = getApproximation(theta, 7);
    double angleApproxDeci= k*((double)angleApprox.numerator/(double)angleApprox.denominator);
    double blank;
    angleApproxDeci = modf(angleApproxDeci, &blank);
    return  angleApproxDeci * (2*M_PI);
}

Seed getSeed(ContinuedFraction &theta, int k) {
    Seed toRet;
    
    double angle = getAngle(theta, k);
    
    toRet.x= sqrt(k/M_PI)*cos(angle);
    toRet.y= sqrt(k/M_PI)*sin(angle);
    return toRet;
}

void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
    flower.push_back(getSeed(theta, (int)flower.size()));
}

int spitNextMagicBox(MagicBox &box) {
    if((box.k == 0 && box.l ==0 ) || box.boxedFraction.fixedPart.size() == 0){
        return -1;
        
    }
    double blank;
    double joverl;
    double ioverk;
    try {
         joverl= modf((double)box.j / (double)box.l, &blank);
         ioverk= modf((double)box.i / (double)box.k, &blank);
    } catch (int e) {
        
    }
    if(joverl != ioverk || box.k ==0  || box.l ==0 ){
     
        int p=box.boxedFraction.fixedPart.back();
        box.boxedFraction.fixedPart.pop_back();
        
        int i =box.i;
        box.i=box.j;
        int k =box.k;
        box.k=box.l;
        box.j = i+ (box.j*p);
        
        box.l = k+ (box.l*p);
        return p;
    }
    
    if(joverl != ioverk){
        int p=box.boxedFraction.fixedPart.back();
        box.boxedFraction.fixedPart.pop_back();
        int i =box.i;
        box.i=box.j;
        int k =box.k;
        box.k=box.l;
        box.j = i+ (box.j*p);
        box.l = k+ (box.l*p);
        return p;
    }
    return -1;
   
}


ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
    std::vector<int> temp;
    int n = length;
    //make a new vector list for the length of n
    if (f.fixedPart[0]==0) {
        std::vector<int>::iterator it = f.periodicPart.begin();
        while (n>1) {
            temp.push_back(*it);
            n--;
            if (it == f.periodicPart.end() ) {
                it = f.periodicPart.begin() ;
            }
        }
        
        
    }
    else if (f.fixedPart.size()!=0) {
        
        for (std::vector<int>::iterator it = f.fixedPart.begin() ; it != f.fixedPart.end(); ++it){
            temp.push_back(*it);
            n--;
            if (n<1) {
                break;
                
            }
        }
    }
    //recurse though periodic part for new list
    if (f.periodicPart.size()!=0) {
        
        std::vector<int>::iterator it = f.periodicPart.begin();
        while (n>1) {
            temp.push_back(*it);
            n--;
            if (it == f.periodicPart.end() ) {
                it = f.periodicPart.begin() ;
            }
        }
    }
   
    
    MagicBox *box = new MagicBox;
    box->i=a;
    box->j=b;
    box->boxedFraction.fixedPart = temp;
    
    ContinuedFraction toRet = *new ContinuedFraction;
    int flag =   spitNextMagicBox(*box);
    while ( flag != -1) {
        toRet.fixedPart.push_back(flag);
      
        flag = spitNextMagicBox(*box);
        
        

    }
    
    
    
    return toRet;
}
