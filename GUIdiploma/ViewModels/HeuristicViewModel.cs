using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

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
                IsAuto = true;
                IsNaive = false;
                IsFull = false;
                IsFWC = false;
                IsBin = false;
                NotifyOfPropertyChange(() => UseDefaultProps);
                NotifyOfPropertyChange(() => NotUseDefaultProps);
                NotifyOfPropertyChange(() => IsAuto);
                NotifyOfPropertyChange(() => IsNaive);
                NotifyOfPropertyChange(() => IsFull);
                NotifyOfPropertyChange(() => IsFWC);
                NotifyOfPropertyChange(() => IsBin);

                IsAutoLen = true;
                MinLen = "";
                MaxLen = "";
                NotifyOfPropertyChange(() => IsAutoLen);
                NotifyOfPropertyChange(() => MinLen);
                NotifyOfPropertyChange(() => MaxLen);

                IsUseDicts = true;
                NotifyOfPropertyChange(() => IsUseDicts);

                IsFirstWord = true;
                IsAllWords = false;
                IsRandWord = false;
                NotifyOfPropertyChange(() => IsFirstWord);
                NotifyOfPropertyChange(() => IsAllWords);
                NotifyOfPropertyChange(() => IsRandWord);
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

        private bool HaveSymbols(string s)
        {
            foreach (var x in s)
            {
                if (!char.IsDigit(x))
                    return true;
            }
            return false;
        }

        public bool IsAutoLen
        {
            get; set;
        }
        private string _minLen, _maxLen;
        public string MinLen
        {
            get
            {
                return _minLen;
            }
            set
            {
                if (value == _minLen)
                    return;
                if (value != "")
                {
                    IsAutoLen = false;
                    NotifyOfPropertyChange(() => IsAutoLen);
                }
                if (HaveSymbols(value))
                {
                    MessageBox.Show("Поле длины не должно содержать символы", "Error");
                    return;
                }
                _minLen = value;
                NotifyOfPropertyChange(() => MinLen);
            }
        }
        public string MaxLen
        {
            get
            {
                return _maxLen;
            }
            set
            {
                if (value == _maxLen)
                    return;
                if (value != "")
                {
                    IsAutoLen = false;
                    NotifyOfPropertyChange(() => IsAutoLen);
                }
                if (HaveSymbols(value))
                {
                    MessageBox.Show("Поле длины не должно содержать символы", "Error");
                    return;
                }
                _maxLen = value;
                NotifyOfPropertyChange(() => MaxLen);
            }
        }

        public bool IsUseDicts
        {
            get; set;
        }

        public bool IsFirstWord
        {
            get; set;
        }
        public bool IsAllWords
        {
            get; set;
        }
        public bool IsRandWord
        {
            get; set;
        }

        public HeuristicViewModel()
        {
            DisplayName = "Настройки эвристического алгоритма";

            UseDefaultProps = true;
            IsAutoLen = true;
            IsUseDicts = true;
            IsFirstWord = true;
            IsAuto = true;
            MinLen = "";
            MaxLen = "";
        }

        public void Save()
        {
            if (!IsAutoLen)
            {
                if (string.IsNullOrEmpty(MinLen) || string.IsNullOrEmpty(MaxLen))
                {
                    MessageBox.Show("Поле с длинной не должно быть пустым", "Error");
                    return;
                }
                if (int.Parse(MinLen) <= 0)
                {
                    MessageBox.Show("Минимальная длина должна быть больше 0", "Error");
                    return;
                }
                if (int.Parse(MinLen) > int.Parse(MaxLen))
                {
                    MessageBox.Show("Минимальная длина не должна превышать максимальную", "Error");
                    return;
                }
            }
            MessageBox.Show("Настройки сохранены", "");
            TryClose();
        }
    }
}
