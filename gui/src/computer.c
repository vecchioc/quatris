#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "computer.h"

unsigned int mossa2;
  int max_dep=0;

int mv[25];
int
valuta(unsigned int a,unsigned int b,int depth, int alpha, int beta,int MAXD);

double  position(unsigned int, int);
int Count (unsigned int w);

void
init_computer_alghoritm() {  
 
  mv[1]=0x1000; mv[2]=0x2000; mv[3]=0x100; mv[4]=0x80; mv[5]=0x40;
  mv[6]=0x800; mv[7]=0x10000; mv[8]=0x20000; mv[9]=0x40000; mv[10]=0x80000;
  mv[11]=0x4000; mv[12]=0x200; mv[13]=0x10; mv[14]=0x8; mv[15]=0x4;
  mv[16]=0x2; mv[17]=0x1; mv[18]=0x20; mv[19]=0x400; mv[20]=0x8000;
  mv[21]=0x100000; mv[22]=0x200000; mv[23]=0x400000; 
                   mv[24]=0x800000; mv[25]=0x1000000;

	     

}
//    v=valuta(board2,board1,DP,-2000,2000);
//
//    printf("%d\n",mossa2);
//    if(v>0) {
//      previsione=DP-v;
//      printf("faccio quatris fra %.f mosse\n",ceil(previsione/2));
//    }

double  position(unsigned int u,int j) {
  unsigned int w,v;
  int i;
 
  v=u;
  for (i=1; i <= 5; i++){
    w = 0x108421&v;
    if(!w&mv[i]) continue;

    if ((w == 0x08421) || (w == 0x108420) || (w == 0x108421)) 
      return 1;
    v=v>>1;
  }
  v=u;
  for (i=1; i <= 5; i++){
    w = 0x01f&v;
    if(!w&mv[i]) continue;

    if ((w == 0x01f) || (w == 0x0f) || (w == 0x1e)) 
      return 1;
    v=v>>5;
  }
  v=u;
  w = 0x1041041&v;
  if ((w == 0x1041041) || (w == 0x1041040) || (w == 0x041041) 
                  || ((0x082082&v) == 0x082082) || ((0x820820&v) == 0x820820)) 
      return 1;

  w = 0x111110&v;
  if ((w == 0x111110) || (w == 0x111100) || (w == 0x011110)
                    || ((0x222200&v) == 0x222200) || ((0x8888&v) == 0x8888)) 
      return 1;


  return 0; 
}


// this is the wrapper for the gui
double
computer_run(unsigned int b1, unsigned int b2) {
  int deep, v;
 
   deep=25-Count(b1|b2);

   
  if(deep == 25){
  
    mossa2 = 0x1000;
    return 0;
  }
  if(deep == 24){
 
    if(!(0x1000&(b1|b2))){
  
       mossa2 = 0x1000;
        return 0;
    }
    else if(!(0x100&(b1|b2))){

      mossa2=0x100;
      return 0;
    }
    else if(!(0x40 &(b1|b2))){
       mossa2=0x40;
       return 0;
    }
    else if(!(0x10000 &(b1|b2))){
       mossa2=0x10000;
       return 0;
    }
    else if(!(0x40000 &(b1|b2))){
        mossa2=0x40000;
        return 0;
    }
  }
 
  

  deep=(deep > DP)? DP:deep;
    init_computer_alghoritm();
    if(deep>4)
      {
         v=valuta (b1,b2,4,-2000,2000,4);
         if(v)
            return v;
	 
         mv[1]=mossa2;
      }
  max_dep=0;	  
  v=valuta(b1,b2,deep,-2000,2000,deep);

  return v;

}


int
valuta(unsigned int a,unsigned int b,int depth, int alpha, int beta,int MAXD) {
  unsigned int i,moves,res;
  int val,w;


  if( (depth==0)) 
    return 0;
  
  moves = ~(a|b);
 

  i=1;
  val=0;
 
 
  while(i <= 25){

    if (moves & mv[i]){ 
      res = a|mv[i];

      w = position(res,i);
      if (w) {
	val=depth;
	if (depth==0) return w;
      }
      else val = -valuta (b,res,depth-1,-beta,-alpha,MAXD);


      if (val >= beta)
      	return beta;
      if (val > alpha){
	alpha = val;
      	if(depth==MAXD) mossa2 = mv[i]; 

      }

    }

    i++;
  }
  //  if(depth>max_dep){printf("%d\n",depth); max_dep=depth;}
  return alpha; 
}



int Count (unsigned int w)
{
   w = (0x55555555 & w) + (0x55555555 & (w>> 1));
   w = (0x33333333 & w) + (0x33333333 & (w>> 2));
   w = (0x0f0f0f0f & w) + (0x0f0f0f0f & (w>> 4));
   w = (0x00ff00ff & w) + (0x00ff00ff & (w>> 8));
   w = (0x0000ffff & w) + (0x0000ffff & (w>>16));
   return w;
}
