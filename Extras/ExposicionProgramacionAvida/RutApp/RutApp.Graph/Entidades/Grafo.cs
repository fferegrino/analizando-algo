using Microsoft.Practices.EnterpriseLibrary.Data;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RutApp.Graph.Entidades
{
    public class Grafo
    {
        private static SortedList<Estacion, Int32> grafo;
        public int NumeroNodos { get { return grafo.Count; } }
        public decimal[,] MatrizPesos;
        private Estacion[,] MatrizCamino;

        public Grafo()
        {
            grafo = new SortedList<Estacion, int>();
        }

        /// <summary>
        /// Obtiene el índice dentro del grafo en el que se
        /// encuentra la estación especificada
        /// </summary>
        /// <param name="e"></param>
        /// <returns></returns>
        public int ObtenerIndiceEstacion(Estacion e)
        {
            return grafo.IndexOfKey(e);
        }

        #region Algoritmo Dijkstra

        /// <summary>
        /// Método para encontrar la ruta óptima entre dos puntos dada sus coordenadas.
        /// </summary>
        /// <param name="latInicio">Latitud del punto inicial</param>
        /// <param name="longInicio">Longitud del punto inicial</param>
        /// <param name="latFinal">Latitud del punto final</param>
        /// <param name="longFinal">Longitud del punto final</param>
        /// <returns>La mejor ruta encontrada</returns>
        public Ruta EncontrarRuta(decimal latInicio, decimal longInicio, decimal latFinal, decimal longFinal)
        {
            // Buscamos las estaciones cercanas a las coordenadas de inicio y final
            Estacion origen = EstacionMasCercana(latInicio, longInicio);
            Estacion destino = EstacionMasCercana(latFinal, longFinal);

            // Llamamos a otro método que busca a partir de estaciones
            return EncontrarRuta(origen, destino);
        }

        /// <summary>
        /// Método para encontrar la ruta óptima entre dos puntos dadas las estaciones para iniciar
        /// </summary>
        /// <param name="inicio">Estación inicial</param>
        /// <param name="fin">Estación final</param>
        /// <returns>La mejor ruta encontrada</returns>
        public Ruta EncontrarRuta(Estacion inicio, Estacion fin)
        {
            Estacion auxiliar = fin;

            // Encontramos la ruta a partir del inicio
            List<Estacion> minimos = CalculaRutasMinimas(inicio);

            Ruta ruta = new Ruta();
            decimal distancia = 0;

            // Si no existe en nuestra lista es porque no hay conexión entre ellos
            if (!minimos.Contains(auxiliar))
            {
                throw new Exception(String.Format("{0} no alcanzable desde {1}", fin.Nombre, inicio.Nombre));
            }

            auxiliar = minimos[minimos.IndexOf(auxiliar)];
            distancia = auxiliar.PesoAcumulado;
            // Se usa una pila para almacenar la ruta
            Stack<Estacion> pila = new Stack<Estacion>();
            while (auxiliar != null)
            {
                pila.Push(auxiliar);
                auxiliar = auxiliar.EstacionPredecesora;
            }
            // Vaciar la pila para armar la ruta correcta
            while (pila.Count > 0)
            {
                ruta.Estaciones.Add(pila.Pop());
            }
            return ruta;
        }

        /// <summary>
        /// Método que a partir de una estación, encuentra las rutas optimas hacia todos los demás
        /// </summary>
        /// <param name="origen"></param>
        /// <returns></returns>
        public List<Estacion> CalculaRutasMinimas(Estacion origen)
        {
            List<Estacion> S = new List<Estacion>();
            List<Estacion> minimos = new List<Estacion>();

            S.Add(origen);

            while (S.Count > 0) // Mientras que existan elementos para procesar
            {
                // Sacamos un elemento de la lista
                Estacion temporal = S[0];
                Estacion predecesora = temporal.EstacionPredecesora;
                decimal pesoAnterior = temporal.PesoAcumulado;
                S.RemoveAt(0);
                // Lo agregamos a nuestro arreglo de soluciones
                temporal = grafo.ElementAt(grafo.IndexOfKey(temporal)).Key;
                temporal.EstacionPredecesora = predecesora;
                temporal.PesoAcumulado = pesoAnterior;
                minimos.Add(temporal);
                // Obtenemos el índice
                int indice1 = grafo.IndexOfKey(temporal);
                int indice2 = -1;
                // Por cada conexión con este nodo
                foreach (Conexion conexion in temporal.Conexiones)
                {
                    // Para cada arista que conecta con temporal
                    indice2 = grafo.IndexOfKey(conexion.Destino);
                    // No hay conexion
                    if (MatrizPesos[indice1, indice2] <= 0) continue;
                    // Ya se calculó
                    if (minimos.Contains(conexion.Destino)) continue;

                    // Marcamos con la etiqueta el nodo seleccionado
                    conexion.Destino.EstacionPredecesora = temporal;
                    conexion.Destino.PesoAcumulado = MatrizPesos[indice1, indice2] + temporal.PesoAcumulado;

                    // Si no existe, lo agregamos a la lista para ser procesado por el algoritmo
                    if (!S.Contains(conexion.Destino))
                    {
                        S.Add(conexion.Destino);
                        continue;
                    }
                    // Si llegó aquí es porque ya existía, entonces lo buscamos para comprobar que 
                    // siempre esté actualizado con el menor peso
                    for (int ix = 0; ix < S.Count; ix++)
                    {
                        Estacion e = S[ix];
                        if (e.Equals(conexion.Destino) // Si hablamos de las mismas estaciones
                            && e.PesoAcumulado > conexion.Destino.PesoAcumulado) // Y el peso es menor
                        {
                            S.RemoveAt(ix);
                            S.Add(conexion.Destino);
                            break;
                        }
                    }
                }
            }
            return minimos;
        }
        #endregion

        #region Datos

        public Estacion EstacionMasCercana(decimal latitud, decimal longitud) {
            Estacion e = null;
            Database db = DatabaseFactory.CreateDatabase("RutAppBd");

            // Recuperamos todas las estaciones de la base de datos
            DbCommand cmd = db.GetStoredProcCommand("dbo.ObtieneEstacionesCercanas");
            db.AddInParameter(cmd, "latitud", DbType.Decimal, latitud);
            db.AddInParameter(cmd, "longitud", DbType.Decimal, longitud);
            db.AddInParameter(cmd, "radio", DbType.Int32, 2000);
            using (IDataReader reader = db.ExecuteReader(cmd))
            {
                if (reader.Read())
                {
                    String idEstacion = reader.GetString(reader.GetOrdinal("id"));
                    e = new Estacion(idEstacion);
                    e.Nombre = reader.GetString(reader.GetOrdinal("nombre"));
                    int i = reader.GetOrdinal("linea");
                    if (!reader.IsDBNull(i))
                        e.Linea = reader.GetString(i);
                    e.Latitud = (decimal)reader.GetDouble(reader.GetOrdinal("latitud"));
                    e.Longitud = (decimal)reader.GetDouble(reader.GetOrdinal("longitud"));
                    e.Tarifa = reader.GetDecimal(reader.GetOrdinal("tarifa"));
                    e.TipoEstacion = reader.GetString(reader.GetOrdinal("tipo_estacion"));
                }
            }
            return e;
        }

        public void CargaGrafo()
        {
            Database db = DatabaseFactory.CreateDatabase("RutAppBd");

            // Recuperamos todas las estaciones de la base de datos
            DbCommand cmd = db.GetStoredProcCommand("dbo.ObtieneTodasEstaciones");
            int ix = 0;
            using (IDataReader reader = db.ExecuteReader(cmd))
            {
                while (reader.Read())
                {
                    String idEstacion = reader.GetString(reader.GetOrdinal("id"));
                    Estacion nvaEst = new Estacion(idEstacion);
                    nvaEst.Nombre = reader.GetString(reader.GetOrdinal("nombre"));
                    int i = reader.GetOrdinal("linea");
                    if (!reader.IsDBNull(i))
                        nvaEst.Linea = reader.GetString(i);
                    nvaEst.Latitud = (decimal)reader.GetDouble(reader.GetOrdinal("latitud"));
                    nvaEst.Longitud = (decimal)reader.GetDouble(reader.GetOrdinal("longitud"));
                    nvaEst.Tarifa = reader.GetDecimal(reader.GetOrdinal("tarifa"));
                    nvaEst.TipoEstacion = reader.GetString(reader.GetOrdinal("tipo_estacion"));

                    grafo.Add(nvaEst, ix++);
                }
            }

            // Para cada estacion, obtenemos sus adyacencias
            foreach (Estacion estacion in grafo.Keys)
            {
                DbCommand dbC = db.GetStoredProcCommand("RecuperaTramos");
                db.AddInParameter(dbC, "estacion", DbType.String, estacion.IdEstacion);
                using (IDataReader reader = db.ExecuteReader(dbC))
                {
                    while (reader.Read())
                    {
                        Conexion conexion = new Conexion();
                        conexion.MetrosTramo = reader.GetDecimal(reader.GetOrdinal("distancia"));
                        conexion.VelocidadPromedio = reader.GetDecimal(reader.GetOrdinal("velocidad"));
                        conexion.Destino = new Estacion(reader.GetString(1));
                        estacion.Conexiones.Add(conexion);
                    }
                }
            }

            // Relleno de la matriz de pesos
            MatrizPesos = new decimal[NumeroNodos, NumeroNodos];
            for (int i = 0; i < NumeroNodos; i++)
            {
                for (int j = 0; j < NumeroNodos; j++)
                {
                    Estacion uno = grafo.ElementAt(i).Key;
                    Estacion dos = grafo.ElementAt(j).Key;
                    MatrizPesos[i, j] = uno.PesoConexion(dos);
                }
            }
        }

        #endregion
    }
}
