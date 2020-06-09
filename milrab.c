



//MILRAB.C

#include <stdio.h>
#include <time.h>
#define MINNUM 3990000000
#define MAXNUM 4010000000



//a function to return (base^exponent)%modulus -"Modular Exponentiation" pseudocode in C algorithm-
unsigned long modular_pow (unsigned long base,unsigned long exponent,unsigned long modulus)
{
    unsigned long result;
    
    if (modulus ==1)
        return 0;
    
    result=1;
    base=base%modulus;
    while (exponent>0) {
        if (exponent%2==1)
            result = (result*base) % modulus;
        
        exponent=exponent>>1;
        base= (base*base) % modulus;
        
    }
    
    return result;
    
}

///Here is a function for a.To return a=1||a=7||a=61.
int choose(int x)
{
    
    int a;
    
    if (x==1)
        a = 2;
    else if (x==2)
        a = 7;
    else if (x==3)
        a = 61;
    
    return a;
}




int Deterministic (unsigned int minnum , unsigned int maxnum ) {
    
    
    unsigned int i;
    int j , flag=0 , p=0 ;
    for (i = MINNUM+1 ; i<MAXNUM ; i=i+2 )    {
        if ((i%2==0)||(i%3==0)) //Now we check if i is factorial of 2 and 3.
            continue; //If i is factorial of 2 and 3,jump to next i .
        for (j=5 ; (j*j)<=i ; j=j+6){ //Now we just need to check
            if ((i%j==0 )||(i%(j+2)==0)) { //the numbers (5,7) next (11,13) , etc.
                
                flag=0; //if i%j=0 , number has at least one fuctorial(j or j+2) and its not prime.
                break; //break "for" loop for this i,and check the next i.
                
            }
            
            else { //if the  second "if statement" is false ,
                flag=1; //number is prime.
                
            }
        }
        if (flag==1){//i is prime and now
            p=p+1; //primes are p+1.
        }
    } //closing the 2nd for .
    return p;
} //end of "Deterministic" function



//MILER-RABIN PSEUDOCODE IN C ALOGORITHM

int MilerRabin (unsigned int minnum , unsigned int maxnum ) {
    
    unsigned long  x,q,a,d,s ;
    int w,flag,r,isprime,p=0;
    
    for (s = minnum+1; s <= maxnum-1 ; s = s + 2){
        d = s - 1;
        r = 0;
        
        while (d % 2 == 0 ){
            d = d/2;
            r++;
        } //Inside this "while" loop , we just get the number in factors of 2^r * (an odd number "d")
        
        isprime = 1;
        for(int i  = 1; i <= 3; i++){ //Actually "i" is the sequence of a's we use (we use 3 a's :a=2|7|61 )
            flag = 0;
            a = choose(i); // "a" gets the value of the function "choose(i)"
            
            x = modular_pow (a,d,s); //x gets the value of the function "modular_pow", x=(a^d)%s.
            
            if ((x==1) || (x==s-1))
                continue; //In case of x=1 or x=s-1 , we need to check for next a.
            
            for(w=1; (w<=(r-1)); w++){ //else in case of x!1 or x!s-1
                
                x = modular_pow(x,2,s); //"x" gets the value of "modular_pow" function, x=(x^2)%s
                
                if (x==s-1){
                    flag=1;
                    break; //In case of the "if" statement is true, break the 2nd "for" loop and check for the next a, if it exists.
                }
            }
            
            if (flag)
                continue; //check for next a,if exists.
            else{
                isprime = 0; //i isn't prime
                break; //stop checking for this i.
            }
            
        }
        
        if (isprime)
            p=p+1; //in case of the value of "isprime" is 1, number is prime and we have to increase the variable.
    }
    
    return p;
    
}

//MAIN PROGRAM USING THE DETERMINISTIC AND MILER RABIN ALGORITHMS THAT I MADE
int main(void) {
    
    int p=0;
    double sttime , endtime ;
    
    // Deterministic Algorithm
    
    
    printf("Checking range [%ld,%ld] for primes \n" , MINNUM , MAXNUM);
    sttime = (double) clock(); //Let the time count.
    p=Deterministic(MINNUM,MAXNUM);//Use function "Deterministic" to get the results for Deterministic algorithm.
    endtime = (double) clock(); //Program ended,stop counting time.
    printf("Deterministic algorithm: Found %d primes in %.2f secs \n" , p , (endtime - sttime)/CLOCKS_PER_SEC ) ; //Print the results of Deterministic algorithm
    
    //Miler-Rabin algorithm
    
    sttime = (double) clock();  //Let the time count,again.
    p=MilerRabin(MINNUM,MAXNUM); //Use function "MilerRabin" to get the results for Miler Rabin algorithm.
    endtime = (double) clock(); //Program ended,stop counting time.
    printf("Miler-Rabin algorithm:   Found %d primes in  %.2f secs \n" , p , (endtime - sttime)/CLOCKS_PER_SEC ) ; //Print the results of Miler-Rabin algorithm
    
}

