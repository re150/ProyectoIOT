package com.proyecto.iot.demo.service;

import com.proyecto.iot.demo.model.Datos;
import com.proyecto.iot.demo.repositorio.DatosRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;


@Service
public class DatosServiceImpl implements DatosService<Datos>{
    @Autowired
    private DatosRepository datosRepository;
    @Override
    public Datos save(Datos datos) {
        return datosRepository.save(datos);
    }
}
