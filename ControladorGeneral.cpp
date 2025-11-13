#include "ControladorGeneral.h"

ControladorGeneral::ControladorGeneral() {}

void ControladorGeneral::ejecutarMenuPanadero(int opcion) {
    if (opcion == 1) {
        panadero.registrarReceta();
    } 
    else if(opcion == 2){
        panadero.registrarPanes();
    }
    else if (opcion == 3){
        panadero.consultarStock();
    }
}

void ControladorGeneral::ejecutarMenuEncargadoInventario(int opcion) {
     if (opcion == 1) {
         encargadoInventario.registrarIngrediente();
    } 
    else if(opcion == 2){
        encargadoInventario.consultarInventario();
    }
    else if (opcion == 3){
        encargadoInventario.verificarNivelMinimo();
    }
}

void ControladorGeneral::ejecutarMenuAdministrador(int opcion) {
    if (opcion == 1) {
        administrador.generarReporte();
    } 
    else if(opcion == 2){
        administrador.exportarReporteTxt();
    }
}
