#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Joystick Input");

    // Joystick-Verbindung überprüfen
    if (!sf::Joystick::isConnected(0)) {
        std::cout << "Kein Joystick verbunden!" << std::endl;
        return 1;
    }

    HANDLE serialHandle;

    serialHandle = CreateFile(L"\\\\.\\COM5", GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);

    GetCommState(serialHandle, &serialParams);
    serialParams.BaudRate = 9600;
    serialParams.ByteSize = 8;
    serialParams.StopBits = TWOSTOPBITS;
    serialParams.Parity = NOPARITY;
    SetCommState(serialHandle, &serialParams);

    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 50;
    timeout.ReadTotalTimeoutConstant = 50;
    timeout.ReadTotalTimeoutMultiplier = 50;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;

    SetCommTimeouts(serialHandle, &timeout);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Beenden des Programms beim Schließen des Fensters
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Abrufen der X-Achsenposition
            int xAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::X) + 100;
            int gas = sf::Joystick::getAxisPosition(0, sf::Joystick::Z) + 100;

            // Ausgabe der Position auf der Konsole
            std::cout << "X-Achsenposition: " << xAxis << " Z dings: " << gas << std::endl;

            // Convert integer values to strings
            std::string xAxisStr = std::to_string(xAxis);
            std::string gasStr = std::to_string(gas);

            xAxisStr = "1" + xAxisStr;
            gasStr = "2" + gasStr;
            std::cout << xAxisStr << " " << gasStr;

            // Send data over the serial port
            DWORD bytesWritten;
            WriteFile(serialHandle, xAxisStr.c_str(), xAxisStr.length(), &bytesWritten, NULL);
            WriteFile(serialHandle, " ", 1, &bytesWritten, NULL); // Separator
            WriteFile(serialHandle, gasStr.c_str(), gasStr.length(), &bytesWritten, NULL);
            WriteFile(serialHandle, "\n", 1, &bytesWritten, NULL); // New line
        }

        window.clear();

        window.display();
    }

    return 0;
}