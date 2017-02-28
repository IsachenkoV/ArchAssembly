using Caliburn.Micro;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace GUIdiploma.ViewModels
{
    class MainViewModel : Screen
    {
        private string _dataFilePath;
        private const string _dllPath = @"/dll/OOPdiploma.dll";
        public string DataFilePath
        {
            get
            {
                return _dataFilePath;
            }

            set
            {
                if (value == _dataFilePath)
                    return;
                _dataFilePath = value;
                NotifyOfPropertyChange(() => DataFilePath);
            }
        }

        private IWindowManager _mgr;
        private HeuristicViewModel hvm;
        private GeneralAgglomerViewModel gavm;

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

        public bool IsHeuristic
        {
            get; set;
        }

        public bool IsGenAgglo
        {
            get;
            set;
        }

        public bool IsNaive
        {
            get; set;
        }

        public bool IsFull
        {
            get;
            set;
        }

        public bool IsFWC
        {
            get;
            set;
        }

        public bool IsBin
        {
            get;
            set;
        }

        public bool IsHuffman
        {
            get;
            set;
        }

        public bool IsLevenshtein
        {
            get;
            set;
        }

        public MainViewModel (IWindowManager mgr)
        {
            _mgr = mgr;
            DisplayName = "Архиватор на основе алгоритма сборки слова";
            //_dllPath = Path.Combine(Environment.CurrentDirectory, "dll", "OOPdiploma.dll");
        }

        public void ShowHeuristicParams()
        {
            hvm = new HeuristicViewModel();
            _mgr.ShowWindow(hvm);
        }

        public void ShowAgglomParams()
        {
            gavm = new GeneralAgglomerViewModel();
            _mgr.ShowWindow(gavm);
        }

        public void BrowseDataFile()
        {
            var fd = new OpenFileDialog();
            if (!IsAlgoEnabled)
                fd.Filter = "Файлы формата aslv, ashf|*.aslv;*.ashf";
            if (fd.ShowDialog() != null)
            {
                DataFilePath = fd.FileName;
            }
        }

        [DllImport(_dllPath, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private extern static void encode_file(char[] path, int sz, int[] args);

        [DllImport(_dllPath, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private extern static void decode_file(char[] path, int type);

        public void Run()
        {
            //convert all properties and run C++ code!
            if (string.IsNullOrEmpty(DataFilePath))
            {
                MessageBox.Show("Необходимо указать файл!", "Error");
                return;
            }

            if (IsAlgoEnabled)
            {
                if (!IsLevenshtein && !IsHuffman)
                {
                    MessageBox.Show("Необходимо выбрать префиксный код!", "Error");
                    return;
                }

                if (!IsHeuristic && !IsGenAgglo && !IsNaive && !IsFull && !IsFWC && !IsBin)
                {
                    MessageBox.Show("Необходимо выбрать алгоритм нахождения схемы конкатенации!", "Error");
                    return;
                }

                int algoNum = 0, codeNum = 0, size = 0;
                int[] args;
                if (IsHeuristic)
                    algoNum = 1;
                if (IsGenAgglo)
                    algoNum = 2;
                if (IsNaive)
                    algoNum = 3;
                if (IsFull)
                    algoNum = 4;
                if (IsFWC)
                    algoNum = 5;
                if (IsBin)
                    algoNum = 6;

                if (IsHuffman)
                    codeNum = 1;
                else
                    codeNum = 2;

                if (algoNum == 1)
                {
                    size = 7;
                    args = new int[size];
                    
                    int subAlgoNum = 0;
                    if (hvm.IsNaive)
                        subAlgoNum = 1;
                    if (hvm.IsFull)
                        subAlgoNum = 2;
                    if (hvm.IsFWC)
                        subAlgoNum = 3;
                    if (hvm.IsBin)
                        subAlgoNum = 4;
                    if (hvm.IsAuto)
                        subAlgoNum = 5;

                    int minLen, maxLen;
                    if (hvm.IsAutoLen)
                    {
                        minLen = -1;
                        maxLen = -1;
                    }
                    else
                    {
                        minLen = int.Parse(hvm.MinLen);
                        maxLen = int.Parse(hvm.MaxLen);
                    }

                    int useDicts = 0;
                    if (hvm.IsUseDicts)
                        useDicts = 1;

                    int words = 0;
                    if (hvm.IsFirstWord)
                        words = 1;
                    if (hvm.IsAllWords)
                        words = 2;
                    if (hvm.IsRandWord)
                        words = 3;

                    args[0] = algoNum;
                    args[1] = codeNum;
                    args[2] = subAlgoNum;
                    args[3] = minLen;
                    args[4] = maxLen;
                    args[5] = useDicts;
                    args[6] = words;
                }
                else
                if (algoNum == 2)
                {
                    size = 4;
                    args = new int[size];

                    int subAlgoNum = 0;
                    if (gavm.IsNaive)
                        subAlgoNum = 1;
                    if (gavm.IsFull)
                        subAlgoNum = 2;
                    if (gavm.IsFWC)
                        subAlgoNum = 3;
                    if (gavm.IsBin)
                        subAlgoNum = 4;
                    if (gavm.IsAuto)
                        subAlgoNum = 5;

                    int len;
                    if (gavm.IsAutoLen)
                    {
                        len = -1;
                    }
                    else
                    {
                        len = int.Parse(gavm.Klen);
                    }

                    args[0] = algoNum;
                    args[1] = codeNum;
                    args[2] = subAlgoNum;
                    args[3] = len;
                }
                else
                {
                    size = 2;
                    args = new int[size];
                    args[0] = algoNum;
                    args[1] = codeNum;
                }
                /**
                var pth = Encoding.Default.GetBytes(DataFilePath.ToArray());
                var ch = Encoding.Convert(Encoding.Default, Encoding.GetEncoding("Windows-1251"), pth);
                var str = Encoding.GetEncoding("Windows-1251").GetChars(ch);
                */
                var str = DataFilePath + "\0";
                encode_file(str.ToArray(), size, args);

                MessageBox.Show("Сжатие прошло успешно!");
            }
            else
            {
                int type = 0;
                if (DataFilePath.Substring(DataFilePath.Length - 5) == ".aslv")
                    type = 2;
                else
                if (DataFilePath.Substring(DataFilePath.Length - 5) == ".ashf")
                    type = 1;
                else
                {
                    MessageBox.Show("Архиватор поддерживает только файлы с расширением .aslv или .ashf", "Error");
                    return;
                }
                var str = DataFilePath + "\0";
                decode_file(str.ToArray(), type);
                MessageBox.Show("Разархивирование прошло успешно!");
            }
        }
    }
}
