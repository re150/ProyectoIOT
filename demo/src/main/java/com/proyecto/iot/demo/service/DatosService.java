package com.proyecto.iot.demo.service;

import java.util.List;

public interface DatosService<T> {
    T save(T t);

    List<T> findall();
}