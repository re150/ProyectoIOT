package com.proyecto.iot.demo.controller;

import com.proyecto.iot.demo.model.Datos;
import com.proyecto.iot.demo.service.DatosService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api") // Uncommented for clarity
@CrossOrigin // Uncommented for clarity
public class DatosController {
    private final DatosService datosService;
    private static final Logger logger = LoggerFactory.getLogger(DatosController.class);

    public DatosController(DatosService datosService) {
        this.datosService = datosService;
    }

    @PostMapping("/datos")
    public String recibirDatos(@RequestBody Datos datos) {
        logger.info("New datos : {}", datos);
        datosService.save(datos);
        System.out.println("Datos recibidos: " + datos.getValor());
        return "Datos recibidos con éxito";
    }
}