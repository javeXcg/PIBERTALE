#include "raylib.h"
#include "raygui.h"  
#include "globals.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#if defined(_WIN32) || defined(_WIN64)
#include "json.hpp"
using json = nlohmann::json;
#else
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#endif
#include <sstream> // Necesario para std::istringstream

std::vector<std::string> adaptar_dialogo(const std::string& dialogo, size_t limite) {
    std::vector<std::string> lineas;
    std::istringstream iss(dialogo);
    std::string palabra;
    std::string linea_actual;

    while (iss >> palabra) {
        // Si la línea está vacía, añadimos la palabra directamente
        if (linea_actual.empty()) {
            linea_actual = palabra;
        } 
        // Si al agregar la palabra se pasa del límite, guardamos la línea y empezamos una nueva
        else if (linea_actual.size() + 1 + palabra.size() > limite) {
            lineas.push_back(linea_actual);
            linea_actual = palabra;
        } 
        // Si entra, agregamos con espacio
        else {
            linea_actual += " " + palabra;
        }
    }

    // Guardar última línea si no está vacía
    if (!linea_actual.empty()) {
        lineas.push_back(linea_actual);
    }

    // Rellenar hasta tener 5 líneas en total (índices 0..4)
    while (lineas.size() < 5) {
        lineas.push_back(" ");
    }

    return lineas;
}

std::vector<std::string> tomarDialogosDeJson(const std::string& rutaArchivo) {
    std::vector<std::string> dialogos;

    // Abrir el archivo
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo JSON" << std::endl;
        return dialogos;
    }

    // Parsear el JSON desde el archivo
    json j;
    archivo >> j;

    // Recorrer el array y extraer "TEXTO"
    for (auto& elemento : j) {
        if (elemento.contains("TEXTO")) {
            dialogos.push_back(elemento["TEXTO"]);
        }
    }

    return dialogos;
}

void dialogoDelTurno(int turno, const std::vector<std::string>& dialogos) {
    if (turno < dialogos.size()) {
        auto lineas = adaptar_dialogo(dialogos[turno], 40); // límite de 40 caracteres por ejemplo
        texto_caja1 = lineas[0];
        texto_caja2 = lineas[1];
        texto_caja3 = lineas[2];
        texto_caja4 = lineas[3];
        texto_caja5 = lineas[4];
    }
}

