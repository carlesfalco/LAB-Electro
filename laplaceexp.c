#include <stdio.h>


void iteracio (int midax, int miday, double matriu[midax][miday], 
	       double matriuc[midax][miday]);

int main () {
  
  int div = ; //Nombre de divisions a cada cm
  int n = ; //n² nombre de cel·les (28div)x(20div)
  int nx = 28*div; //Nombre total de punts x
  int ny = 20*div; //Nombre total de punts y
  double phi[n*nx][n*ny], phic[n*nx][n*ny]; //Matrius potencial i check de cond inicials
  int i,j;
  int k = 0;
  int nmax = ; //Max iteracions
  
  
  //Inicialitzem matrius
  for (i = 0; i < n*nx; i++) {
    for (j = 0; j < n*ny; j++) {
      phi[i][j] = 0;
      phic[i][j] = 0;
    }
  }
  //Fixem condicions inicials, mostrem els tres casos
  
  //1.Fils: dues circumferencies radi i centres determinats (per n=5 i div=6)
  double radi = div/2.0+3/2.0;
  int y1 = 2*ny+10*div;
  int y2 = 2*ny+10*div;
  int x1 = 2*nx+10*div+div/2.0;
  int x2 = 2*nx+17*div+div/2.0;
  
  for (j=0;j<n*ny;j++) {
    phi[0][j]=0;
    phi[n*nx-1][j]=0;
    phic[0][j]=1;
    phic[n*nx-1][j]=1;
  }
  
  for (i=0;i<n*nx;i++) {
    phi[i][0]=0;
    phi[i][n*ny-1]=0;
    phic[i][0]=1;
    phic[i][n*ny-1]=1;
  }
  
  for (i = 0; i < n*nx; i++) {
    for (j = 0; j < n*ny; j++) {
      if ( (x1-i)*(x1-i)+(y1-j)*(y1-j)<radi*radi ) {
	phi[i][j] = -7.5;
	phic[i][j] = 1;
      }
      
      if ( (x2-i)*(x2-i)+(y2-j)*(y2-j)<radi*radi ) {
	phi[i][j] = +7.5;
	phic[i][j] = 1;
      }
    }
  }
  
   //2. Condensador: plaques a potencial constant (per n=5 i div=6)
   
  for (j = 2*ny+6*div; j < 2*ny+14*div; j++) {
    phi[2*nx+17*div+1][j] = -7.5;
    phi[2*nx+17*div][j] = -7.5;
    phi[2*nx+11*div-1][j] = 7.5;
    phi[2*nx+11*div][j] = 7.5;
    phic[2*nx+17*div][j] = 1;
    phic[2*nx+17*div+1][j] = 1;
    phic[2*nx+11*div-1][j] = 1;
    phic[2*nx+11*div][j] = 1;
  }
  //3. Pel cas lliure trobem les equacions de les rectes de la configuració i procedim igual
  //S'ha fet n=1 perque fora el potencial ja era zero.
  //En aquest cas s'han girat nx=20*div i ny=28*div, així com i i j
   //Quadrat exterior
  for (j = 9*div; j < 19*div; j++) {
    phi[15*div][j] = -1;
    phi[5*div][j] = -1;
    phic[15*div][j] = 1;
    phic[5*div][j] = 1;
  }
  
  for (i = 5*div; i < 15*div; i++) {
    phi[i][9*div] = -1;
    phi[i][19*div] = -1;
    phic[i][9*div] = 1;
    phic[i][19*div] = 1;
  }
  
  //Triangle interior
  for (j = 12*div; j < 16*div; j++) {
    phi[9*div][j] = 1;
    phic[9*div][j] = 1;
  }
  for (j = 12*div; j < 14*div; j++) {
    if (j%2 == 0) { //Comprovem que te sentit
      phi[3*j/2-9*div][j] = 1;
      phic[3*j/2-9*div][j] = 1;
    }
  }
  
  for (j = 14*div; j < 16*div; j++) {
    if (j%2 == 0) { //Comprovem que te sentit
      phi[-3*j/2+33*div][j] = 1;
      phic[-3*j/2+33*div][j] = 1;
    }
  }
  //Apliquem l'algorisme
  while em (k < nmax) {
    iteracio(n*nx,n*ny,phi,phic);
    k++;
  }
  
  //Escrivim el resultat en un fitxer
  FILE* sortida;
   sortida = fopen("filspot.dat","w");
   if(sortida == NULL) {
         printf("ERROR: aquest fitxer no es pot obrir\n");
         return 1;
   }
     
for(i = 0; i < n*nx; i++){
    for(j = 0; j < n*ny; j++){
         fprintf(sortida," %lf \n",phi[i][j]);
    }
}
     
fclose(sortida); 

return 0; //Acaba el main
}

void iteracio (int midax, int miday, double matriu[midax][miday], double matriuc[midax][miday]) {
   int i,j;
   double w = 1.8; //Parametre de relaxacio, accelera la convergencia 1<w<2
   
   for (i = 0; i < midax-1; i++) {
    for (j = 0; j < miday-1; j++) {
      if (matriuc[i][j] != 1) { //check no es cond inicial, punt fix
	matriu[i][j] =(1-w)*matriu[i][j]+w*(matriu[i+1][j] + matriu[i-1][j] + matriu[i][j-1]+ matriu[i][j+1])/4.0;
          //Sense parametre de relaxacio es simplement la mitjana
      }
    }
  }
}