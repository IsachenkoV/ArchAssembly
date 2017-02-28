using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace GUIdiploma.ViewModels
{
    class GeneralAgglomerViewModel : Screen
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

                IsAuto = true;
                IsNaive = false;
                IsFull = false;
                IsFWC = false;
                IsBin = false;
                NotifyOfPropertyChange(() => IsAuto);
                NotifyOfPropertyChange(() => IsNaive);
                NotifyOfPropertyChange(() => IsFull);
                NotifyOfPropertyChange(() => IsFWC);
                NotifyOfPropertyChange(() => IsBin);

                IsAutoLen = true;
                Klen = "";
                NotifyOfPropertyChange(() => IsAutoLen);
                NotifyOfPropertyChange(() => Klen);
            }
        }

        public bool IsNaive
        {
            get; set;
        }
        public bool IsFull
        {
            get; set;
        }
        public bool IsFWC
        {
            get; set;
        }
        public bool IsBin
        {
            get; set;
        }
        public bool IsAuto
        {
            get; set;
        }

        public bool IsAutoLen
        {
            get; set;
        }
        private string _klen;
        public string Klen
        {
            get
            {
                return _klen;
            }
            set
            {
                if (value == _klen)
                    return;
                if (value != "")
                {
                    IsAutoLen = false;
                    NotifyOfPropertyChange(() => IsAutoLen);
                }
                _klen = value;
                NotifyOfPropertyChange(() => Klen);
            }
        }
        public GeneralAgglomerViewModel()
        {
            DisplayName = "Настройки обобщенного агломеративного алгоритма";
            UseDefaultProps = true;
            IsAuto = true;
            IsAutoLen = true;
            Klen = "";
        }

        public void Save()
        {
            if (!IsAutoLen)
            {
                if (string.IsNullOrEmpty(Klen))
                {
                    MessageBox.Show("Поле с длинной не должно быть пустым", "Error");
                    return;
                }
                if (int.Parse(Klen) <= 0)
                {
                    MessageBox.Show("Минимальная длина должна быть больше 0", "Error");
                    return;
                }
            }

            MessageBox.Show("Настройки сохранены", "");
            TryClose();
        }
    }
}
