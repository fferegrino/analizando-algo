using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RutApp.Graph.Entidades
{
    public class Conexion
    {
        public Estacion Destino { get; set; }
        public decimal VelocidadPromedio { get; set; }
        public decimal MetrosTramo { get; set; }
        public decimal Peso { get { return MetrosTramo; } }
        public decimal Tarifa { get; set; }

        public override bool Equals(object obj)
        {
            if (obj == null
                || this.GetType() != obj.GetType())
                return false;

            if (ReferenceEquals(this, obj))
                return true;

            Conexion c = obj as Conexion;

            return this.Destino.Equals(c.Destino);
        }

    }
}
