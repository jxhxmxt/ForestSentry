import React from 'react';
import { MapContainer, TileLayer, Marker, Popup } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';
import L from 'leaflet';

// Custom marker icon
const icon = new L.Icon({
    iconUrl: 'https://unpkg.com/leaflet@1.7.1/dist/images/marker-icon.png',
    iconSize: [25, 41],
    iconAnchor: [12, 41],
    popupAnchor: [1, -34],
    shadowUrl: 'https://unpkg.com/leaflet@1.7.1/dist/images/marker-shadow.png',
    shadowSize: [41, 41]
});

// receives a list of data points as props (data)
const MapView = ({ data }) => {
    
    console.log("el mock de verdad")
    console.log(data)
    return (
        <MapContainer center={[data[0].latitude, data[0].longitude]} zoom={15} style={{ height: '100vh', width: '75%' }}>
            <TileLayer
                url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
            />
            {/*  Create a Marker for each data point */}
            {data.map((point, index) => (
                <Marker key={index} position={[point.latitude, point.longitude]} icon={icon}>
                    {/*  Add a Popup card with the data point's information */}
                    <Popup>
                        <div>
                            <p>Humidity: {point.humidity}%</p>
                            <p>Temperature: {point.temperature}°C</p>
                            <p>Smoke Level: {point.smokeLevel}</p>
                            <p>Rain Status: {point.rainStatus}</p>
                            <p>Alert Level: {point.alertLevel}</p>
                            <p>Device ID: {point.deviceID}</p>
                        </div>
                    </Popup>
                </Marker>
            ))}
        </MapContainer>
    );
};

export default MapView;
