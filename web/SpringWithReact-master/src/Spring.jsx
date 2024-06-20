import React, { useState, useEffect } from 'react';
import { Line } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from 'chart.js';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

export const Spring = () => {
    const [datos, setDatos] = useState([]);
    
    useEffect(() => {
        const fetchData = () => {
            fetch('http://localhost:8080/api/getAll')
                .then(response => response.json())
                .then(data => {
                    const lastTenData = data.slice(-10);
                    setDatos(lastTenData);
                })
                .catch(error => console.error("Error fetching data: ", error));
        };
    
        fetchData(); 
    
        const interval = setInterval(fetchData, 10000); 
    
        return () => clearInterval(interval);
    }, []);
    const options = {
        responsive: true,
        plugins: {
            legend: {
                position: 'top',
            },
            title: {
                display: true,
                text: 'Datos',
            },
        },
    };

    const createChartData = (label, data) => ({
        labels: data.map((_, index) => `Registro ${index + 1}`),
        datasets: [
            {
                label: label,
                data: data,
                fill: false,
                borderColor: 'rgb(75, 192, 192)',
                backgroundColor: 'rgba(75, 192, 192, 0.5)',
            },
        ],
    });

    return (
        <div className="container">
            {datos.length > 0 && (
                <>
                    <div className="row">
                        <div className="col-md-6 offset-md-3"> {/* Add offset-md-3 to center the graph */}
                            <Line options={options} data={createChartData('Humeda', datos.map(dato => dato.valorh), datos.map(dato => dato.fechaHora))} />
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-md-6">
                        <Line options={options} data={createChartData('Temperata en  °C', datos.map(dato => dato.valort), datos.map(dato => dato.fechaHora))} />
                        </div>
                        <div className="col-md-6">
                            <Line options={options} data={createChartData('Temperata en  °F', datos.map(dato => dato.valorf), datos.map(dato => dato.fechaHora))} />
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-md-6">
                            <Line options={options} data={createChartData('Indice de calor en °C', datos.map(dato => dato.valorhc), datos.map(dato => dato.fechaHora))} />
                        </div>
                        <div className="col-md-6">
                            <Line options={options} data={createChartData('Indice de calor en °F', datos.map(dato => dato.valorhf), datos.map(dato => dato.fechaHora))} />
                        </div>
                    </div>
                </>
            )}
        </div>
    );
};
