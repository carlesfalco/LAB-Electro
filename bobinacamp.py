from scipy.integrate import quad, dblquad #Funcio que fa dobles integrals
import numpy as np

muo=4.*np.pi*10**(-7)

#La variable rho és la distància del punt on es calcula el camp fins a l'eix z (suposat eix paral·lel a la bobina)
#La variable z és l'alçada del punt on es calcula el camp
#La variable d és l'alçada del centre de l'espira corresponent
#La variable R és el radi de les espires

#Expressions prèvies a la integral:
def IntBr(theta,R,z,d,rho):
    return np.cos(theta)*(z-d)/((rho-R*np.cos(theta))**2+(R*np.sin(theta))**2+(z-d)**2)**(3./2)

def IntBz(theta,R,z,d,rho):
    return (R-rho*(np.cos(theta)))/((rho-R*np.cos(theta))**2+(R*np.sin(theta))**2+(z-d)**2)**(3./2)

#Integral doble amb bobina centrada a l'origen
def Bz(N,L,R,z,rho,I):
    bz=dblquad(lambda d, theta: IntBz(theta,R,z,d,rho), 0, 2*np.pi, lambda d: -L/2, lambda d: L/2)
    Bztot=bz[0]*R*N*I*muo/4/np.pi
    return Bztot

def Br(N,L,R,z,rho,I):
    br=dblquad(lambda d, theta: IntBr(theta,R,z,d,rho), 0, 2*np.pi, lambda d: -L/2, lambda d: L/2)
    Brtot=br[0]*R*N*I*muo/4/np.pi
    return Brtot

def B(N,L,R,z,rho,I):
    Camp=[Br(N,L,R,z,rho,I),Bz(N,L,R,z,rho,I)]
    return Camp