using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RutApp.Graph.Entidades
{
    public class Ruta
    {
        public List<Estacion> Estaciones { get; set; }
        public Ruta()
        {
            Estaciones = new List<Estacion>();
        }
    }
}
