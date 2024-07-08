### ForestSentry - Sistema de Monitoreo Ambiental para la Detección Temprana de Incendios Forestales

---

## Descripción del Proyecto

El Sistema de Monitoreo Ambiental para la Detección Temprana de Incendios Forestales es una innovadora herramienta diseñada para prevenir y mitigar desastres naturales causados por incendios forestales. Utiliza un conjunto de sensores conectados a un microcontrolador ESP8266 para recopilar datos ambientales en tiempo real y transmitirlos a una plataforma en línea.

### Tecnologías Utilizadas

- **Frontend:** React
- **Base de Datos:** PostgreSQL
- **API:** Springboot Java
- **Microcontrolador:** Arduino (C/C++)
- **Lenguajes:**
  - C (53.1%)
  - C++ (44.2%)
  - JavaScript (1.3%)
  - Java (1.1%)
  - Python (0.3%)
  - HTML (0.0%)
- **Plataforma de Datos en Línea:** Adafruit IO

### Proceso del Sistema

1. **Recopilación de Datos:** Sensores en el Arduino envían datos a la API.
2. **Procesamiento de Datos:** La API conecta estos datos a la base de datos y al frontend.
3. **Visualización de Datos:** El frontend consume y presenta los datos a los usuarios.

### Instalación y Configuración

#### Requisitos Previos

- Node.js
- PostgreSQL
- JDK 11+
- Arduino IDE

#### Instrucciones de Instalación

1. **Clonar el Repositorio:**
   ```sh
   git clone https://github.com/jxhxmxt/ForestSentry.git
   cd ForestSentry
   ```

2. **Instalar Dependencias (Frontend):**
   ```sh
   cd frontend
   npm install
   ```

3. **Configurar Base de Datos:**
   Crear una base de datos PostgreSQL y actualizar las credenciales en el archivo de configuración de Springboot (`application.properties`).

4. **Compilar y Ejecutar el Backend:**
   ```sh
   cd backend
   ./mvnw spring-boot:run
   ```

5. **Iniciar el Frontend:**
   ```sh
   cd frontend
   npm start
   ```

6. **Configurar Arduino:**
   - Conectar los sensores al microcontrolador ESP8266.
   - Subir el código desde el Arduino IDE.

### Ejemplo de Código

#### Backend (Java - Springboot)
```java
@RestController
@RequestMapping("/api")
public class SensorController {

    @Autowired
    private SensorService sensorService;

    @PostMapping("/data")
    public ResponseEntity<?> receiveData(@RequestBody SensorData data) {
        sensorService.processData(data);
        return ResponseEntity.ok("Data received");
    }
}
```

#### Frontend (React)
```jsx
import React, { useEffect, useState } from 'react';
import axios from 'axios';

const DataDisplay = () => {
    const [data, setData] = useState([]);

    useEffect(() => {
        axios.get('/api/data')
            .then(response => setData(response.data))
            .catch(error => console.error('Error fetching data:', error));
    }, []);

    return (
        <div>
            <h1>Sensor Data</h1>
            <ul>
                {data.map(item => (
                    <li key={item.id}>{item.value}</li>
                ))}
            </ul>
        </div>
    );
};

export default DataDisplay;
```

### Licencia

Este proyecto está licenciado bajo la **Licencia Pública General Reducida de GNU (LGPL) versión 2.0**. La LGPL v2.0 es una licencia de software libre que garantiza la libertad de usar, modificar y distribuir el software, asegurando al mismo tiempo que las mejoras y modificaciones también se mantengan libres.

#### ¿Por qué utilizamos LGPL v2.0?

1. **Flexibilidad:** Permite la integración con software propietario, lo que facilita la adopción y uso del proyecto en entornos comerciales sin necesidad de liberar el código fuente propietario.
2. **Compatibilidad:** Es compatible con otras licencias de software libre y de código abierto, lo que facilita la colaboración y el intercambio de código con otros proyectos.
3. **Protección de las Mejoras:** Asegura que cualquier mejora o modificación realizada al proyecto original se mantenga libre y abierta, beneficiando a la comunidad en general.

### Contribuciones

Para contribuir al proyecto, sigue estos pasos:

1. **Fork del Proyecto:**
   - Haz un fork del repositorio en GitHub.

2. **Crear una Nueva Rama:**
   - ```sh
     git checkout -b feature/nueva-funcionalidad
     ```

3. **Realizar Cambios y Hacer Commit:**
   - ```sh
     git commit -m 'Añadir nueva funcionalidad'
     ```

4. **Subir Cambios:**
   - ```sh
     git push origin feature/nueva-funcionalidad
     ```

5. **Abrir un Pull Request:**
   - Desde tu repositorio fork, abre un pull request hacia el repositorio original.

#### Normas de Contribución

- Asegúrate de que tu código sigue las convenciones de estilo del proyecto.
- Escribe pruebas para tu código nuevo o modificado.
- Actualiza la documentación según sea necesario.

### Contacto

Para más información o asistencia, puedes contactar a los siguientes miembros del equipo:

- **Diego Engelhard Robert:** 00356119@uca.edu.sv
- **Luis Alexander Hernandez Martinez:** 00129020@uca.edu.sv
- **Diego Alejandro Gasteazoro:** 00315919@uca.edu.sv
- **Gabriel Enrique Martínez:** 00389819@uca.edu.sv
- **Josue Humberto Montecinos:** 00103013@uca.edu.sv

---

Este README proporciona una guía completa para entender, instalar y contribuir al proyecto ForestSentry. Si tienes alguna pregunta o necesitas asistencia adicional, no dudes en ponerte en contacto con nosotros.