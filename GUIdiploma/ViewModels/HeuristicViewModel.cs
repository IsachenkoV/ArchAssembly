using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUIdiploma.ViewModels
{
    class HeuristicViewModel : Screen
    {
        private bool _useDefaultProps = true;
        private bool _notUseDefaultProps = false;

        public bool NotUseDefaultProps
        {
            get
            {
                return _notUseDefaultProps;
            }
            set
            {
                if (value == _notUseDefaultProps)
                    return;
                _notUseDefaultProps = !value;
                NotifyOfPropertyChange(() => NotUseDefaultProps);
            }
        }

        public bool UseDefaultProps
        {
            get
            {
                return _useDefaultProps;
            }
            set
            {
                if (value == _useDefaultProps)
                    return;
                _useDefaultProps = value;
                _notUseDefaultProps = !value;
                NotifyOfPropertyChange(() => UseDefaultProps);
                NotifyOfPropertyChange(() => NotUseDefaultProps);
            }
        }
        public HeuristicViewModel()
        {
            DisplayName = "Настройки эвристического алгоритма";
        }
    }
}
