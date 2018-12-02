import numpy as np
#Funcio que fa el -gradient d'un camp escalar

def gradient(pot,cx,cy,delta): 
    for i in range(0,len(pot)-1):
        for j in range(0,len(pot[0])-1):
            cx[i][j] = -1/delta*(pot[i+1][j]-pot[i][j])
            cy[i][j] = -1/delta*(pot[i][j+1]-pot[i][j])

#Funcio que calcula la direccio del camp electric 
#entre dos punts d'una línia equipotencial

def campelectric(vv,E): 
    v=vv.transpose()

    for i in range(0,len(v)-1):
        x=(v[i][0]+v[i+1][0])/2
        y=(v[i][1]+v[i+1][1])/2
        a=(v[i+1][1]-v[i][1]);
        b=(v[i+1][0]-v[i][0]);
        n=np.sqrt(a*a+b*b)
        if n==0:
            n=1
        E[i][0]=x
        E[i][1]=y
        E[i][2]=-a/n
        E[i][3]=b/n