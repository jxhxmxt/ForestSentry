import React from 'react';
import MapView from './MapView';

// Mock data (replace with real data from the API)
const mockData = [
    {
        "humidity": 45.2,
        "temperature": 26.5,
        "smokeLevel": 350,
        "rainStatus": 0,
        "alertLevel": 1,
        "latitude": -34.60,
        "longitude": -58.38,
        "deviceID": "d1"
    },
    {
        "humidity": 45.2,
        "temperature": 26.5,
        "smokeLevel": 350,
        "rainStatus": 0,
        "alertLevel": 1,
        "latitude": 23.55,
        "longitude": 46.63,
        "deviceID": "d1"
    },
    // Add more 
];

const HomeView = () => {
    return (
        <>
            <h1 className="fixed top-0 left-0 bg-white z-10 p-4 shadow-md">ForestSentry</h1>
            <div className="mt-16">
                <MapView data={mockData} />
            </div>
        </>
    );
};

export default HomeView;
