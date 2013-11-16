using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AlgoritmosUtil
{
    public class Matematica
    {
        /// <summary>
        /// Método para calcular <paramref name="a"/>^<paramref name="n"/> mod <paramref name="z"/> que es el Test de Primalidad de Fermat
        /// <para>http://es.wikipedia.org/wiki/Test_de_primalidad_de_Fermat</para>
        /// <para>http://webdiis.unizar.es/asignaturas/EDA/ea/slides/3-Divide%20y%20venceras.pdf</para>
        /// </summary>
        /// <param name="a"></param>
        /// <param name="n"></param>
        /// <param name="z"></param>
        /// <returns></returns>
        public static ulong ModuloPotencia(ulong a, ulong n, ulong z)
        {
            ulong i = n;
            ulong x = a;
            ulong r = 1;

            while (i > 0)
            {
                if (i % 2 != 0)
                {
                    r = r * x % z;
                }
                x = x * x % z;
                i /= 2;
            }
            return r;
        }
    }
}
