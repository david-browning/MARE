using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace InstallerUI.InstallerComponents
{
   public class InstallableComponent : INotifyPropertyChanged
   {
      private string _id = "ID";
      public string ID
      {
         get { return _id; }
         set
         {
            _id = value;
            OnPropertyChanged();
         }
      }

      private string _name = "Name";
      public string Name
      {
         get { return _name; }
         set
         {
            _name = value;
            OnPropertyChanged();
         }
      }

      private string _description = "Description";
      public string Description
      {
         get { return _description; }
         set
         {
            _description = value;
            OnPropertyChanged();
         }
      }

      private bool _isInstalled = false;
      public bool IsInstalled
      {
         get { return _isInstalled; }
         set
         {
            _isInstalled = true;
            OnPropertyChanged();
         }
      }

      public event PropertyChangedEventHandler PropertyChanged;
      protected void OnPropertyChanged([CallerMemberName] String propertyName = "")
      {
         if(PropertyChanged != null)
         {
            PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
         }
      }
   }
}
