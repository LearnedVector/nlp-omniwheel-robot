import serial 
import time
import struct

def Motion(Vx, Vy, W):
     R=3;
     L=13;
     W0=(Vy+Vx-L*W);
     W1=(Vy-Vx+L*W);
     W2=(Vy-Vx-L*W);
     W3=(Vy+Vx+L*W);
     return W0, W1, W2, W3

W0,W1,W2,W3=Motion(0, 255, 0);
SPD=abs(W0);
print ("W0: ", W0, "W1", W1, "W2", W2, "W3", W3, "SPD", SPD, "")

if (W0>0):
     W0=0x01;
else:
     W0=0x02;

if (W1>0):
     W1=0x05;
else:
     W1=0x06; 

if (W2>0):
     W2=0x09;
else:
     W2=0x0A;

if (W3>0):
     W3=0x0D;
else:
     W3=0x0E;


print ("W0: ", W0, "W1", W1, "W2", W2, "W3", W3, "SPD", SPD, "")


serialKiller = serial.Serial('/dev/ttyUSB0',9600)


#W0=0x01;
#W1=0x05;
#W2=0x09;
#W3=0x0D;
serialKiller.write(bytes(W0, encoding="utf-8"))
serialKiller.write(bytes(W1, encoding="utf-8"))
serialKiller.write(bytes(W2, encoding="utf-8"))
serialKiller.write(bytes(W3, encoding="utf-8"))
#serialKiller.write(bytes(SPD, encoding="utf-8"))
serialKiller.write(b'\xFF')

time.sleep(2)

