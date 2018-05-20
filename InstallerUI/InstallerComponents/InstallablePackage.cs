using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace InstallerUI.InstallerComponents
{
   public class InstallablePackage : InstallableComponent
   {
      private bool _isDependency;
      public bool IsDependency
      {
         get { return _isDependency; }
         set
         {
            _isDependency = value;
            OnPropertyChanged();
         }
      }
   }
}
