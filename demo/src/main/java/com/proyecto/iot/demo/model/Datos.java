package com.proyecto.iot.demo.model;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

import java.time.LocalDate;
import java.time.LocalTime;

@Entity
public class Datos {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private float valorh;
    private float valort;
    private float valorf;
    private float valorhc;
    private float valorhf;

    private LocalDate date;
    private LocalTime time;


    public Datos() {
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public float getValorh() {
        return valorh;
    }

    public void setValorh(float valorh) {
        this.valorh = valorh;
    }

    public float getValort() {
        return valort;
    }

    public void setValort(float valort) {
        this.valort = valort;
    }

    public float getValorf() {
        return valorf;
    }

    public void setValorf(float valorf) {
        this.valorf = valorf;
    }

    public float getValorhc() {
        return valorhc;
    }

    public void setValorhc(float valorhc) {
        this.valorhc = valorhc;
    }

    public float getValorhf() {
        return valorhf;
    }

    public void setValorhf(float valorhf) {
        this.valorhf = valorhf;
    }
    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }
    public LocalTime getTime() {
        return time;
    }

    public void setTime(LocalTime time) {
        this.time = time;
    }
}
