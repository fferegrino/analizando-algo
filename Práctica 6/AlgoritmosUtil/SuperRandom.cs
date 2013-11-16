using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AlgoritmosUtil
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

        public UInt64 NextUInt64(ulong min, ulong max)
        {
            var buffer = new byte[sizeof(Int64)];
            base.NextBytes(buffer);
            ulong longRand = BitConverter.ToUInt64(buffer, 0);
            return (longRand % (max - min)) + min;
        }
    }
}
