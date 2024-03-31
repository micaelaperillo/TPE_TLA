# CAL 9000
## Cellular Automata Language 9000

El proyecto buscará abstraer lo máximo posible la generación visual de los autómatas celulares. Para ello se proporcionará al usuario un lenguaje con formato similar a Python.

Se brindarán dos modalidades distintas de uso del lenguaje. La primera consistirá en especificar una regla predefinida de vecindad, o bien una especificada por el usuario. utilizando una nomenclatura provista por el lenguaje. Por otro lado, la segunda le permitirá al usuario dibujar los autómatas celulares elementales.

El lenguaje generará una salida en Python, utilizando la librería PyGame para poder visualizar el autómata y que el usuario interactúe con el mismo en caso de que sea en dos dimensiones.

La nomenclatura para los autómatas en dos dimensiones será la siguiente: A/D/B/V, en donde cada letra significa

    A: Cantidad de vecinos vivos para que la célula siga viva, sino muere de soledad
    D: Cantidad de vecinos vivos para que la célula muera por sobrepoblación
    B: Cantidad de vecinos vivos para que una célula nazca en una celda vacía
    V: Regla de vecindad, podra ser Moore (M), Von Neumann (VN) o creada por el usuario (U) y el rango especificado. Por ejemplo. M(2) es la distancia de Moore con rango dos. 
    
La extensión de los archivos será .cal9000.
