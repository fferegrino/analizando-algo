using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ComprobacionPrimalidad;

namespace PhoneApp.ViewModels
{
    public class ComprobacionPrimalidadViewModel : BaseViewModel
    {
        private int iteraciones;
        public int Iteraciones
        {
            get { return iteraciones; }
            set { iteraciones = value; OnPropertyChanged(); }
        }

        private ulong numero;
        public ulong Numero
        {
            get { return numero; }
            set { numero = value; EsPrimo = true; OnPropertyChanged(); }
        }

        private bool isBusy;
        public bool IsBusy
        {
            get { return isBusy; }
            set { isBusy = value; OnPropertyChanged(); }
        }

        private bool esPrimo;

        public bool EsPrimo
        {
            get { return esPrimo; }
            set { esPrimo = value; OnPropertyChanged(); }
        }


        public ComprobacionPrimalidadViewModel()
        {
            EsPrimo = true;
            Numero = 3571;
            Iteraciones = 100;
        }

        private ActionCommand compruebaCommand;

        public ActionCommand CompruebaCommand
        {
            get
            {
                if (compruebaCommand == null)
                {
                    compruebaCommand = new ActionCommand(() =>
                    {
                        IsBusy = true;
                        SupuestoPrimo sp = new SupuestoPrimo(numero);
                        EsPrimo = sp.EsPrimo(iteraciones);
                        IsBusy = false;
                    });
                }
                return compruebaCommand;
            }

        }


    }
}
