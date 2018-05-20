using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace InstallerUI.UI
{
   public partial class PageError : CommonPage
   {
      public PageError(UIModel model) :
         base(model)
      {
         InitializeComponent();
      }

      private void _exitButton_Click(object sender, RoutedEventArgs e)
      {
         UIModel.Quit(UIModel.LastError.ErrorCode);
      }
   }
}
