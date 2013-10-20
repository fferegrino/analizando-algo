using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RutApp.Graph.Entidades;

namespace RutApp.Consola
{
    class Program
    {
        static void Main(string[] args)
        {
            decimal latI = 0, longI = 0, latF = 0, longF = 0;
            string[] coordenadasInicio = null;
            string[] coordenadasFinal = null;
            if (args.Length > 1)
            {
                coordenadasInicio = args[0].Split(',');
                coordenadasFinal = args[1].Split(',');
            }
            else
            {
                Console.Write("Coordenadas origen: ");
                coordenadasInicio = Console.ReadLine().Split(',');
                Console.Write("Coordenadas destino: ");
                coordenadasFinal = Console.ReadLine().Split(',');
            }
            latI = decimal.Parse(coordenadasInicio[0]);
            longI = decimal.Parse(coordenadasInicio[1]);
            latF = decimal.Parse(coordenadasFinal[0]);
            longF = decimal.Parse(coordenadasFinal[1]);

            Grafo g = new Grafo();
            // Cargamos el grafo de información
            g.CargaGrafo();
            // Calculamos la ruta:
            Ruta r = g.EncontrarRuta(latI, longI, latF, longF);
            int estaciones = r.Estaciones.Count;
            Console.WriteLine(String.Join(" - ", r.Estaciones));
            Console.Read();
        }
    }
}
