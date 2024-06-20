package com.proyecto.iot.demo.service;

import com.proyecto.iot.demo.model.Datos;
import com.proyecto.iot.demo.repositorio.DatosRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.xml.crypto.Data;
import java.util.List;

@Service
public class DatosServiceImpl implements DatosService<Datos> {
    private final DatosRepository datosRepository;

    @Autowired
    public DatosServiceImpl(DatosRepository datosRepository) {
        this.datosRepository = datosRepository;
    }

    @Override
    public Datos save(Datos datos) {
        return datosRepository.save(datos);
    }

    @Override
    public List<Datos> findall() {
        List<Datos> alldata = datosRepository.findAll();
        return datosRepository.findAll();
    }
}