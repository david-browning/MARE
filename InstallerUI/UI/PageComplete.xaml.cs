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
using InstallerUI.InstallerComponents;
using InstallerUI.UI;

namespace InstallerUI.Pages
{
   /// <summary>
   /// Interaction logic for PageComplete.xaml
   /// </summary>
   public partial class PageComplete : CommonPage
   {
      public PageComplete(UIModel m) :
          base(m)
      {
         InitializeComponent();
      }

      private void _exitButton_Click(object sender, RoutedEventArgs e)
      {
         UIModel.Quit(0);
      }

      private void CommonPage_Loaded(object sender, RoutedEventArgs e)
      {
      }
   }
}
