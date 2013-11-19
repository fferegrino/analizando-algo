using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Algoritmos.Util;
using System.Threading.Tasks;


namespace ProblemaNReinas
{
    /// <summary>
    /// Clase que representa el tablero donde se colocarán las reinas
    /// </summary>
    public class Tablero
    {
        static readonly SuperRandom sr = new SuperRandom(DateTime.Now.Millisecond);

        private int[,] reinas;

        public int[,] Reinas
        {
            get { return reinas; }
            set { reinas = value; }
        }

        public int NumeroReinas { get; private set; }

        public Tablero(int numeroReinas)
        {
            NumeroReinas = numeroReinas;
            Reinas = new int[numeroReinas, numeroReinas];
        }

        /// <summary>
        /// Método para colocar una reina en la posición <paramref name="i"/>, <paramref name="j"/> del tablero
        /// </summary>
        /// <param name="i"></param>
        /// <param name="j"></param>
        public void ColocaReina(int i, int j)
        {
            Reinas[i, j] = 1;
        }

        /// <summary>
        /// Método para saber si es válido colocar una reina en la posición <paramref name="i"/>, <paramref name="j"/> del tablero
        /// </summary>
        /// <param name="i"></param>
        /// <param name="j"></param>
        /// <returns></returns>
        public bool ChecarValidez(int i, int j)
        {
            bool valido = true;
            // Obtenemos suma de las reinas la fila, columna y diagonales
            int calc = ReinasEnFila(i) + ReinasEnColumna(j) + ReinasEnDiagonales(i, j);
            // Si la suma es igual a 0 es posible colocar una reina
            valido = calc == 0;
            return valido;
        }

        /// <summary>
        /// Método para obtener el número de reinas en la fila especificada
        /// </summary>
        /// <param name="fila"></param>
        /// <returns></returns>
        public int ReinasEnFila(int fila)
        {
            int reinas = 0;
            for (int i = 0; i < NumeroReinas; i++)
            {
                reinas += Reinas[fila, i];
            }
            return reinas;
        }

        /// <summary>
        /// Método para obteneer el número de reinas en la columna especificada
        /// </summary>
        /// <param name="columna"></param>
        /// <returns></returns>
        public int ReinasEnColumna(int columna)
        {
            int reinas = 0;
            for (int i = 0; i < NumeroReinas; i++)
            {
                reinas += Reinas[i, columna];
            }
            return reinas;
        }

        /// <summary>
        /// Método para obtener el número de reinas en las diagonales de la posición especificada
        /// </summary>
        /// <param name="i"></param>
        /// <param name="j"></param>
        /// <returns></returns>
        public int ReinasEnDiagonales(int i, int j)
        {
            int reinas = 0;
            /// TODO: Implementación del método
            return reinas;
        }

        /// <summary>
        /// Método que lanza la ejecución del algoritmo Las Vegas para la resolución del problema de las
        /// n reinas.
        /// </summary>
        /// <param name="iteraciones">La cantidad de iteraciones para intentar de colocar una reina en una posición válida</param>
        /// <returns><code>true</code> si eel algoritmo fue capaz de obtener una respuesta, <code>false</code> si no la encontró</returns>
        public bool LasVegas(int iteraciones)
        {
            // Variables bandera para trazar el estatus de este método
            bool exito = true;
            bool ubicacionValida = false;
            int fila = 0;
            // Recorremos el tablero columna por columna, dado que no existe la necesidad de
            // volver atrás para colocar una reina
            for (int columna = 0; columna < NumeroReinas && exito; columna++)
            {
                // Realizamos tantos intentos de colocar una reina como indique el parámetro
                // o mientras que una reina no haya sido colocada en una ubicación adecuada
                for (int intentos = 0; intentos < iteraciones && !ubicacionValida; intentos++)
                {
                    // Obtenemos un número aleatorio ubicado dentro de los límites del tablero
                    // para encontrar la posible ubicación de la siguiente reina
                    fila = sr.NextInt32(0, NumeroReinas); 
                    // Checamos la validez de la nueva ubicación
                    ubicacionValida = ChecarValidez(columna, fila);
                }
                // Si la ubicación fue válida colocamos la reina en la posición
                if (ubicacionValida)
                    ColocaReina(columna, fila);
                // Si no, indicamos que el algoritmo falló
                else
                    exito = false;

                ubicacionValida = false;
            }
            return exito;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < NumeroReinas; i++)
            {
                for (int j = 0; j < NumeroReinas; j++)
                {
                    sb.Append(Reinas[i, j]);
                }
                sb.AppendLine();
            }
            return sb.ToString();
        }

    }
}
