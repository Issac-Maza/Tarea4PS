/* Variables globales */
int readcnt = 0; /* Inicializamos la cantidad de escritores a 0 */
sem_t mutex, w, z; /* varibales tipo semaforos mutex and w inicializadas = 1, z = 1 */
//mutex protege el acceso exclusivo a readcnt para evitar condiciones de carrera.
//w controla el acceso a la seccion critica para los escritores(y también los lectores si no hay escritores)
//z introducido para bloquear a los lectores mientras hay escritores esperando o escribiendo, asegurando prioridad a los escritores.

void reader(void) {
    while (1) {
        P(&z);           /* Prevenir acceso si hay escritores esperando */
		//asegura que los lectores no accedan si hay un escritor esperando.
		//Si no hay escritores, el lector continúa.

        P(&mutex);       /* Acceso exclusivo a readcnt */ 
		//para garantizar que solo un lector acceda a la variable a la vez.
        readcnt++;
        if (readcnt == 1) {
            P(&w);       /* Bloquear escritores si es el primer lector */
        }
        V(&mutex);       /* Liberar acceso a readcnt */
        V(&z);           /* Permitir nuevos lectores si no hay escritores o escritores*/

        /* Critical section */
        /* Reading happens */
		//Decrementar el contador de lectores (readcnt):
        P(&mutex);       /* Acceso exclusivo a readcnt */
        readcnt--;		//decrementa a 0
        if (readcnt == 0) {
            V(&w);       /*  desbloquea w permitiendo escritores accder */
        }
        V(&mutex);       /* Liberar acceso a readcnt */
    }
}

void writer(void) {
    while (1) {
        P(&z);           /* Prevenir nuevos lectores mientras escribe */
        P(&w);           /* Acceso exclusivo para escribir */

        /* Critical section */
        /* Writing happens */

        V(&w);           /* Liberar acceso para lectores o escritores */
        V(&z);           /* Permitir nuevos lectores o escritores */
    }
}

