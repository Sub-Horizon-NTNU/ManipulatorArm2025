#ifndef MANUALCONTROLLER_HPP
#define MANUALCONTROLLER_HPP

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

class ManualController {
public:
    ManualController() {
        angle_ = 0;
        speed_ = 0;
        error_ = true;
    }

    void changeAngleSpeed(const char character){
        //Endrer vinkel utifra insendte tegn, 0.25 gjør at det er 200 steg fra 0 til 50
        if (not error_){
            //Opp hvis w trykkes på
            if (character == 119 && angle_ < 50){
                angle_ += 0.25;
            //Ned hvis s trykkes på
            } else if (character == 115 && angle_ > 0) {
                angle_ -= 0.25;
            //Senk fart hvis a trykkes på
            } else if (character == 97 && speed_ > -100){
                speed_ -= 1;
            //Øk fart hvis d trykkes på
            } else if (character == 100 && speed_ < 100 ){
                speed_ += 1;
            //0 for å gå til startposisjon
            } else if (character == 48){
                speed_ = 0;
                angle_ = 0;
            }
        }
        //Space er for å skru av/på error modus som muliggjør bevegelse
        if (character == 32){
            error_ = not error_;
        }
    }

    int getSpeed(){
        return speed_;
    }

    float getAngle(){
        return angle_;
    }

private:
    float angle_;
    int speed_;
    bool error_; 
};

#endif //MANUALCONTROLLER_HPP