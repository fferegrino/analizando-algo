using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using PhoneApp.ViewModels;
<<<<<<< HEAD
using ProblemaNReinas;
=======
using Practica6.Common;
>>>>>>> Práctica 6 completa
using System.Windows.Shapes;
using System.Windows.Media;

namespace PhoneApp
{
    public partial class ProblemaReinas : PhoneApplicationPage
    {
        static GridLength CellSize = new GridLength(25);

        public ProblemaReinas()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            NReinasViewModel vm = DataContext as NReinasViewModel;
            vm.EjecutaNReinas.Execute(null);
            GeneraTablero(vm.Tablero);
        }

        /// <summary>
        /// Método para generar el tablero en pantalla
        /// </summary>
        /// <param name="tablero"></param>
        public void GeneraTablero(Tablero tablero)
        {
            TableroReinas.ColumnDefinitions.Clear();
            TableroReinas.RowDefinitions.Clear();
            TableroReinas.Children.Clear();
            for (int i = 0; i < tablero.NumeroReinas; i++)
            {
                TableroReinas.ColumnDefinitions.Add(new ColumnDefinition() { Width = CellSize });
                TableroReinas.RowDefinitions.Add(new RowDefinition() { Height = CellSize });
            }

            for (int i = 0; i < tablero.NumeroReinas; i++)
            {
                for (int j = 0; j < tablero.NumeroReinas; j++)
                {
                    Rectangle r = new Rectangle();
<<<<<<< HEAD
                    r.SetValue(Grid.RowProperty, j);
                    r.SetValue(Grid.ColumnProperty, i);

                    if (((i * tablero.NumeroReinas) + j) % 2 == 0)
=======
                    r.SetValue(Grid.RowProperty, i);
                    r.SetValue(Grid.ColumnProperty, j);

                    if ((i  + j) % 2 == 0)
>>>>>>> Práctica 6 completa
                        r.Fill = new SolidColorBrush(Colors.Black);
                    else
                        r.Fill = new SolidColorBrush(Colors.White);

                    TableroReinas.Children.Add(r);

                    if (tablero.Reinas[i, j] == 1)
                    {
                        Ellipse c = new Ellipse();
                        c.Fill = new SolidColorBrush(Color.FromArgb(255, 164, 16, 52));
                        c.SetValue(Grid.ColumnProperty, j);
                        c.SetValue(Grid.RowProperty, i);
                        TableroReinas.Children.Add(c);
                    }

                }
            }
        }
    }
}