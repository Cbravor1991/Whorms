# Manual de Proyecto

## Desarrollo del proyecto

### Semana 1(desde 17/10/2023)

- Creación del repositorio
- Reutilización de algunas cosas del tp de thrads (parte del protocolo y algunas funcionalidades basicas del servidor)
- Modificación del protocolo del cliente y servidor.
- Implementación de los threads que reciben y envian datos entre el servidor y el cliente
- Familiarizarse con las distintas librerias a usar

### Semana 2(desde 24/10/2023)

- Implementación de turnos por tiempo
- Implementación de clases para encapsular los mensajes enviados entre el cliente y el servidor
- Agregado queues a los threads que se encargan de enviar y recibir datos tanto del cliente como del servidor
- Prueba de concepto de SDL2
- Separación de los archivo del cliente, del servidor y los que son comunes a ambos en carpetas

### Semana 3(desde 31/10/2023)

- El cliente guarda a todos los jugadores conectados y las vigas.
- Modificación en la logica del protocolo
- Implementación del CMake con las librerias a usar
- Implementación de movimientos del gusano
- Implementación inicial del manejador de eventos

### Semana 4(desde 7/11/2023)

- Se muestra el gusano y las vigas en la interfaz grafica.
- Animación del gusano al caminar
- Agregado musica al cliente
- Implementación de clase para guardar texturas y audios
- Implementación de vigas inclinadas


### Semana 5(desde 14/11/2023)
- Implementación del inventario de los gusanos
- Implementación inicial de las armas(ataque aereo, teleport, banana y bate)
- Color a los gusanos de acuerdo al jugador al que pertenecen
- Agregado efectos de sonido

### Semana 6(desde 21/11/2023)
- Daño de caida y cambio de turno por daño o disparo de armas
- Implementación de las armas en el cliente
- Implementación de la mira, potencia y temporizador de explosion de las armas
- Implementación inicial del lobby del cliente con QT
- Implementación de más armas en el servidor
- Animación de las explosiones
- Empezamos a implementar las multipartidas
- Agregado configuracion del servidor con yaml
- Ahora el creador de las partidas decide cuando iniciarla

### Semana 7(desde 28/11/2023)
- Implementación final de multipartidas
- Implementación de provisiones
- Se terminó de implementar las armas
- Se implementaron las Animaciónes para la potencia y la mira
- Implementación del viento
- Se implementó la pantalla de victoria/derrota
- Arreglo de memory leaks y race conditions en el servidor
- Se implementó el editor de mapas, con la creación y edición de los mapas
- Implementación de la vida por equipo y rotacion de los proyectiles
- Creación de los distintos documentos y manuales
- Integración del servidor y cliente con las multipartidas
- Integración de los mapas del editor con el servidor

## Herramientas usadas

- Servidor: en el servidor se utilizó el motor de físicas Box2D para implementar los movimientos de los gusanos y proyectiles.
- Dibujos y Animaciónes: para los dibujos y Animaciónes en el cliente se usó SDL2 y el wrapper SDL2pp
- Pantalla de inicio: para la pantalla de inicio del cliente, se utilizo solamente QT5.
- Editor: Para la implemantacion del editor se utilizó SDL2 con el wrapper SDL2pp y QT5
- Archivos de configuracion y mapas: para los archivos de configuración usados en el servidor y los mapas se utilizó archivos yaml y la librería yaml-cpp para poder crearlos, editarlos y leerlos.

## Problemas encontrados

- Uno de los pricipales problemas que encontramos fue implementar la cámara con SDL2, estuvimos intentando mucho tiempo, pero al final no nos salió y decidimos seguir avanzando con el resto de cosas a implementar.
- A la hora de realizar la interfaz gráfica del usuario con Qt, tanto en el juego principal como en el editor, nos encontramos con diversos problemas. El que más tiempo nos llevó resolver fue la configuración del archivo CMake con las configuraciones pertinentes de las bibliotecas de Qt5. Luego, para el diseño, fue necesario un breve y rápido entrenamiento utilizando el programa Qt Creator. Pero, superados estos inconvenientes, el resultado fue satisfactorio.
