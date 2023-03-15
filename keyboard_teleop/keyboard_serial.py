PORT='/dev/ttyUSB1' # update after checking arduino port
baud=9600

import pygame
import serial
import time

def pygameSetup():
    pygame.init()
    screen = pygame.display.set_mode((1500, 90))    

    background = pygame.Surface(screen.get_size())
    background = background.convert()
    background.fill((250, 250, 250))

    if pygame.font:
        font = pygame.font.Font(None, 36)
        text = font.render(
            "f/r = forward/reverse mode || SPACE/n = FRONT BREAK ENGAGE || b = FRONT BREAK DISENGAGE || 5/./BACKSPACE = REAR BREAK || KP0/KP+ = REAR BREAK DISENGAGE", 1, (10, 10, 10))
        textpos = text.get_rect(centerx=background.get_width()/2, centery=background.get_height()/2)
        background.blit(text, textpos)

    screen.blit(background, (0, 0))
    pygame.display.flip()

# For steering and brakes
def onePressControl(port):
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if (event.key == pygame.K_ESCAPE):
                port.write(b'x') #interrupt update when exit teleop/auto mode
                print("sent x for exiting teleop mode")
                pygame.quit()
                return

            elif (event.key == pygame.K_h):
                port.write(b'H')
                print("Requested Homing")
                
            elif (event.key == pygame.K_LEFT or event.key == pygame.K_a or event.key== pygame.K_KP4):
                port.write(b'l')
                print("handle left")

            elif (event.key == pygame.K_RIGHT or event.key == pygame.K_d or event.key == pygame.K_KP6):
                port.write(b'r')
                print("handle right")

            elif (event.key == pygame.K_b):  # front break diseanagae
                port.write(b'b')
                print("brake disengaged")

            elif(event.key == pygame.K_SPACE or event.key == pygame.K_n): #engage
                port.write(b'n')
                print("n ->    front break")

            elif(event.key == pygame.K_KP_PERIOD or event.key == pygame.K_KP5 or event.key == pygame.K_BACKSPACE):  # rear break
                port.write(b'z')
                print("pressed period/5 -> Rear brake engage")

            elif(event.key == pygame.K_KP0 or event.key == pygame.K_KP_PLUS):
                port.write(b'Z')
                print("pressed keypad 0 -> rear brake disengage")
            
            elif(event.key == pygame.K_r):
                port.write(b'o')
                print("sent o, reverse mode")
            
            elif(event.key == pygame.K_f):
                port.write(b'c')
                print("sent c, forward mode")
            # elif( event.key == pygame.K_UP or event.key == pygame.K_w ):
            #         port.write(b'h')
            #         print("pressed Up")
                    
            # elif( event.key == pygame.K_DOWN or event.key == pygame.K_s):
            #         port.write(b'j')
            #         print("Pressed Down")

            elif(event.key == pygame.K_KP_ENTER):
                print("stop")
                port.write(b's')


# Only for Throttle
def continuousControl(keys, port):
    flag = 1
    

    if(keys[pygame.K_UP] or keys[pygame.K_w]):
        port.write(b'h')
        print("pressed Up")
        time.sleep(0.01)
                    
    elif(keys[pygame.K_DOWN] or keys[pygame.K_s]):
        port.write(b'j')
        print("Pressed Down")
        time.sleep(0.01)

    elif(keys[pygame.K_SPACE]):
        port.write(b'q')
        print("space -> throttle = 0")

    elif(flag and keys[pygame.K_KP_ENTER]):
        port.write(b's')
        print("stop")
        flag = 0

    else:
        flag = 1


def main():
    pygameSetup()
    initialized = False

    while not initialized:
        try:
            mega = serial.Serial(PORT, baud)  # steer and break arduino port #changed to single arduino mega
            # uno = serial.Serial("COM5", 9600)  # throttle arduino port
            initialized = True
            print("serial up")
        except:
            print("waiting for serial")
            time.sleep(1)
            return

    while True:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return
        keys = pygame.key.get_pressed()
        onePressControl(mega)
        continuousControl(keys, mega)


if __name__ == '__main__':
    main()
