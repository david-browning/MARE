using System.Threading;
using System.Windows;
using InstallerUI.UI;

namespace InstallerUI.Pages
{
   /// <summary>
   /// Interaction logic for PageCancel.xaml
   /// </summary>
   public partial class PageCancel : CommonPage
   {
      public PageCancel(UIModel m) :
         base(m)
      {
         InitializeComponent();
      }

      private void _yesButton_Click(object sender, RoutedEventArgs e)
      {
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Quit(0);
         });
      }

      private void _noButton_Click(object sender, RoutedEventArgs e)
      {
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Resume();
            UIModel.NavigateBack();
         });
      }
   }
}
