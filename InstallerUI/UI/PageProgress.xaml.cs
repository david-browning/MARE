using System.Threading;
using System.Windows;
using InstallerUI.Bootstrapper;
using InstallerUI.UI;

namespace InstallerUI.Pages
{
   public partial class PageProgress : CommonPage
   {
      public PageProgress(UIModel m) :
          base(m)
      {
         InitializeComponent();
      }

      private void CommonPage_Loaded(object sender, RoutedEventArgs e)
      {
         UIModel.Apply();
      }

      private void _cancelButton_Click(object sender, RoutedEventArgs e)
      {
         UIModel.Pause();
      }
   }
}
