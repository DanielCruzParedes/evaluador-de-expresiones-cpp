# Evaluador de Expresiones

## Descripción del Proyecto
Este proyecto consiste en un evaluador de expresiones matemáticas desarrollado en C++ que permite la conversión de expresiones en notación infija a notación postfija y su posterior evaluación.

## Características
- Soporte para operaciones matemáticas básicas: `+`, `-`, `*`, `/`, `%`, `^`.
- Manejo de paréntesis para definir la precedencia de operaciones.
- Conversión de expresiones infijas a postfijas.
- Evaluación de expresiones postfijas usando una pila.
- Soporte para constantes predefinidas (configurables en un archivo de texto):
  - `π=3.141592`
  - `e=2.71828`
  - `g=9.81`
(NOTA: Si se quieren agregar más constantes hacerlo sin dejar espacios. Por ejemplo: year=2025)
- Permite el uso de variables ingresadas por el usuario.
- Soporte para números enteros y flotantes.
- Implementación de validaciones para detectar errores en la expresión infija.
- Uso de características de C++23.

## Instalación y Uso
### Requisitos
- Compilador compatible con C++23.
- CMake instalado en el sistema.
- Entorno de desarrollo como Visual Studio Code o similar.

### Compilación
```sh
cd build
cmake ..
cmake -build .
```

### Ejecución
```sh
cd build
./EvaluadorDeExpresiones.exe
```

### Entrada y Salida
- **Entrada:** Expresión matemática en notación infija (sin espacios entre los números), por ejemplo:
  ```
  (100+25)*399
  ```
- **Salida:** La expresión ingresada, la evaluación de la expresión en notación postfija y su resultado:
  ```
  La expresion ingresada es: (100+25)*399
  La expresion en postfijo es: 100 25 + 399 * 
  El resultado de la expresion es: 49875
  ```

**Nota:** No se permiten espacios entre los números en la expresión. Ejemplo correcto: `(100+10)*5`. Ejemplo incorrecto: `(100 + 10) * 5`.

## Validaciones Implementadas
- Detección de paréntesis sin cerrar o incorrectos.
- Errores sintácticos en la expresión infija.
- División y módulo por cero.
- Operadores mal posicionados (ejemplo: `10 + 5 +.`).
- No se permiten espacios entre los números.

## Pruebas
Se implementa TDD utilizando el framework **Catch2**.
- Se incluyen 10 pruebas exitosas y 10 fallidas con validaciones de errores.
- Los tests se ejecutan desde la carpeta `build`.

## Créditos
- Proyecto desarrollado en la clase **Lenguajes de Programación** en **UNITEC** en **Q1-2025**.


