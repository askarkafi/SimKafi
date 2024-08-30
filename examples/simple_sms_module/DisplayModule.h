#ifndef DISPLAYMODULE_H
#define DISPLAYMODULE_H

class DisplayModule {
public:
    void begin();
    void show(const char* Message);
    void showSignal(int signal);
};

#endif
