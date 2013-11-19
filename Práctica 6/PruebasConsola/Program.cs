using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Algoritmos.Util;
using ComprobacionPrimalidad;
using ProblemaNReinas;

namespace PruebasConsola
{
    class Program
    {
        static void Main(string[] args)
        {
            Tablero r = new Tablero(10);
            Console.WriteLine(r);
            bool exito = r.LasVegas(20);
            if (exito) Console.WriteLine("Exito: ");
            Console.WriteLine(r);
                Console.Read();
        }

    }
}
