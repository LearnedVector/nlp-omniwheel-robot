import serial 
import time

def Motion(Vx, Vy, W0):
     R=3;
     L=12.75;
     W0=(Vy+Vx-L*W0)/R;
     W1=(Vy-Vx+L*W0)/R;
     W2=(Vy-Vx-L*W0)/R;
     W3=(Vy+Vx+L*W0)/R;
     return W0, W1, W2, W3

print ("")
#serialKiller = serial.Serial('/dev/ttyUSB0',9600)



#serialKiller.write(b'\x01')
#serialKiller.write(b'\x05')
#serialKiller.write(b'\x09')
#serialKiller.write(b'\x0D')
#serialKiller.write(b'\x3F')

#time.sleep(2)

#serialKiller.write(b'\x01')
#serialKiller.write(b'\x05')
#serialKiller.write(b'\x09')
#serialKiller.write(b'\x0D')
#serialKiller.write(b'\x00')
#time.sleep(1);
##time.sleep(1);
