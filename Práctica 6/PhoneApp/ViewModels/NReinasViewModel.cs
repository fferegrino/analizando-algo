using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
<<<<<<< HEAD
using ProblemaNReinas;
=======
using Practica6.Common;
>>>>>>> Práctica 6 completa

namespace PhoneApp.ViewModels
{
    public class NReinasViewModel : BaseViewModel
    {
        private Tablero tablero;

        public Tablero Tablero
        {
            get { return tablero; }
            set { tablero = value; OnPropertyChanged(); }
        }

        private int numeroReinas;

        public int NumeroReinas
        {
            get { return numeroReinas; }
            set { numeroReinas = value; OnPropertyChanged(); }
        }

<<<<<<< HEAD
=======
        private bool resultado;

        public bool Resultado
        {
            get { return resultado; }
            set { resultado = value; OnPropertyChanged(); }
        }

>>>>>>> Práctica 6 completa
        private int iteraciones;

        public int Iteraciones
        {
            get { return iteraciones; }
            set { iteraciones = value; OnPropertyChanged(); }
        }

        public NReinasViewModel()
        {
            Iteraciones = 5;
            NumeroReinas = 5;
        }

        private ActionCommand ejecutaNReinas;

        public ActionCommand EjecutaNReinas
        {
            get
            {
                if (ejecutaNReinas == null)
                {
                    ejecutaNReinas = new ActionCommand(() =>
                    {
                        Tablero = new Tablero(NumeroReinas);
<<<<<<< HEAD
                        Tablero.LasVegas(Iteraciones);
=======
                        Resultado = Tablero.LasVegas(Iteraciones);
>>>>>>> Práctica 6 completa
                    });
                }
                return ejecutaNReinas;
            }
        }

    }
}
