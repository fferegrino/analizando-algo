using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Practica6.Common
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
        /// Método para generar un entero positivo de 32 bits con signo "aleatorio"
        /// </summary>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public int NextInt32(int min, int max)
        {
            var buffer = new byte[sizeof(long)];
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
