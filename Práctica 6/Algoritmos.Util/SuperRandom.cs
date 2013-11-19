using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Algoritmos.Util
{
    public class SuperRandom : Random
    {
        public SuperRandom(int seed)
            : base(seed)
        {

        }

        public SuperRandom()
            : base()
        {
        }

        /// <summary>
        /// Método para obtener un entero del servicio web de Random.org
        /// </summary>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public int IntRandomOrg(int min, int max)
        {
            /// TODO: Implementación del método
            throw new NotImplementedException();
        }

        /// <summary>
        /// Método para generar un entero positivo de 32 bits con signo "aleatorio"
        /// </summary>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public int NextInt32(int min, int max)
        {
            var buffer = new byte[sizeof(int)];
            base.NextBytes(buffer);
            int longRand = BitConverter.ToInt32(buffer, 0);
            return (Math.Abs(longRand) % (max - min)) + min;
        }

        /// <summary>
        /// Método para generar un entero positivo de 64 bits sin signo "aleatorio"
        /// </summary>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public ulong NextUInt64(ulong min, ulong max)
        {
            var buffer = new byte[sizeof(ulong)];
            base.NextBytes(buffer);
            ulong longRand = BitConverter.ToUInt64(buffer, 0);
            return (longRand % (max - min)) + min;
        }

    }
}
