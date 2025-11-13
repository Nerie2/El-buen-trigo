#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <filesystem>
#include "json.hpp"

using json = nlohmann::json;

class BaseDeDatos {
private:
    std::string rutaBD;
    std::map<std::string, std::vector<std::string>> datos;
    json datosJSON;  // JSON parseado
    bool jsonCargado;

    void cargarDatos(const std::filesystem::path& ruta, const std::string& nombreArchivo);
    void cargarJSON(const std::filesystem::path& ruta);

public:
    BaseDeDatos();
    // conectar puede recibir una carpeta (lee todos los .txt/.json) o un solo archivo
    void conectar(const std::string& ruta);
    void desconectar();

    // Métodos para archivos TXT (compatibilidad)
    const std::map<std::string, std::vector<std::string>>& obtenerDatos() const;
    std::vector<std::string> obtenerLineas(const std::string& nombreArchivo) const;
    
    // Métodos para trabajar con JSON
    json obtenerJSONParseado() const;
    std::string obtenerJSONString() const;
    bool tieneJSON() const;
    
    // Métodos específicos para la panadería
    json obtenerIngredientes() const;
    json obtenerRecetas() const;
    json obtenerPanes() const;
    
    // Buscar elementos específicos
    json buscarIngrediente(const std::string& nombre) const;
    json buscarReceta(const std::string& nombre) const;
    json buscarPan(const std::string& nombre) const;
};

#endif
