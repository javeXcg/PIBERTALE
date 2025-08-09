#include "raylib.h"
#include "raygui.h"  
#include "globals.h"

#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> adaptar_dialogo(const std::string& dialogo, size_t limite) {
    std::vector<std::string> partes;
    size_t start = 0;
    size_t n = dialogo.size();

    while (start < n) {
        if (n - start <= limite) {
            partes.push_back(dialogo.substr(start));
            break;
        }

        size_t end = start + limite;
        if (end >= n) end = n - 1;

        if (dialogo[end] != ' ' && dialogo[end] != '\0') {
            size_t space_pos = dialogo.rfind(' ', end);
            if (space_pos == std::string::npos || space_pos < start) {
                space_pos = dialogo.find(' ', end);
                if (space_pos == std::string::npos) {
                    partes.push_back(dialogo.substr(start));
                    break;
                }
                end = space_pos;
            } else {
                end = space_pos;
            }
        }

        partes.push_back(dialogo.substr(start, end - start));

        start = end;
        while (start < n && dialogo[start] == ' ') start++;
    }

    // Asegurar al menos 5 partes llenando con strings vacíos si hace falta
    while (partes.size() < 5) {
        partes.push_back("");
    }

    return partes;
}