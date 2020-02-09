// CANTestBench.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "KvaserCanInterface.h"

int main()
{
    KvaserCanInterface iface = KvaserCanInterface();
    actionStatus status = iface.initialize();
    if (status == actionStatus::OK) {
        for (auto& chan : iface.channels()) {
            std::cout << "Test " << chan.get()->name() << " ## " << chan.get()->vChannel() << std::endl;
        }
    }
}
