using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RutApp.Graph.Entidades
{
    public class Estacion : IComparable<Estacion>
    {
        public string IdEstacion { get; set; }
        public string Nombre { get; set; }
        public bool Terminal { get; set; }
        public decimal Latitud { get; set; }
        public decimal Longitud { get; set; }
        public decimal Tarifa { get; set; }
        public string Linea { get; set; }
        public string TipoEstacion { get; set; }
        public List<Conexion> Conexiones { get; set; }
        public decimal PesoAcumulado { get; set; }
        public Estacion EstacionPredecesora{ get; set; }


        public Estacion(string idEstacion)
        {
            IdEstacion = idEstacion;
            Conexiones = new List<Conexion>();
        }

        public override bool Equals(object obj)
        {
            if (obj == null 
                || this.GetType() != obj.GetType())
                return false;

            if (ReferenceEquals(this, obj))
                return true;
            Estacion o = obj as Estacion;
            return CompareTo(o) == 0;
        }

        public int CompareTo(Estacion other)
        {
            return this.IdEstacion.CompareTo(other.IdEstacion);
        }

        /// <summary>
        /// Método que nos indica si hay conexión entre
        /// una estación y otra
        /// </summary>
        /// <param name="e"></param>
        /// <returns></returns>
        public bool HayConexion(Estacion e)
        {
            return Conexiones.Contains(new Conexion() { Destino = e });
        }

        public decimal PesoConexion(Estacion e)
        {
            if (HayConexion(e))
            {
                foreach (Conexion c in Conexiones)
                {
                    if (c.Destino.Equals(e))
                    {
                        return c.Peso;
                    }
                }
            }
            return -1;
        }

        /// <summary>
        /// Método que agrega una nueva conexión con
        /// otra estación
        /// </summary>
        /// <param name="c"></param>
        /// <returns>Cierto si lo agregó, falso si no</returns>
        public bool AgregaConexion(Conexion c)
        {
            // Si ya hay una conexión, salimos
            if (Conexiones.Contains(c)) return false;
            // Si el nodo destino es igual al origen, salimos
            if (Equals(c.Destino)) return false;

            Conexiones.Add(c);

            return true;
        }

        public override string ToString()
        {
            return string.Format("{0} ({1})", this.Nombre, this.TipoEstacion);
        }
        
    }
}
