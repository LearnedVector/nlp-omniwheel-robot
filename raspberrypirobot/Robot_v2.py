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

W0,W1,W2,W3=Motion(0, 100, 0);
print ("W0: ", W0, "W1", W1, "W2", W2, "W3", W3, "")
if (W0>0):
     W0='\x01';
else:
     W0='\x02';

if (W1>0):
     W1='\x05';
else:
     W1='\x06'; 

if (W2>0):
     W2='\x09';
else:
     W2='\x0A';

if (W3>0):
     W3='\x0D';
else:
     W3='\x0E';
     
serialKiller = serial.Serial('/dev/ttyUSB0',9600)
print ("W0: ", W0, "W1", W1, "W2", W2, "W3", W3, "")

#W0='\x01';
#W1=0x05;
#W2=0x09;
#W3=0x0D;
serialKiller.write(bytes(W0, encoding="utf-8"))
serialKiller.write(bytes(W1, encoding="utf-8"))
serialKiller.write(bytes(W2, encoding="utf-8"))
serialKiller.write(bytes(W3, encoding="utf-8"))
serialKiller.write(b'\xFF')

time.sleep(2)

