#include "flowers.h"
#include <math.h>
#include <stdio.h>
#include <list>

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
     if (fr.fixedPart.size()!=0) {

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
//    printf("BOX:  K: %d        l: %d        j: %d       i: %d \n",box.k ,box.l,box.j,box.i);
//    double blank;
//    double joverl = -1;
//    double ioverk = -2;
//    double temp1,temp2;
//    if((box.k == 0 && box.l ==0 ) || box.boxedFraction.fixedPart.size() == 0){
//        std::cout<< "____K AND L == 0___"<<std::endl;
//        return -1;
//    }
//    else if(box.k !=0  && box.l !=0 ) {
//        temp1 =box.j / (double)box.l;
//        temp2 =box.i / (double)box.k;
//        joverl = (int) temp1;
//        ioverk = (int) temp2;
//        std::cout<<"\n joverl = "<< temp1<<  "  ioverk = "  << temp2<<std::endl;
//        std::cout<<"\n joverl = "<< joverl<<  "  ioverk "  << ioverk<<std::endl;
//        
//    }
//    else if(joverl == ioverk){
//        std::cout<<"\n joverl == ioverk   : "<< joverl <<std::endl;
//        int p=box.boxedFraction.fixedPart.front();
//        box.boxedFraction.fixedPart.erase(box.boxedFraction.fixedPart.begin());
//        
//        int i =box.i;
//        box.i=box.j;
//        int k =box.k;
//        box.k=box.l;
//        box.j = i+ (box.j*p);
//        box.l = k+ (box.l*p);
//        
//        //printf("returning:  %f",joverl);
//        return (int)joverl;
//    }
//    else if(joverl != ioverk || box.k ==0  || box.l ==0 ){
//        printf(" J/l!= i/K or K or (L == 0) \n");
//        int p=box.boxedFraction.fixedPart.front();
//        box.boxedFraction.fixedPart.erase(box.boxedFraction.fixedPart.begin());
//        //set holders and swap
//        int i =box.i;
//        box.i=box.j;
//        int k =box.k;
//        box.k=box.l;
//        //evaluate for new l and j
//        box.j = i+ (box.j*p);
//        box.l = k+ (box.l*p);
//        printf("BOX2:  K: %d        l: %d        j: %d       i: %d \n",box.k ,box.l,box.j,box.i);
//        spitNextMagicBox(box);
//    }
//        
//   
//    
//    return -1;
    return 2;
    
    
    
}


ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
    std::vector<int> temp;
    int n = length +1;
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
    std::cout<<flag << ":FLAG"<<std::endl;
    while ( flag != -1 && flag <1) {
        toRet.fixedPart.push_back(flag);
        
        flag = spitNextMagicBox(*box);
        
        

    }
    
    
    
    return toRet;
}
