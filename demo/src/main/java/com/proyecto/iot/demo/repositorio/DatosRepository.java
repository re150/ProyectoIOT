package com.proyecto.iot.demo.repositorio;

import com.proyecto.iot.demo.model.Datos;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface DatosRepository extends JpaRepository<Datos,Integer> {
}
