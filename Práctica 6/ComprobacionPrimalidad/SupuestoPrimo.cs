using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Algoritmos.Util;


namespace ComprobacionPrimalidad
{
    public class SupuestoPrimo
    {
        public ulong Numero { get; set; }
        static readonly SuperRandom sr = new SuperRandom(DateTime.Now.Millisecond);

        public SupuestoPrimo(ulong numero)
        {
            Numero = numero;
        }

        /// <summary>
        /// Método que nos servirá para comprobar la supuesta primalidad de un número
        /// </summary>
        /// <param name="iteraciones">El número de iteraciones para calcular</param>
        /// <returns></returns>
        public bool EsPrimo(int iteraciones)
        {
            // Partimos con la premisa de que el número es primo
            bool esPrimo = true;
            // Ejecutamos el algoritmo tantas veces como se haya solicitado 
            // y mientras que el número "siga siendo" primo
            for (int i = 1; i < iteraciones && esPrimo; i++)
            {
                // Obtenemos un número aleatorio en el rango [1,n-1]
                ulong a = sr.NextUInt64(1, Numero - 1);
                // Ejecutamos el Test de Primalidad de Fermat 
                // http://es.wikipedia.org/wiki/Test_de_primalidad_de_Fermat
                ulong mod = Matematica.ModuloPotencia(a, Numero - 1, Numero);

                esPrimo = mod == 1 && esPrimo;
            }
            return esPrimo;
        }


        public override string ToString()
        {
            return Numero.ToString();
        }
    }
}
