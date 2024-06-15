package com.proyecto.iot.demo.model;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class Datos {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)  // Auto Increment
    private int id;

    /*public Datos(float valor) {
        this.valor = valor;
    }*/

    private float valor;

    // Getters y Setters
    public float getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public float getValor() {
        return valor;
    }

    public void setValor(float valor) {
        this.valor = valor;
    }
}
