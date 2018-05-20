using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using InstallerUI.InstallerComponents;

namespace InstallerUI.UI
{
   public class CommonPage : Page
   {
      public CommonPage(UIModel m)
      {
         UIModel = m;
      }

      public CommonPage()
      {
         //UIModel = new UIModel();
      }

      protected UIModel UIModel
      {
         get
         {
            return (UIModel)DataContext;
         }
         private set
         {
            DataContext = value;
         }
      }
   }
}
