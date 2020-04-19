#ifndef screen_diagnostic_h
#define screen_diagnostic_h

#include "screen.h"

class ScreenDiagnostic {
    public:
        ScreenDiagnostic(Screen *screen);
        ScreenDiagnostic() = default;
        void test();
    private:
        Screen *screen;
        unsigned short int ledCount;
};
#endif
