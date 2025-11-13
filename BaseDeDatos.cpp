#include "BaseDeDatos.h"
#include <filesystem>
#include <sstream>

BaseDeDatos::BaseDeDatos() : jsonCargado(false) {}

void BaseDeDatos::conectar(const std::string& ruta) {
    rutaBD = ruta;
    datos.clear();
    datosJSON.clear();
    jsonCargado = false;

    namespace fs = std::filesystem;
    fs::path p(ruta);

    if (!fs::exists(p)) {
        std::cerr << "Ruta no existe: " << ruta << std::endl;
        return;
    }

    if (fs::is_directory(p)) {
        for (const auto& ent : fs::directory_iterator(p)) {
            if (ent.is_regular_file()) {
                if (ent.path().extension() == ".txt") {
                    cargarDatos(ent.path(), ent.path().filename().string());
                } else if (ent.path().extension() == ".json") {
                    cargarJSON(ent.path());
                }
            }
        }
    } else if (fs::is_regular_file(p)) {
        if (p.extension() == ".txt") {
            cargarDatos(p, p.filename().string());
        } else if (p.extension() == ".json") {
            cargarJSON(p);
        } else {
            std::cerr << "Ruta no es un .txt, .json ni un directorio: " << ruta << std::endl;
        }
    }
}

void BaseDeDatos::desconectar() {
    datos.clear();
    datosJSON.clear();
    jsonCargado = false;
}

void BaseDeDatos::cargarDatos(const std::filesystem::path& ruta, const std::string& nombreArchivo) {
    std::ifstream archivo(ruta);
    std::string linea;
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir: " << ruta << std::endl;
        return;
    }
    while (std::getline(archivo, linea)) {
        datos[nombreArchivo].push_back(linea);
    }
    archivo.close();
}

void BaseDeDatos::cargarJSON(const std::filesystem::path& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir JSON: " << ruta << std::endl;
        return;
    }
    
    try {
        archivo >> datosJSON;
        jsonCargado = true;
        archivo.close();
        std::cout << "JSON cargado y parseado exitosamente desde: " << ruta << std::endl;
    } catch (json::parse_error& e) {
        std::cerr << "Error al parsear JSON: " << e.what() << std::endl;
        jsonCargado = false;
        archivo.close();
    }
}

const std::map<std::string, std::vector<std::string>>& BaseDeDatos::obtenerDatos() const {
    return datos;
}

std::vector<std::string> BaseDeDatos::obtenerLineas(const std::string& nombreArchivo) const {
    auto it = datos.find(nombreArchivo);
    if (it != datos.end()) return it->second;
    return {};
}

json BaseDeDatos::obtenerJSONParseado() const {
    return datosJSON;
}

std::string BaseDeDatos::obtenerJSONString() const {
    return datosJSON.dump(4);  // Formateado con 4 espacios
}

bool BaseDeDatos::tieneJSON() const {
    return jsonCargado;
}

// Métodos específicos para la panadería
json BaseDeDatos::obtenerIngredientes() const {
    if (jsonCargado && datosJSON.contains("ingredientes")) {
        return datosJSON["ingredientes"];
    }
    return json::array();
}

json BaseDeDatos::obtenerRecetas() const {
    if (jsonCargado && datosJSON.contains("recetas")) {
        return datosJSON["recetas"];
    }
    return json::array();
}

json BaseDeDatos::obtenerPanes() const {
    if (jsonCargado && datosJSON.contains("panes")) {
        return datosJSON["panes"];
    }
    return json::array();
}

// Buscar elementos específicos
json BaseDeDatos::buscarIngrediente(const std::string& nombre) const {
    if (!jsonCargado) return json();
    
    auto ingredientes = obtenerIngredientes();
    for (const auto& ing : ingredientes) {
        if (ing["nombre"] == nombre) {
            return ing;
        }
    }
    return json();
}

json BaseDeDatos::buscarReceta(const std::string& nombre) const {
    if (!jsonCargado) return json();
    
    auto recetas = obtenerRecetas();
    for (const auto& rec : recetas) {
        if (rec["nombre"] == nombre) {
            return rec;
        }
    }
    return json();
}

json BaseDeDatos::buscarPan(const std::string& nombre) const {
    if (!jsonCargado) return json();
    
    auto panes = obtenerPanes();
    for (const auto& pan : panes) {
        if (pan["nombre"] == nombre) {
            return pan;
        }
    }
    return json();
}
