using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace PhoneApp.ViewModels
{
    public class ActionCommand : ICommand
    {
        Action act;

        public ActionCommand(Action action)
        {
            act = action;
        }

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public event EventHandler CanExecuteChanged;

        public void Execute(object parameter)
        {
            act();
        }
    }
}
