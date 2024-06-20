package com.proyecto.iot.demo.controller;

import com.proyecto.iot.demo.model.Datos;
import com.proyecto.iot.demo.service.DatosService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.*;

import javax.xml.crypto.Data;
import java.time.LocalDate;
import java.time.LocalTime;
import java.util.List;

@RestController
@RequestMapping("/api")
@CrossOrigin
public class DatosController {
    private final DatosService datosService;
    private static final Logger logger = LoggerFactory.getLogger(DatosController.class);

    public DatosController(DatosService datosService) {
        this.datosService = datosService;
        System.out.println("datosService = " + datosService);
        logger.info("New datos : {}", datosService);
    }

    @PostMapping("/datos")
    public String recibirDatos(@RequestBody Datos datos) {
        LocalDate fechactual = LocalDate.now();
        LocalTime time = LocalTime.now();
        logger.info("New datos : {}", datos);
        System.out.println("Datos recibidos y guardados: " +
                datos.getValorhc() + ", " +
                datos.getValorhf() + ", " +
                datos.getValort() + ", " +
                datos.getValorf() + ", " +
                datos.getValorh());
                datos.setDate(fechactual);
                datos.setTime(time);
        datosService.save(datos);
        return "Datos recibidos con éxito";
    }

    @GetMapping("/getAll")
    public List<Data>findall(){
        return datosService.findall();
    }
}