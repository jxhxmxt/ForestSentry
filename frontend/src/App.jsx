import React, { useState } from 'react'

// Import React Router
import { Routes, Route, Navigate } from 'react-router-dom';

// Import Views
import HomeView from './views/HomeView'

import './App.css'

function App() {

  return (
    <>
      <Routes>
        <Route path="/" element={<HomeView />} />
        <Route path="*" element={<Navigate to="/" />} />
      </Routes>
    </>
  )
}

export default App
