
#ifndef CONTROLADORGENERAL_H
#define CONTROLADORGENERAL_H

#include "Panadero.h"
#include "EncargadoInventario.h"
#include "Administrador.h"
#include "BaseDeDatos.h"
#include "../Modelo/InventarioIngredientes.h"
#include "../Modelo/InventarioPanes.h"
#include "../Modelo/Recetas.h"
#include <vector>

class ControladorGeneral {
private:
    Panadero panadero;
    EncargadoInventario encargadoInventario;
    Administrador administrador;
    BaseDeDatos baseDatos;

    InventarioIngredientes inventarioIngredientes;
    InventarioPanes inventarioPanes;
    std::vector<Recetas> recetas;

public:
    ControladorGeneral();

    // Sólo estas tres funciones públicas: la Vista llamará a una de ellas
    void ejecutarMenuPanadero(int opcion);
    void ejecutarMenuEncargado(int opcion);
    void ejecutarMenuAdministrador(int opcion);
};

#endif // CONTROLADORGENERAL_H

/*
===============================================================================
                                TARJETA CRC
===============================================================================
Nombre de la clase:       ControladorGeneral
Responsabilidades:        
    Se encarga de mostrar el menu, dependiendo del usuario que lo solicite.
    Ejecuta el meno correspondiente al usuario con sus propias accciones.

===============================================================================
*/
