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
    // just looking at the peridoic part of th eq and see the patterns
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
    //just get decimal part of aproxmation
    angleApproxDeci = modf(angleApproxDeci, &blank);
    //following the formula
    return  angleApproxDeci * (2*M_PI);
}

Seed getSeed(ContinuedFraction &theta, int k) {
    Seed toRet;
    //applying formula from assigment
    double angle = getAngle(theta, k);
    
    toRet.x= sqrt(k/M_PI)*cos(angle);
    toRet.y= sqrt(k/M_PI)*sin(angle);
    return toRet;
}

void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
    //pretty simple
    flower.push_back(getSeed(theta, (int)flower.size()));
}

int spitNextMagicBox(MagicBox &box) {

    //base case
    printf("BOX:  \n i: %d  j: %d      \n k: %d  l: %d \n",box.i ,box.j,box.k,box.l);
    if (box.k == 0 && box.l==0) {
        return NULL;
    }
    //end of x case
    if (box.boxedFraction.fixedPart.size()==0) {
        
        int i=box.i;
        int k=box.k;
        box.k= 0;
        box.l=0;
        return i/k;
    }
    // k or l are zero
    if (box.k == 0 || box.l ==0) {
        notEqual:
        //make temps and resign as per the algortihmim in the assigment
        int p=box.boxedFraction.fixedPart.front();
        box.boxedFraction.fixedPart.erase(box.boxedFraction.fixedPart.begin());
        int i =box.i;
        box.i=box.j;
        int k =box.k;
        box.k=box.l;
        //evaluate for new l and j
        box.j = i+ (box.j*p);
        box.l = k+ (box.l*p);
        //recurese
        return spitNextMagicBox(box);
    }
    double temp1 =box.j / (double)box.l;
    double temp2 =box.i / (double)box.k;
    int joverl = (int) temp1;
    int ioverk = (int) temp2;
    //eq case
    if (joverl == ioverk ) {
        //make temps and resign as per the algortihmim in the assigment
        int p = joverl;
        int i =box.i;
        box.i=box.k;
        int j =box.j;
        box.j=box.l;
        box.k = i - (box.k*p);
        box.l = j - (box.l*p);
         printf("RETURNING: %d \n",p);
        return p;
    }
    else{
        // same case as l or k ==0
        goto notEqual;
    }
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
   
    //make a new magic box
    MagicBox *box = new MagicBox;
    box->i=a;
    box->j=b;
    box->boxedFraction.fixedPart = temp;
    
    ContinuedFraction toRet = *new ContinuedFraction;
    //push new magic box if it is not null
    int flag = spitNextMagicBox(*box);
    
    if (flag != NULL) {
        toRet.fixedPart.push_back(flag);
    }
    //continue to push while not null
    while (flag != NULL) {
        flag = spitNextMagicBox(*box);
        toRet.fixedPart.push_back(flag);
    }
    printf("MAGIC %d", spitNextMagicBox(*box));
    
    
    
    return toRet;
}
