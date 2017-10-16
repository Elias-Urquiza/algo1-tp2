Aquí trabajaremos en el tp2.
Por el momento queda discutir como nos dividiremos la labor.
Habría que ir anotando lo que vamos haciendo mientras hacemos el tp asi facilita la creacion del informe
Tambíen habrá que leer la bibliografia de <time.h>


Incluyo lo que escribió el profesor en respuesta a una pregunta que le hicieron por la lista de correos:

Hola:
como la consulta le sirve a todxs, la respondo hacia la lista de
correos.

On Fri, Oct 06, 2017 at 04:57:29PM -0300, Julieta Cloé Galante wrote:
> Hola, queríamos hacer algunas preguntas sobre cómo proceder en la primera
> parte del trabajo, ya que no entendemos del todo en qué consiste cada uno
> de los seis pasos de la sección 4.1. En primer lugar no entendemos que
> sería el paso 1. Extraer campos de la línea y tampoco su respectiva
> validación, que suponemos que es el paso 2.

Les comenté que un archivo CSV contiene, en cada línea, campos separados
por comas (,). Entonces, lo que ustedes tienen que hacer es generar un
vector de cadenas con cada uno de esos campos.

Si ustedes leen la línea:

linea: "CAMPO1,CAMPO2,CAMPO3,CAMPO4,CAMPO5,CAMPO6"

la procesan y obtienen:

campos: * ---
\-->| *-|--> "CAMPO1"
|---|
| *-|--> "CAMPO2"
|---|
| *-|--> "CAMPO3"
|---|
| *-|--> "CAMPO4"
|---|
| *-|--> "CAMPO5"
|---|
| *-|--> "CAMPO6"
---

> Por otro lado, en el paso 3. a lo que se refiere es a crear una matriz
> donde se carguen los datos que ingresen desde el programa? Y habría que
> validar en este caso que la memoria sea suficiente para guardar la cantidad
> de datos ingresada?

En el paso 3, lo que tienen que hacer es guardar los datos que
almacenaron en la variable 'campos' en una estructura del tipo indicado
en la tabla 1 del enunciado. Para los campos 'id', 'puntaje' y
'reseñas', lo que tienen que hacer es una conversión de una cadena a un
número. En el campo fecha, la conversión es distinta, y tienen que usar
el tipo de dato time_t, definido en la biblioteca time.h. Es tarea de
ustedes leer de la bibliografía cómo se manipula ese tipo de dato. Es
algo que durante el ejercicio de la profesión tienen que hacer
constantemente (lo de leer la referencia de una biblioteca). En este
caso es una biblioteca nativa, que se utiliza para representar fechas, y
hay mucha información al respecto. De dónde leen esto, es un item que va
en la bibliografía del informe.

> Por último, el paso 5. no podríamos hacerlo todavía, o si?

No, todavía no. Ese sería el punto que reemplazan por la impresión (por
pantalla) de un campo de la estructura cargada --o toda la estructura--,
para verificar que cargaron bien los datos.

Como recomendación, pueden hacer una función que reciba la estructura y
la imprima en formato CSV. Esa misma función les serviría para lo que
tienen que hacer en la sección 4.2 ``Desbinarización de la base de
datos''.

Saludos,
--
PATRICIO MORENO
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibligrafia

H. M. Deitel y P. J. Deitel. Como programar en C/C++ y Java. 4ª Edición. Pearson
Educación, 2004, ISBN 970-26-0531-8, págs 390 a 413.

/*INSERT LINKS HERE*/
