using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace InstallerUI.InstallerComponents
{
    public class InstallableFeature : InstallableComponent
    {
        private bool _isChecked = false;
        public bool IsChecked
        {
            get { return _isChecked; }
            set
            {
                _isChecked = value;
                OnPropertyChanged();
            }
        }

      private int _attributes;
      public int Attributes
      {
         get { return _attributes; }
         set
         {
            _attributes = value;
            OnPropertyChanged();
         }
      }

      public bool DisallowAbsent
      {
         get
         {
            //If the attribute is 16, it means that the feature cannot be absent.
            //Set this attribute in the Wix setupt project by setting a feature's Absent="disallow"
            //https://msdn.microsoft.com/en-us/library/windows/desktop/aa368585(v=vs.85).aspx
            return (Attributes & 16) == 16;
         }
      }
    }
}
