using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AlgoritmosUtil;
using ComprobacionPrimalidad;

namespace PruebasConsola
{
    class Program
    {
        static void Main(string[] args)
        {

            ulong[] longs = { 3, 5, 7, 11, 13, 17, 19, 23, 29, 30, 123123, 512312543, 53928298, 12372438212, 1235789123, 1988108901, 997881729831267, 997 };
            SuperRandom sr = new SuperRandom();
            foreach (ulong l in longs)
            {
                SupuestoPrimo sp = new SupuestoPrimo(l);
                if (sp.EsPrimo(10000))
                {
                    Console.WriteLine("{0} puede ser primo", l);
                }
                else
                {
                    Console.WriteLine("{0} no es primo", l);
                }
            }
            Console.Read();
        }

    }
}
