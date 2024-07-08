import React, { useState, useEffect } from 'react';
import MapView from './MapView';
import API from '../services/GetServices.js';
import sensor from '../assets/sensor.png'
import habilitado from '../assets/habilitar.png'
import humedad from '../assets/humedad.png'
import temperatura from '../assets/temperatura-alta.png'
import humo from '../assets/bomba-de-humo.png'
import locacion from '../assets/alfiler.png'
import lluvia from '../assets/gota-de-agua.png'

// Mock data (replace with real data from the API)


/* const mockData = [
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
]; */

const HomeView = () => {
    const [Mock, SetMock] = useState([
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
    ]);
    useEffect(() => {
        const fetchData = async () => {

            const response = await API.GetLatest();
            console.log("mock");
            console.log(response);
            if (response === null) {
                const newsensor = {
                    "humidity": 45.2,
                    "temperature": 26.5,
                    "smokeLevel": 350,
                    "rainStatus": 20,
                    "alertLevel": 1,
                    "latitude": 23.55,
                    "longitude": 46.63,
                    "deviceID": "d1"
                }

                SetMock([...Mock, newsensor]);
            } else
                SetMock([...Mock, response]);
        }

        fetchData();

        console.log("el mock")
        console.log(Mock)
    }, []);



    return (
        <>
            {/* Top Bar */}
            <div className=" top-0 left-0 right-0 bg-white z-10 py-5 shadow-md flex justify-center items-center">
                <h1 className="text-3xl font-bold">ForestSentry</h1>
            </div>

            <div className='h-screen  flex flex-col overflow-hidden'>
                <div className=' bg-slate-100 flex flex=col w-screen h-screen'>
                    <div className=' mb-2  w-5/6 '>
                        <div className='border-2 border-black  rounded-xl mx-20 py-10 my-10 flex flex-row hover:scale-105 hover:shadow-xl'>
                            <img className='w-28 mx-7' src={sensor} alt="sensor" />
                            <div className='text-3xl font-bold'> <h1 className=''>Bosque de prueba 1</h1>
                                <h1 className='pt-3 px-3'>- 3 sensores activos</h1></div>
                            <div className='px-14 '><h1 className='py-2'>zona sur</h1>
                                <h1 className='py-2'>Lago</h1>
                                <h1 className='py-2'>Entrada</h1>
                            </div>
                            <img className='w-15 h-20 justify-center align-middle pt-7 pr-36'
                                style={{ transform: 'scaleX(-1)' }} src={habilitado} alt="" />
                            <h1 className='pt-10 px-3'>online</h1>
                        </div>
                        <div className='border-2 border-black  rounded-xl mx-20 py-10 my-10 flex flex-row hover:scale-105 hover:shadow-xl'>
                            <img className='w-28 mx-7' src={sensor} alt="sensor" />
                            <div className='text-3xl font-bold'> <h1 className=''>Bosque de prueba 1</h1>
                                <h1 className='pt-3 px-3'>- 6 sensores activos</h1></div>
                            <div className='px-7 '><h1 className='py-2'>zona sur</h1>
                                <h1 className='py-2'>Lago</h1>
                                <h1 className='py-2'>Entrada</h1>
                            </div>
                            <div className=' '><h1 className='py-2'>zona sur</h1>
                                <h1 className='py-2'>Lago</h1>
                                <h1 className='py-2'>Entrada</h1>
                            </div>
                            <img className='w-15 h-20 justify-center align-middle pt-7 pl-36'
                                src={habilitado} alt="" />
                            <h1 className='pt-10 px-3'>offline</h1>
                        </div>
                        <div className='border-2 border-black  rounded-xl mx-20 py-10 my-10 flex flex-row hover:scale-105 hover:shadow-xl'>
                            <img className='w-28 mx-7' src={sensor} alt="sensor" />
                            <div className='text-3xl font-bold'> <h1 className=''>Bosque de prueba 1</h1>
                                <h1 className='pt-3 px-3'>- 3 sensores activos</h1></div>
                            <div className='px-14 '><h1 className='py-2'>zona sur</h1>
                                <h1 className='py-2'>Lago</h1>
                                <h1 className='py-2'>Entrada</h1>
                            </div>
                            <img className='w-15 h-20 justify-center align-middle pt-7 pl-36'
                                src={habilitado} alt="" />
                            <h1 className='pt-10 px-3'>offline</h1>
                        </div>
                    </div>


                    <div className=' bg-slate-700 mb-2 flex '>
                        <div className='bg-black h-full overflow-hidden '>
                            <img

                                className='h-full w-full object-cover object-center ml ' src="https://www.dicyt.com/downloadItem.php?itemId=36500&dialog=Y" alt="" />

                        </div>
                    </div>
                </div>

            </div>
            <div className='bg-zinc-100 py-8 flex justify-center items-center'>
                <h1 className="text-3xl font-bold">Bosque de prueba 1</h1>
            </div>

            {/* Map */}
            <div className=" flex flex-col ">
                <div className='flex '>
                    <MapView data={Mock} className=" bg-black" />
                    <div className=' bg-zinc-100 flex pt-3 flex=col w-screen h-screen'>
                        <div className=' mb-2  w-5/6 '>
                            <div className='border-2 border-black rounded-xl mx-24 py-6 my-16 flex flex-row hover:scale-125 hover:shadow-2xl'>
                                <img className='w-24 h-24' src={humedad} alt="humedad" />
                                <div>
                                    <h1 className="text-3xl font-bold px-12">Humedad</h1>
                                    {Mock[2] && (<h1 className="text-3xl px-24 py-1">{Mock[2].humidity}%</h1>)}
                                    <h1 className='text-xl px-14 py-2'></h1>
                                </div>
                            </div>

                            <div className='border-2 border-black rounded-xl mx-24 py-6 my-16 flex flex-row hover:scale-125 hover:shadow-2xl'>
                                <img className='w-24 h-24 ml-4' src={temperatura} alt="humedad" />
                                <div>
                                    <h1 className="text-3xl font-bold px-6">Temperatura</h1>
                                    {Mock[2] && (<h1 className="text-3xl px-20 py-1">{Mock[2].temperature}C</h1>)}
                                    <h1 className='text-xl px-14 py-2'></h1>
                                </div>
                            </div>
                            
                            
                            <div className='border-2 border-black rounded-xl mx-24 py-6 my-16 flex flex-row hover:scale-125 hover:shadow-2xl'>
                                <img className='w-24 h-24' src={humo} alt="humedad" />
                                <div>
                                    <h1 className="text-3xl font-bold px-12">Humedad</h1>
                                    {Mock[2] && (<h1 className="text-3xl px-24 py-1">{Mock[2].smokeLevel}</h1>)}
                                    <h1 className='text-xl px-14 py-2'></h1>
                                </div>
                            </div>
                        </div>
                        <div className=' mb-2  w-5/6 '>
                        <div className='border-2 border-black rounded-xl mx-24 py-6 my-16 flex flex-row hover:scale-125 hover:shadow-2xl'>
                                <img className='w-24 h-24' src={lluvia} alt="humedad" />
                                <div>
                                    <h1 className="text-3xl font-bold px-12">Lluvia</h1>
                                    {Mock[2] && (<h1 className="text-3xl px-24 py-1">{Mock[2].rainStatus}</h1>)}
                                    <h1 className='text-xl px-14 py-2'></h1>
                                </div>
                            </div>

                            <div className='border-2 border-black rounded-xl mx-24 py-6 my-16 flex flex-row hover:scale-125 hover:shadow-2xl'>
                                <img className='w-24 h-24' src={locacion} alt="humedad" />
                                <div>
                                    <h1 className="text-3xl font-bold px-12">Latitud</h1>
                                    {Mock[2] && (<h1 className="text-3xl px-12 py-1">{Mock[2].latitude}</h1>)}
                                    <h1 className='text-xl px-14 py-2'></h1>
                                </div>
                            </div>

                            <div className='border-2 border-black rounded-xl mx-24 py-6 my-16 flex flex-row hover:scale-125 hover:shadow-2xl'>
                                <img className='w-24 h-24' src={locacion} alt="humedad" />
                                <div>
                                    <h1 className="text-3xl font-bold px-12">Longitud</h1>
                                    {Mock[2] && (<h1 className="text-3xl px-12 py-1">{Mock[2].longitude}</h1>)}
                                    <h1 className='text-xl px-14 py-2'></h1>
                                </div>
                            </div>
                        </div>
                    </div>

                </div>

            </div>
        </>
    );
};

export default HomeView;
