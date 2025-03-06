#ifndef KEYLOGGER_HPP
#define KEYLOGGER_HPP

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class KeyLogger {
public:
    KeyLogger() {
        tcgetattr(STDIN_FILENO, &m_original_settings);
        
        termios new_settings = m_original_settings;
        new_settings.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
        new_settings.c_cc[VMIN] = 1;
        new_settings.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    }

    ~KeyLogger() {
        // Restore original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &m_original_settings);
    }

    char checkKeyPressed() {
        char character = '\0';
        if(read(STDIN_FILENO, &character, 1) > 0) {
            //Reagerer bare på wasd, 0, space og escape, reagerer ikke på wasd med store bokstaver
            if (character == 119 || character == 97 || 
                character == 115 || character == 100 || 
                character == 27 || character == 48 ||
                character == 32){
                return character;
            } else{
                return '\0';
            }
        }
        return '\0';
    }

private:
    termios m_original_settings;
};

#endif // KEYLOGGER_HPP