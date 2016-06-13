using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUIdiploma.ViewModels
{
    class MainViewModel : Screen
    {
        private IWindowManager _mgr;

        private bool _isAlgoEnabled;

        public bool IsAlgoEnabled
        {
            get
            {
                return _isAlgoEnabled;
            }
            set
            {
                if (value == _isAlgoEnabled)
                    return;
                _isAlgoEnabled = value;
                NotifyOfPropertyChange(() => IsAlgoEnabled);
            }
        }

        public MainViewModel (IWindowManager mgr)
        {
            _mgr = mgr;
            DisplayName = "Архиватор на основе алгоритма сборки слова";
        }

        public void ShowHeuristicParams()
        {
            _mgr.ShowWindow(new HeuristicViewModel());
        }

        public void ShowAgglomParams()
        {
            _mgr.ShowWindow(new GeneralAgglomerViewModel());
        }
    }
}
