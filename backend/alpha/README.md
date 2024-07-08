# Sistema de Monitoreo Ambiental para la Detección Temprana de Incendios Forestales

## Descripción del Proyecto

El **Sistema de Monitoreo Ambiental para la Detección Temprana de Incendios Forestales** es una innovadora herramienta diseñada para la prevención y mitigación de desastres naturales causados por incendios forestales. Este proyecto, alojado en el repositorio [ProjectACAForestFireSensor](https://github.com/luis12007/ProjectACAForestFireSensor.git), integra varias tecnologías avanzadas para ofrecer una solución eficaz y en tiempo real para la detección de incendios.

## Componentes del Sistema

El sistema utiliza un conjunto de sensores avanzados que incluyen:

- Sensores de Temperatura
- Sensores de Humedad
- Sensores de Gas
- Sensores de Lluvia
- Módulo GPS

Estos sensores están conectados a un microcontrolador ESP8266, conocido por su capacidad de conexión a redes WiFi. Los datos recopilados por estos sensores son transmitidos a una plataforma en línea, como Adafruit IO, donde se analizan en tiempo real. Esta infraestructura permite la detección temprana de condiciones propicias para incendios forestales, proporcionando alertas visuales a través de la plataforma en línea. Además, se ofrece una interfaz de usuario visual que facilita la comprensión de los datos recolectados.

## Tecnologías Utilizadas

| Componente       | Descripción                             |
|------------------|-----------------------------------------|
| Microcontrolador | ESP8266                                 |
| Plataforma       | Adafruit IO                             |
| Lenguajes        | Arduino C/C++                           |
| Base de Datos    | A definir (posiblemente MySQL o PostgreSQL) |
| Framework        | A definir (posiblemente React o Angular) |

## Mejoras en Desarrollo

1. **Incorporación de una Licencia:**
    - Inicialmente, el proyecto no contemplaba el uso de una licencia. Uno de los primeros pasos en el desarrollo actual es la selección y aplicación de una licencia adecuada para asegurar el correcto uso y distribución del software.

2. **Implementación de una Base de Datos:**
    - Se añadirá una base de datos para almacenar la información generada por el conjunto de sensores. Esto permitirá un manejo más eficiente de los datos históricos y facilitará el análisis a largo plazo.

3. **Servicio de Recuperación de Datos:**
    - Se desarrollará un servicio que extraerá la información almacenada en la base de datos y la entregará a una aplicación gráfica. Esta aplicación proporcionará a los usuarios una representación visual intuitiva de los datos, mejorando la capacidad de respuesta ante posibles incendios.

## Vínculo al Repositorio

Para más detalles sobre el proyecto y acceso al código fuente, visita el repositorio en GitHub: [ProjectACAForestFireSensor](https://github.com/luis12007/ProjectACAForestFireSensor.git)
