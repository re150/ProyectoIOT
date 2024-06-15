package com.proyecto.iot.demo.controller;
import com.proyecto.iot.demo.model.Datos;
import com.proyecto.iot.demo.repositorio.DatosRepository;
import com.proyecto.iot.demo.service.DatosService;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.*;
import org.slf4j.Logger;

@RestController
//@RequestMapping("/api")
@CrossOrigin
public class DatosController {
    private DatosService datosService;
    private static final Logger logger = LoggerFactory.getLogger(DatosController.class);
    @PostMapping("/api/datos")
    public String recibirDatos(@RequestBody String  data) {
        float temperatura = Float.parseFloat(data.trim());

        Datos datos = new Datos();
        logger.info("New datos : {}", datos);
        datosService.save(datos);
        System.out.println("Datos recibidos: " + datos.getValor());
        return "Datos recibidos con éxito";
    }
}
